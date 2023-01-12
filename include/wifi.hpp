#include "config.hpp"

#include <ESP8266WiFi.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}