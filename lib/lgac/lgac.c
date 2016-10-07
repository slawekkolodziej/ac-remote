#include "lgac.h"

uint16_t crc;
uint16_t lgac_buffer[LGAC_BUFFER_SIZE];

uint16_t* lgac_set_mode(char* modeName, int fan, int temperature, char* stateName) {
    lgac_buffer[0] = FIRST_HIGH;
    lgac_buffer[1] = FIRST_LOW;
    crc = 0;

    int state = get_state(stateName);
    int mode;

    if (strcmp(stateName, "off") == 0) {
        mode = get_mode("none");
        temperature = 0;
        fan = get_fan_speed(-1);
    } else {
        mode = get_mode(modeName);
        temperature = get_temperature(temperature);
        fan = get_fan_speed(fan);
    }

    // first bytes, probably contains more settings
    lgac_fill_buffer(0, 8, FIRST_BYTE);
    lgac_fill_buffer(8, 5, state);
    lgac_fill_buffer(13, 3, mode);
    lgac_fill_buffer(16, 4, temperature);
    lgac_fill_buffer(20, 1, 0); //jet
    lgac_fill_buffer(21, 3, fan);
    lgac_fill_buffer(24, 4, crc);

    lgac_buffer[LGAC_BUFFER_SIZE - 1] = ZERO_AND_ONE_HIGH;

    return lgac_buffer;
}

int get_mode(char* modeName) {
    if (strcmp(modeName, "heating") == 0 ) {
        return 4; //b100
    } else if (strcmp(modeName, "auto") == 0 ) {
        return 3; //b011
    } else if (strcmp(modeName, "fan") == 0 ) {
        return 2;
    } else if (strcmp(modeName, "dehumidification") == 0 ) {
        return 1; //b001
    } else if (strcmp(modeName, "cooling") == 0 ) {
        return 0;
    } else if (strcmp(modeName, "none") == 0 ) {
        return 0;
    }

    return 0;
}

int get_state(char* stateName) {
    if (strcmp(stateName, "on") == 0) {
        return 0;
    } else if (strcmp(stateName, "off")) {
        return 24; //b11000
    }

    return 24;
}

int get_fan_speed(int fanSpeed) {
    switch (fanSpeed) {
        case 1:
            return 1;
        case 2:
            return 0;
        case 3:
            return 2;
        case 4:
            return 4;
        case -1:
        default:
            return 5;
    }
}

int get_temperature(int temp) {
    return temp - 15;
}

void lgac_fill_buffer(int pos, int bits, int value) {
    for (int i = bits; i > 0; i--) {
        int bit_value = bit_read(value, i - 1);
        int bit_pos = 2 + 2 * (pos + bits - i);
        lgac_buffer[ bit_pos ] = ZERO_AND_ONE_HIGH;
        lgac_buffer[ bit_pos + 1] = (bit_value == 1 ? ONE_LOW : ZERO_LOW);
        if (bit_value == 1) {
            int bitset = 1 << (128 + i - pos - bits - 1) % 4;
            crc = crc + bitset;
        }
    }
}

void lgac_debug() {
    unsigned char i;

    for (i = 0; i < LGAC_BUFFER_SIZE; i++){
        printf("%d,", lgac_buffer[i]);
    }
}

int bit_read(uint16_t num, uint16_t pos) {
    return (num & ( 1 << pos )) >> pos;
}
