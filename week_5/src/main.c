#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "blinky.h"
#include "console.h"
#include "pico/stdlib.h"

int main() {

    const uint8_t LED_PIN           = 13;
    const uint32_t BLINK_TIME_MS    = 1000;

    BLINKY_VAR used_blinky_params = {
        .led_var       = {.led_pin = LED_PIN, .blink_time_ms = BLINK_TIME_MS},
    };

    //blinky_init(&used_blinky_params);
    //blinky_loop(&used_blinky_params);

    stdio_init_all();
	ConsoleInit();

	while(1) 
	{
		ConsoleProcess();
	}	

}
