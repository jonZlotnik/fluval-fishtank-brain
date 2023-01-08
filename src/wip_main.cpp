// #include <Arduino.h>
// #include <PubSubClient.h>
// #include <ESP8266WiFi.h>

// #include "config.h"

// WiFiClient wifi;
// PubSubClient mqtt;

// void callback(const char[] topic, byte* payload, unsigned int length){

// }

// void setup() {
//   Serial.begin(9600);
//   WiFi.begin(WIFI_SSID, WIFI_PASS);

//   Serial.print("Connecting to WiFi...");
//   while (WiFi.status() != WL_CONNECTED) 
//   {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected!");

//   Serial.println("\n\nConnecting to MQTT...");
//   mqtt = PubSubClient("10.0.1.135", 1883, callback, wifi);
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) 
//   {
    
//   }
// }