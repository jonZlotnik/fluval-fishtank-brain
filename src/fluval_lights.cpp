// #include <string>
// #include <map>

// #include <Arduino.h>
// #include <IRremoteESP8266.h>
// #include <IRsend.h>

// // #include "fluval_lights.hpp"

// std::map<std::string, LightStates> commands = {
//     {"auto", LightStates::AUTO},
//     {"reset", LightStates::RESET},
//     {"day", LightStates::DAY},
//     {"night", LightStates::NIGHT},
//     {"sunrise", LightStates::SUNRISE},
//     {"sunset", LightStates::SUNSET},
// };

// // FluvalClient::FluvalClient()
// // {
// //     IRsend default_ir_sender(4);
// //     this->ir_sender = default_ir_sender;
// // }

// void update_lights(std::string command)
// {
//     switch (commands[command]){
//     case LightStates::AUTO:
//         break;
//     case LightStates::RESET:
//         reset_sequence();
//         Serial.println("Reset complete.");
//         break;
//     case LightStates::DAY:
//         break;
//     case LightStates::NIGHT:
//         break;
//     case LightStates::SUNSET:
//         set_sun();
//         Serial.println("Sunset complete.");
//         break;
//     default:
//         Serial.println("No sun commands.");
//         break;
//     }
// }

// void send_ir_command(uint64_t data, int interval = 1000)
// {
//     delay(interval);
//     // irsend.sendNEC(data);
// }
// void repeat_ir_command(uint64_t data, int times, int interval = 1000)
// {
//     for (int i = 0; i < times; i++)
//     {
//         delay(interval);
//         // irsend.sendNEC(data);
//     }
// }

// void init_lights()
// {
//     // irsend.begin();
//     // #if ESP8266
//     // Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
//     // #else  // ESP8266
//     // Serial.begin(115200, SERIAL_8N1);
//     // #endif  // ESP8266
// }

// void reset_sequence()
// {
//     send_ir_command(IR_NIGHT);
//     send_ir_command(IR_WHITE_POWER);
//     repeat_ir_command(IR_WHITE_MINUS, 16, 500);
//     send_ir_command(IR_WHITE_POWER);
//     send_ir_command(IR_RED);
//     repeat_ir_command(IR_RGB_MINUS, 16, 500);
//     send_ir_command(IR_RGB_POWER);
// }

// void rise_sun()
// {
//     send_ir_command(IR_RED_1);
//     repeat_ir_command(IR_RGB_PLUS, 9);
//     send_ir_command(IR_RED_2);
//     send_ir_command(IR_RED_3);
//     send_ir_command(IR_WHITE_POWER);
//     repeat_ir_command(IR_WHITE_PLUS, 9);
//     send_ir_command(IR_RGB_POWER);
// }
// void set_sun()
// {
//     send_ir_command(IR_RED_3);
//     repeat_ir_command(IR_WHITE_MINUS, 9);
//     send_ir_command(IR_WHITE_POWER);
//     send_ir_command(IR_RED_2);
//     send_ir_command(IR_RED_1);
//     repeat_ir_command(IR_RGB_MINUS, 9);
//     send_ir_command(IR_RGB_POWER);
// }
// void start_storm()
// {
// }
// void end_storm()
// {
// }
// void unicorn_vomit()
// {
// }