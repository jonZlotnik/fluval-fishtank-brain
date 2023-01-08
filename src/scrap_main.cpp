// #include <Arduino.h>
// #include <ArduinoJson.h>
// #include <ESP8266HTTPClient.h>
// #include <ESP8266WiFi.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>

// const char* ssid = "ssid";
// const char* password = "password";

// const long utcOffsetInSeconds = -18000;

// const char* lat = "0";
// const char* lng = "0";

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// void setup() {
//   Serial.begin(9600);
//   WiFi.begin(ssid, password);

//   Serial.print("Connecting...");
//   while (WiFi.status() != WL_CONNECTED) 
//   {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("\nConnected!");
//   timeClient.begin();
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) 
//   {

//     timeClient.update();
//     Serial.println(timeClient.getFormattedTime());

//     HTTPClient http; // Object of class HTTPClient
//     http.begin("https://api.sunrise-sunset.org/json?lat=" + lat + "&lng=" + lng + "&formatted=0");
//     int httpCode = http.GET();

//     if (httpCode > 0) 
//     {
//       // const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
//       StaticJsonDocument<1024> doc;
//       DeserializationError error = deserializeJson(doc, http.getString());
//       if (error) {
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return;
//       }

//       const char* sunrise = doc["sunrise"]; 
//       const char* sunset = doc["sunset"];

//       Serial.printf("Sunrise: %s \n", sunrise);
//       Serial.printf("Sunset: %s \n", sunset);

//     }
//     http.end(); //Close connection
//   }
//   delay(60000);
// }