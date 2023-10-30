#include "../include/blinky.h"


void blinky_init(BLINKY_VAR* ptBlinkyVar){

    led_init(&ptBlinkyVar->led_var);

}

int blinky_loop(BLINKY_VAR* ptBlinkyVar){

    while(true){

        led_blink(ptBlinkyVar->led_var.led_pin, ptBlinkyVar->led_var.blink_time_ms);

    }

}
