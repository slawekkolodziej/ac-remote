#include "LGAC.h"
LGAC::LGAC() {
	Serial.print("initialized!");
};

void LGAC::setMode(
	int _mode,
	int _fan,
	int _temperature,
	int _state)
{
	// set sync
	codes[0] = first_high;
	codes[1] = first_low;
	crc = 0;
	FillBuffer(0,8,first_byte);
	FillBuffer(8,5,_state);
	if(_state==state_off)
		FillBuffer(13,3,mode_none);
	else
		FillBuffer(13,3,_mode);
	if(_state==state_off)
		FillBuffer(16,4,0);
	else
		FillBuffer(16,4,(byte)_temperature-temperature_offset);
	FillBuffer(20,1,0); //jet
	if(_state==state_off)
		FillBuffer(21,3,fan_none);
	else
		FillBuffer(21,3,_fan);
	FillBuffer(24,4,crc);
	codes[LGAC_buffer_size-1] = zero_and_one_high;
}

void LGAC::FillBuffer(byte _pos, byte _bits, byte _value){
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
void LGAC::debug()
{
	for(byte i=0;i<LGAC_buffer_size;i++){
		Serial.print(codes[i],DEC);
		Serial.print(",");
	}
}