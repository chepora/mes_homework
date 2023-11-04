#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "pico/stdlib.h"

int main() {

    stdio_init_all();
	ConsoleInit();

	while(1) 
	{
		ConsoleProcess();
	}	

}
