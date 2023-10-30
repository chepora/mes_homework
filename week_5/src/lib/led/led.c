#include "../include/led.h"

#define ON  1
#define OUT 0


void led_init(LED_VAR* ptLedVar){

    gpio_init(ptLedVar->led_pin);
    gpio_set_dir(ptLedVar->led_pin, GPIO_OUT);

}

void led_blink(uint8_t led_pin, uint32_t blink_time_ms){

    gpio_put(led_pin, ON);
    sleep_ms(blink_time_ms);
    gpio_put(led_pin, OUT);
    sleep_ms(blink_time_ms);
    
}