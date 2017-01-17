#include <esp8266.h>
#include "irremote.h"

uint16_t delay;

void enable_ir_out(uint16_t frequency) {
  delay = 1000 / frequency;
}

void mark(uint16_t time) {
  uint32_t start = sdk_system_get_time();

  while(sdk_system_get_time() - start < time) {
    gpio_write(GPIO_LED, 1);
    sdk_os_delay_us(delay);
    gpio_write(GPIO_LED, 0);
    sdk_os_delay_us(delay);
  }
}

void space(uint16_t time) {
  gpio_write(GPIO_LED, 0);

  if (time > 0) {
    sdk_os_delay_us(time);
  }
}

void ir_send_raw(uint16_t buf[], uint16_t len, uint16_t frequency) {
  enable_ir_out(frequency);

  uint16_t i;
  for (i = 0; i < len; i++) {
    if (i & 1) {
      space(buf[i]);
    } else {
      mark(buf[i]);
    }
  }

  space(0);
}