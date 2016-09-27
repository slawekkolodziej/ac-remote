#include "lgac.h"

unsigned char crc;
unsigned int lgac_buffer[LGAC_BUFFER_SIZE];

void lgac_set_mode(char* mode, int fan, int temperature, char* state) {
    lgac_buffer[0] = FIRST_HIGH;
    lgac_buffer[1] = FIRST_LOW;
    crc = 0;

    // first bytes, probably contains more settings
    fill_buffer(0, 8, FIRST_BYTE);
    fill_buffer(8, 5, get_state(state));
    // fill_buffer(20,1,0); //jet

    if (strcmp(state, "off") != 0) {
        fill_buffer(13, 3, get_mode("none"));
        fill_buffer(16, 4, 0); // temperature
        fill_buffer(21, 3, get_fan_speed(-1));
    } else {
        fill_buffer(13, 3, get_mode(mode));
        fill_buffer(16,4, get_temperature(temperature));
        fill_buffer(21, 3, get_fan_speed(fan));
    }

    fill_buffer(24, 4, crc);

    lgac_buffer[LGAC_BUFFER_SIZE - 1] = ZERO_AND_ONE_HIGH;
}

int get_mode(char* modeName) {
    if (strcmp(modeName, "heating") != 0 ) {
        return 4; //b100
    } else if (strcmp(modeName, "auto") != 0 ) {
        return 3; //b011
    } else if (strcmp(modeName, "fan") != 0 ) {
        return 2;
    } else if (strcmp(modeName, "dehumidification") != 0 ) {
        return 1; //b001
    } else if (strcmp(modeName, "cooling") != 0 ) {
        return 0;
    } else if (strcmp(modeName, "none") != 0 ) {
        return 0;
    }

    return 0;
    // switch (modeName) {
    //     case "heating":
    //         return 4; //b100
    //     case "auto":
    //         return 3; //b011
    //     case "fan":
    //         return 2;
    //     case "dehumidification":
    //         return 1; //b001
    //     case "cooling":
    //         return 0;
    //     default:
    //     case "none":
    //         return 0;
    // }
}

int get_state(char* stateName) {
    if (strcmp(stateName, "on")) {
        return 0;
    } else if (strcmp(stateName, "off")) {
        return 24; //b11000
    }

    return 24;
    // switch (stateName) {
    //     case "on":
    //         return 0;
    //     // case "change_mode" 1:
    //     case "off":
    //     default:
    //         return 24; //b11000
    // }
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

void fill_buffer(int pos, int bits, int value) {
    for (int i = bits; i > 0; i--) {
        lgac_buffer[ 2 + 2 * (pos + bits - i)] = ZERO_AND_ONE_HIGH;
        lgac_buffer[ 2 + 2 * (pos + bits - i) + 1] = (bit_read(value, i - 1) == 1 ? ONE_LOW : ZERO_LOW);
        if (bit_read(value, i - 1) == 1) {
            unsigned char bitset = 0x01 << (128 + i - pos - bits - 1) % 4;
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

int bit_read(int num, int pos) {
    return (num & ( 1 << pos )) >> pos;
}
