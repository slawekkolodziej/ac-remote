#include <esp8266.h>
#include "irremote.h"

// void enable_ir_out(uint16_t frequency) {}

void mark(uint16_t time) {
  gpio_write(GPIO_LED, 1);
  if (time > 0) {
    sdk_os_delay_us(time);
  }
}

void space(uint16_t time) {
  gpio_write(GPIO_LED, 0);

  if (time > 0) {
    sdk_os_delay_us(time);
  }
}

void ir_send_raw(uint16_t buf[], uint16_t len, uint16_t frequency) {
  // set_carrier_frequence(freq_hz);

  uint16_t i;

  for (i = 0; i < len; i++) {
    if (i & 1) {
      space(buf[i]);
    } else {
      mark(buf[i]);
    }
  }

  space(0);

  // enable_ir_out(frequency);
}