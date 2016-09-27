#include "LGAC.h"



void lgac_set_mode(char* mode, int _fan, int _temperature, int _state) {
    int mode = ;

    codes[0] = first_high;
    codes[1] = first_low;
    crc = 0;

    fill_buffer(0, 8, first_byte);
    fill_buffer(8, 5, _state);

    if(_state==state_off)
        fill_buffer(13, 3, mode_none);
    else
        fill_buffer(13, 3, get_mode(mode));
    if(_state==state_off)
        fill_buffer(16, 4, 0);
    else
        fill_buffer(16,4,(byte)_temperature-temperature_offset);
    fill_buffer(20,1,0); //jet

    if (_state==state_off) {
        fill_buffer(21,3,fan_none);
    } else {
        fill_buffer(21,3,_fan);
    }
    fill_buffer(24,4,crc);
    codes[lgac_buffer_size-1] = zero_and_one_high;
}

int get_mode(char* modeName) {
    switch (modeName) {
        case 'heating':
            return 4; //b100
        case 'auto':
            return 3; //b011
        case 'fan':
            return 2;
        case 'dehumidification':
            return 1; //b001
        case 'cooling':
            return 0;
        default:
        case 'none':
            return 0;

    }
}

int get_state(char* stateName) {
    switch (stateName) {
        case 'on':
            return 0;
        // case 'change_mode' 1:
        case 'off':
        default:
            return 24; //b11000
    }
}

int get_fan_speed(fanSpeed) {
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

int get_temperature(temp) {
    return temp + 15;
}

void fill_buffer(byte _pos, byte _bits, byte _value){
    for (int i=_bits;i>0;i--){
        codes[2+2*(_pos+_bits-i)] = zero_and_one_high;
        codes[2+2*(_pos+_bits-i)+1] = (bitRead(_value,i-1)==1?one_low:zero_low);
        if(bitRead(_value,i-1)==1){
            byte bitset = 0;
            bitSet(bitset,(128+i-_pos-_bits-1)%4);
            crc = crc + bitset;
        }
    }
}
void lgac_debug()
{
    for(byte i=0;i<lgac_buffer_size;i++){
        Serial.print(codes[i],DEC);
        Serial.print(",");
    }
}