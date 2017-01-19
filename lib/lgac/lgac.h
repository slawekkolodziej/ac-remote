#ifndef LGAC_h
#define LGAC_h

#define LGAC_BUFFER_SIZE 59
#define FIRST_BYTE 136 //b10001000
#define FIRST_HIGH 8271
#define FIRST_LOW 4298
#define ZERO_AND_ONE_HIGH 439
#define ZERO_LOW 647
#define ONE_LOW 1709

typedef struct lgac_conf {
    char* stateName;
    char* modeName;
    uint8_t temperature;
    uint8_t fan;
} lgac_conf;

uint16_t* lgac_set_mode(lgac_conf* conf);
uint16_t* lgac_fill_buffer(uint16_t pos, uint16_t bits, uint16_t value, uint16_t* crc);
int bit_read(uint16_t num, uint16_t pos);
int get_fan_speed(int fanSpeed);
int get_mode(char* modeName);
int get_state(char* stateName);
int get_temperature(int temp);
void lgac_debug();

#endif