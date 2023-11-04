// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "led.h"

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[]);
static eCommandResult_T ConsoleCommandGetPin(const char buffer[]);
static eCommandResult_T ConsoleCommandGetPinFunctionAsStr(const uint8_t req_pin, enum gpio_function * gpio_function, char * gpio_function_str);
static eCommandResult_T ConsoleCommandBlinkLED(const char buffer[]);
static eCommandResult_T ConsoleCommandGetTurtle(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", ConsoleCommandVer, HELP("Get the version string")},
    {"int", ConsoleCommandParamExampleInt16, HELP("How to get a signed int16 from params list: int -321")},
    {"u16h", ConsoleCommandParamExampleHexUint16, HELP("How to get a hex u16 from the params list: u16h aB12")},
	{"gpio", ConsoleCommandGetPin, HELP("How to get current gpio function pin x uint8: gpio 12")},
	{"led", ConsoleCommandBlinkLED, HELP("How to blink the default board LED: led")},
	{"turtle", ConsoleCommandGetTurtle, HELP("How to get a turtle: turtle")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}


const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}

#define MAX_PIN              21

static eCommandResult_T ConsoleCommandGetPin(const char buffer[]){

	uint8_t parameterPin;

	eCommandResult_T result = COMMAND_SUCCESS;

	
	char *gpio_function_str;
	enum gpio_function gpio_function;

	result = ConsoleReceiveParamUint8(buffer, 1, &parameterPin);

	if ( COMMAND_SUCCESS == result )
	{
		if(parameterPin < MAX_PIN){

			result = ConsoleCommandGetPinFunctionAsStr(parameterPin, &gpio_function, gpio_function_str);
			
		}
		ConsoleIoSendString("You asked for GPIO pin ");
		ConsoleSendParamUint8(parameterPin);
		ConsoleIoSendString(STR_ENDLINE);
		ConsoleIoSendString("Pin is currently ");
		ConsoleIoSendString(gpio_function_str);
		ConsoleSendParamUint8(gpio_function);
		ConsoleIoSendString(STR_ENDLINE);
	}

	return result;

}

static char gpio_pin_function_str_0 [] = {"configured as XIP.\0"};
static char gpio_pin_function_str_1 [] = {"configured as SPI.\0"};
static char gpio_pin_function_str_2 [] = {"configured as UART.\0"};
static char gpio_pin_function_str_3 [] = {"configured as I2C.\0"};
static char gpio_pin_function_str_4 [] = {"configured as PWM.\0"};
static char gpio_pin_function_str_5 [] = {"configured as SIO.\0"};
static char gpio_pin_function_str_6 [] = {"configured as PIO0.\0"};
static char gpio_pin_function_str_7 [] = {"configured as PIO1.\0"};
static char gpio_pin_function_str_8 [] = {"configured as GPCK.\0"};
static char gpio_pin_function_str_9 [] = {"configured as USB.\0"};
static char gpio_pin_function_str_10 [] = {"not configured or could not be found.\0"};


#define MAX_GPIO_STR 11

char * gpio_pin_function_str[MAX_GPIO_STR ] = { gpio_pin_function_str_0, gpio_pin_function_str_1, gpio_pin_function_str_2, gpio_pin_function_str_3,
			   							        gpio_pin_function_str_4, gpio_pin_function_str_5, gpio_pin_function_str_6, gpio_pin_function_str_7,
												gpio_pin_function_str_8, gpio_pin_function_str_9, gpio_pin_function_str_10 };

static eCommandResult_T ConsoleCommandGetPinFunctionAsStr(const uint8_t req_pin, enum gpio_function * gpio_function, char * gpio_function_str)
{
	eCommandResult_T result = COMMAND_SUCCESS;
	
	enum gpio_function current_gpio_function;
	current_gpio_function = gpio_get_function(req_pin);
	*gpio_function = current_gpio_function;

	char *chosen_str;

	if(0 <= current_gpio_function < 10)
	{
		gpio_function_str = gpio_pin_function_str[current_gpio_function];

	}else if(current_gpio_function == 0x1f)
	{
		gpio_function_str = gpio_pin_function_str[10];

	}else
	{
		result = COMMAND_PARAMETER_ERROR;
	}

	return result;

}



static eCommandResult_T ConsoleCommandBlinkLED(const char buffer[]){

	eCommandResult_T result = COMMAND_SUCCESS;

	// try to find deafault led for this board
	uint8_t LED_pin  = PICO_DEFAULT_LED_PIN;


	LED_VAR consoleLED_var = {.led_pin = PICO_DEFAULT_LED_PIN, .blink_time_ms = 250};

	led_init(&consoleLED_var);
	led_blink(&consoleLED_var);

	return result;

}


static char turtle_str_1 [] = {"                _,.---.---.---.--.._  "};
static char turtle_str_2 [] = {"            _.-' `--.`---.`---'-. _,`--.._ "};
static char turtle_str_3 [] = {"           /`--._ .'.     `.     `,`-.`-._\\"};
static char turtle_str_4 [] = {"          ||   \\  `.`---.__`__..-`. ,'`-.//"};
static char turtle_str_5 [] = {"     _  ,`\\ `-._\\   \\    `.    `_.-`-._,``-."};
static char turtle_str_6 [] = {"  ,`   `-_ \\// `-.`--.\\    _\\_.-'\\__.-`-.`-._`."};
static char turtle_str_7 [] = {" (_.o> ,--. `._/'--.-`,--`  \\_.-'       \\`-._ \\"};
static char turtle_str_8 [] = {"  `---'    `._ `---._/__,----`           `-. `-\\"};
static char turtle_str_9 [] = {"            /_, ,  _..-'                    `-._\\"};
static char turtle_str_10 [] = {"            \\_, \\// ._("};
static char turtle_str_11 [] = {"             \\_, \\// ._\\"};
static char turtle_str_12 [] = {"              `._,\\// ._\\"};
static char turtle_str_13 [] = {"                `._// .//`-._"};
static char turtle_str_14 [] = {"                  `-._-_-_.-'"};
static char turtle_str_15 [] = {"stolen from https://www.asciiart.eu/animals/other-water by lgb"};

#define MAX_TURTLE_LENGTH 15

char * turtle_str[MAX_TURTLE_LENGTH] = { turtle_str_1, turtle_str_2, turtle_str_3, turtle_str_4, turtle_str_5,
			   							 turtle_str_6, turtle_str_7, turtle_str_8, turtle_str_9, turtle_str_10,
			   						     turtle_str_11, turtle_str_12, turtle_str_13, turtle_str_14, turtle_str_15};

static eCommandResult_T ConsoleCommandGetTurtle(const char buffer[]){

	eCommandResult_T result = COMMAND_SUCCESS;

	if ( COMMAND_SUCCESS == result )
	{	
		for (uint8_t i = 0; i < MAX_TURTLE_LENGTH; i++)
		{
			ConsoleIoSendString(turtle_str[i]);
			ConsoleIoSendString(STR_ENDLINE);
		}

	}
	return result;
}

