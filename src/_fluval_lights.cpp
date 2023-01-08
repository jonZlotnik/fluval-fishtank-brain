#include "_fluval_lights.h"

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void send_ir_command(uint64_t data, int interval = 1000){
    delay(interval);
    irsend.sendNEC(data);
}
void repeat_ir_command(uint64_t data, int times, int interval = 1000){
    for (int i = 0; i < times; i++)
    {
       delay(interval);
       irsend.sendNEC(data);
    }
}

void init_lights(){
    irsend.begin();
    // #if ESP8266
    // Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
    // #else  // ESP8266
    // Serial.begin(115200, SERIAL_8N1);
    // #endif  // ESP8266
}

void reset_sequence(){
    send_ir_command(IR_NIGHT);
    send_ir_command(IR_WHITE_POWER);
    repeat_ir_command(IR_WHITE_MINUS, 16, 500);
    send_ir_command(IR_WHITE_POWER);
    send_ir_command(IR_RED);
    repeat_ir_command(IR_RGB_MINUS, 16, 500);
    send_ir_command(IR_RGB_POWER);
}

void rise_sun() {
    send_ir_command(IR_RED_1);
    repeat_ir_command(IR_RGB_PLUS, 9);
    send_ir_command(IR_RED_2);
    send_ir_command(IR_RED_3);
    send_ir_command(IR_WHITE_POWER);
    repeat_ir_command(IR_WHITE_PLUS, 9);
    send_ir_command(IR_RGB_POWER);
}
void set_sun() {
    send_ir_command(IR_RED_3);
    repeat_ir_command(IR_WHITE_MINUS, 9);
    send_ir_command(IR_WHITE_POWER);
    send_ir_command(IR_RED_2);
    send_ir_command(IR_RED_1);
    repeat_ir_command(IR_RGB_MINUS, 9);
    send_ir_command(IR_RGB_POWER);
}
void start_storm() {

}
void end_storm() {

}
void unicorn_vomit() {

}