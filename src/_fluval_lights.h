#define IR_BLUE         0xF7609F
#define IR_BLUE_1       0xF750AF
#define IR_BLUE_2       0xF7708F
#define IR_BLUE_3       0xF748B7
#define IR_BLUE_4       0xF76897
#define IR_GREEN        0xF7A05F
#define IR_GREEN_1      0xF7906F
#define IR_GREEN_2      0xF7B04F
#define IR_GREEN_3      0xF78877
#define IR_GREEN_4      0xF7A857
#define IR_RED          0xF720DF
#define IR_RED_1        0xF710EF
#define IR_RED_2        0xF730CF
#define IR_RED_3        0xF708F7
#define IR_RED_4        0xF728D7
#define IR_NIGHT        0xF7F00F
#define IR_STORM        0xF7C837
#define IR_RGB_MINUS    0xF7807F
#define IR_RGB_PLUS     0xF700FF
#define IR_RGB_POWER    0xF740BF
#define IR_WHITE_MINUS  0xF7D02F
#define IR_WHITE_PLUS   0xF7E01F
#define IR_WHITE_POWER  0xF7C03F
#define IR_COLOR_CYCLE  0xF7E817


void init_lights();
void rise_sun();
void set_sun();
void start_storm();
void end_storm();
void unicorn_vomit();
void reset_sequence();