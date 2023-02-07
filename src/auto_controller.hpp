#ifndef AutoController_h
#define AutoController_h

#include <string>
#include <sunrise.h>

#include "fluval_lights.hpp"

class AutoController
{
private:
    bool enabled;
    double lng;
    double lat;
    FluvalClient *fClient;

public:
    AutoController(double lng, double lat, const char *posixTZ,
                   FluvalClient *fClient, const char *ntpSrvr);
    void enable();
    void disable();
    void loop();
};

AutoController::AutoController(double lng, double lat, const char *posixTZ,
                               FluvalClient *fClient, const char *ntpSrvr)
{
    this->enabled = false;
    this->lng = lng;
    this->lat = lat;
    this->fClient = fClient;
    // localize time library
    configTime(posixTZ, ntpSrvr);
}
void AutoController::enable()
{
    this->enabled = true;
}
void AutoController::disable()
{
    this->enabled = false;
}
void AutoController::loop()
{
    // If not enabled, skip.
    if (!this->enabled || fClient->getQueueSize() > 0)
    {
        return;
    }
    // Otherwise...
    // Get current local time as posix Epoch
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    time(&now);

    // Check if sun is visible
    SunRise sun = SunRise();
    sun.calculate(this->lat, this->lng, now);

    // If sun is visible, ensure light state is daytime
    if (sun.isVisible)
    {
        if (strcmp(this->fClient->getState(), FluvalStateTransition::DAY()) != 0)
        {
            FluvalStateTransition toDay(FluvalStateTransition::DAY());
            fClient->enqueue(toDay);
        }

    } // if sun is not visible, ensure light state is nighttime
    else
    {
        if (strcmp(this->fClient->getState(), FluvalStateTransition::NIGHT()) != 0)
        {
            FluvalStateTransition toNight(FluvalStateTransition::NIGHT());
            fClient->enqueue(toNight);
        }
    }
}

#endif