#ifndef LED_H__
#define LED_H_

#include <stdint.h>
#include "pico/stdlib.h"

typedef struct LED_VAR {

    uint8_t     led_pin;
    uint32_t    blink_time_ms;

} LED_VAR;

void led_init(LED_VAR* ptLedVar);
void led_blink(LED_VAR* ptLedVar);

#endif