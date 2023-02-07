#ifndef FluvalLights_h
#define FluvalLights_h

#include <queue>
#include <map>
#include <vector>
#include <string>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_CMD int
#define IR_BLUE 0xF7609F
#define IR_BLUE_1 0xF750AF
#define IR_BLUE_2 0xF7708F
#define IR_BLUE_3 0xF748B7
#define IR_BLUE_4 0xF76897
#define IR_GREEN 0xF7A05F
#define IR_GREEN_1 0xF7906F
#define IR_GREEN_2 0xF7B04F
#define IR_GREEN_3 0xF78877
#define IR_GREEN_4 0xF7A857
#define IR_RED 0xF720DF
#define IR_RED_1 0xF710EF
#define IR_RED_2 0xF730CF
#define IR_RED_3 0xF708F7
#define IR_RED_4 0xF728D7
#define IR_NIGHT 0xF7F00F
#define IR_STORM 0xF7C837
#define IR_RGB_MINUS 0xF7807F
#define IR_RGB_PLUS 0xF700FF
#define IR_RGB_POWER 0xF740BF
#define IR_WHITE_MINUS 0xF7D02F
#define IR_WHITE_PLUS 0xF7E01F
#define IR_WHITE_POWER 0xF7C03F
#define IR_COLOR_CYCLE 0xF7E817

#define DEFAULT_IR_PIN 4
#define DEFAULT_MIN_MILLIS_INTERVAL 500

typedef const char * FluvalState;

class FluvalStateTransition
{
private:
    std::vector<IR_CMD> stateTransition;
    FluvalState finalState;

public:
    static FluvalState RESET() {
        return "reset";
    }
    static FluvalState DAY() {
        return "day";
    }
    static FluvalState NIGHT() {
        return "night";
    }
    FluvalStateTransition(std::vector<IR_CMD> stateTransition)
    {
        this->stateTransition = stateTransition;

    }
    FluvalStateTransition(FluvalState stateTransitionName)
    {
        Serial.println(stateTransitionName);
        stateTransition = std::vector<int>();
        if (strcmp(stateTransitionName, FluvalStateTransition::RESET()) == 0)
        {
            this->finalState = FluvalStateTransition::RESET();
            Serial.println("RESET received");
            this->stateTransition.push_back(IR_NIGHT);
            this->stateTransition.push_back(IR_WHITE_POWER);
            for (int i = 0; i < 16; i++)
            {
                this->stateTransition.push_back(IR_WHITE_MINUS);
            }
            this->stateTransition.push_back(IR_WHITE_POWER);
            this->stateTransition.push_back(IR_RED);
            for (int i = 0; i < 16; i++)
            {
                this->stateTransition.push_back(IR_WHITE_MINUS);
            }
            this->stateTransition.push_back(IR_RGB_POWER);
        }
        else if (strcmp(stateTransitionName, FluvalStateTransition::DAY()) == 0)
        {
            this->finalState = FluvalStateTransition::DAY();
            Serial.println("DAY received");
            this->stateTransition.push_back(IR_WHITE_POWER);
            for (int i = 0; i < 16; i++)
            {
                this->stateTransition.push_back(IR_WHITE_PLUS);
            }
        }
        else if (strcmp(stateTransitionName, FluvalStateTransition::NIGHT()) == 0)
        {
            this->finalState = FluvalStateTransition::NIGHT();
            Serial.println("NIGHT received");
            for (int i = 0; i < 16; i++)
            {
                this->stateTransition.push_back(IR_WHITE_MINUS);
            }
            this->stateTransition.push_back(IR_NIGHT);
        }
        else
        {
            Serial.println("Unknown state transition");
        }
    }

    std::vector<IR_CMD> getSequence()
    {
        return this->stateTransition;
    }

    FluvalState getFinalState() {
        return this->finalState;
    }
};

class FluvalClient
{
private:
    std::queue<IR_CMD> command_queue;
    std::queue<FluvalState> state_queue;
    uint16_t irPin;
    IRsend *ir_sender;
    unsigned long minMillisInterval;
    unsigned long lastCommandTime;
    bool autoEnabled;
    FluvalState currState;
    
public:
    FluvalClient()
    {
        this->command_queue = std::queue<IR_CMD>();
        this->state_queue = std::queue<FluvalState>();
        this->irPin = DEFAULT_IR_PIN;
        this->ir_sender = new IRsend(DEFAULT_IR_PIN);
        this->minMillisInterval = DEFAULT_MIN_MILLIS_INTERVAL;
        this->currState = FluvalStateTransition::RESET();
    }
    FluvalClient(uint16_t irSenderPin, unsigned long minMillisInterval = DEFAULT_MIN_MILLIS_INTERVAL)
    {
        this->command_queue = std::queue<IR_CMD>();
        this->irPin = irSenderPin;
        this->ir_sender = new IRsend(irSenderPin);
        this->minMillisInterval = minMillisInterval;
        this->currState = FluvalStateTransition::RESET();
    }
    void loop()
    {
        Serial.print("Queue size: ");
        Serial.print(command_queue.size());
        unsigned long timeSinceLastCommand = millis() - this->lastCommandTime;
        Serial.print(" | ");
        Serial.print("Time since last command: ");
        Serial.print(timeSinceLastCommand);
        if (!command_queue.empty() && timeSinceLastCommand > this->minMillisInterval)
        {
            Serial.print(" | ");
            Serial.print("Sending command ");
            Serial.print(command_queue.front());
            IR_CMD command = command_queue.front();
            command_queue.pop();
            pinMode(4, OUTPUT);
            this->ir_sender->sendNEC(command);
            lastCommandTime = millis();
            // update current state if we reach state pushed onto the state_queue
            if (state_queue.front() != nullptr) {
                this->currState = state_queue.front();
            }
            state_queue.pop();
        }
        Serial.println();
        Serial.println();
        delay(400);
    }
    void enqueue(FluvalStateTransition stateTransition)
    {
        std::vector<IR_CMD> transitionSequence = stateTransition.getSequence();
        for (unsigned int i = 0; i < transitionSequence.size(); i++)
        {
            this->command_queue.push(transitionSequence[i]);
            if (i == 0) {
                this->state_queue.push(stateTransition.getFinalState());
            } else {
                this->state_queue.push(nullptr);
            }
        }
    }
    FluvalState getState() {
        return this->currState;
    }
    int getQueueSize() {
        return this->state_queue.size();
    }
};

#endif