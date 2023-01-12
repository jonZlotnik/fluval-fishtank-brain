#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <IRsend.h>


#include "fluval_lights.hpp"
#include "auto_controller.hpp"
#include "config.hpp"
#include "wifi.hpp"

const char* mqtt_server = MQTT_BROK;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
const uint16_t irLED = 4; // ESP8266 GPIO pin to use. Recommended: 4 (D2).

FluvalClient fluvalClient(irLED);

#define MSG_BUFFER_SIZE	(64)
char msg[MSG_BUFFER_SIZE];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.printf("Message arrived [%s] ", topic);
  if (length >= MSG_BUFFER_SIZE-1) {
    Serial.println("Message too long");
    return;
  }
  for (unsigned int i = 0; i < length; i++) {
    msg[i] = (char)payload[i];
  }
  msg[length] = '\0';
  Serial.println(msg);

  if (strcmp(msg, "auto") == 0) {

  } else {
    FluvalStateTransition transition = FluvalStateTransition(msg);
    fluvalClient.enqueue(transition);
  }
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      // resubscribe
      mqttClient.subscribe("fishtanks/nano");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  setup_wifi();
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  fluvalClient.loop();
}