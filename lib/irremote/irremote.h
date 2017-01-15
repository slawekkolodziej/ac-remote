#ifndef __IR_REMOTE_H__
#define __IR_REMOTE_H__

void enable_ir_out(uint16_t frequency);

void ir_remote_send_raw(uint16_t buf[], uint16_t len, uint16_t freq_hz);

#endif
