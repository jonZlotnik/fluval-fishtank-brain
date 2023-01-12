#include <string>

#include <ESP8266HTTPClient.h>
#include <ArduinoJSON.h>

#include <synced_clock.hpp>

class AutoController {
    private:
        bool enabled;
        WiFiClient wifi;
        HTTPClient sunHTTP;
        String sunAPI = "https://api.sunrise-sunset.org/json";
        uint32 LastSunDataTime;

    public:
    AutoController(WiFiClient wifi, SyncedClock clk);
    void enable();
    void disable();
    void loop();
        
};

AutoController::AutoController(WiFiClient wifi, SyncedClock clk) {
            this->enabled = false;
            sunHTTP.useHTTP10();
        }
void AutoController::enable() {
    this->enabled = true;
}
void AutoController::disable() {
    this->enabled = false;
}
void AutoController::loop() {
    if (!this->enabled) {
        return;
    }
    
}