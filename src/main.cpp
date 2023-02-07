#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <IRsend.h>
#include <WiFiManager.h>

#include "fluval_lights.hpp"
#include "auto_controller.hpp"
#include "config.hpp"
#include "time.h"

const char *ntpServer = "pool.ntp.org";
const char *mqtt_server = CONFIG_MQTT_BROK;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
const uint16_t irLED = 4; // ESP8266 GPIO pin to use. Recommended: 4 (D2).

FluvalClient fluvalClient(irLED);
AutoController autoController(
  CONFIG_LONGITUDE, CONFIG_LATITUDE,
  CONFIG_TIMEZONE, 
  &fluvalClient, ntpServer);

#define MSG_BUFFER_SIZE (64)
char msg[MSG_BUFFER_SIZE];

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.printf("Message arrived [%s] ", topic);
  if (length >= MSG_BUFFER_SIZE - 1)
  {
    Serial.println("Message too long");
    return;
  }
  for (unsigned int i = 0; i < length; i++)
  {
    msg[i] = (char)payload[i];
  }
  msg[length] = '\0';
  Serial.println(msg);

  if (strcmp(msg, "auto") == 0)
  {
    Serial.println("AutoController Enabled!!!");
    autoController.enable();
  }
  else
  {
    autoController.disable();
    FluvalStateTransition transition = FluvalStateTransition(msg);
    fluvalClient.enqueue(transition);
  }
}

void reconnect()
{
  while (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // resubscribe
      mqttClient.subscribe("fish/fluval-flex-9g/lights");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  WiFiManager wifiManager;
  wifiManager.autoConnect(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);
  if (!wifiClient.connected()){
    wifiManager.startConfigPortal("esp-fluval");
  }
  Serial.println("wifi connected...yeey :)");
  
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);

  FluvalStateTransition toReset("reset");
  fluvalClient.enqueue(toReset);
  autoController.enable();
}

void loop()
{
  delay(100);
  Serial.print("State: ");
  Serial.println(fluvalClient.getState());
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();
  fluvalClient.loop();
  autoController.loop();
}
