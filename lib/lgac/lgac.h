#ifndef LGAC_h
#define LGAC_h

#define LGAC_BUFFER_SIZE 59
#define FIRST_BYTE 136 //b10001000
#define FIRST_HIGH 8271
#define FIRST_LOW 4298
#define ZERO_AND_ONE_HIGH 439
#define ZERO_LOW 647
#define ONE_LOW 1709

extern int bit_read(uint16_t num, uint16_t pos);
extern int get_fan_speed(int fanSpeed);
extern int get_mode(char* modeName);
extern int get_state(char* stateName);
extern int get_temperature(int temp);
extern uint16_t* lgac_set_mode(char* mode, int fan, int temperature, char* state);
extern void lgac_debug();
extern void lgac_fill_buffer(int pos, int bits, int value);

#endif