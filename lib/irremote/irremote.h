#ifndef __IR_REMOTE_H__
#define __IR_REMOTE_H__

// void enable_ir_out(uint16_t frequency);
void mark(uint16_t time);

void space(uint16_t time);

void ir_send_raw(uint16_t buf[], uint16_t len, uint16_t freq_hz);


#endif
