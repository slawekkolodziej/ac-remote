#ifndef LGAC_h
#define LGAC_h
#include <Arduino.h>

#define first_byte 136 //b10001000

#define state_on 0
#define state_off 24 //b11000
#define state_change_mode 1

#define mode_heating 4 //b100
#define mode_auto 3 //b011
#define mode_dehumidification 1 //b001
#define mode_cooling 0
#define mode_none 0

#define temperature_offset 15

#define fan_1 1
#define fan_2 0
#define fan_3 2
#define fan_4 4 //b100
#define fan_none 5 //b101

#define first_high 8271
#define first_low 4298
#define zero_and_one_high 439
#define zero_low 647
#define one_low 1709

#define LGAC_buffer_size 59

class LGAC
{
	public:
		// fields
		unsigned int codes[LGAC_buffer_size];
		// methods
		// setter
		LGAC();

		void setMode(int _mode, int _fan, int _temperature,int _state);
		// debugging
		void debug();
	private:
		// fields
		byte crc;
		// methods
		void FillBuffer(byte _pos, byte _bit, byte _value);
};

#endif;
