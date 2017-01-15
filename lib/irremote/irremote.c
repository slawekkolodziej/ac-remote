
void enable_ir_out(uint16_t frequency) {
  
}

void ir_remote_send_raw(uint16_t buf[], uint16_t len, uint16_t frequency) {
  enable_ir_out(frequency);
}