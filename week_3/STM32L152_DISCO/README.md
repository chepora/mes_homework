# Blinky on the STM32L152 Discovery Board

This program lets the green LED blink and uses the user button as input, which turns on the blue LED.

The [STM32L152 Discovery Board](https://www.st.com/en/evaluation-tools/32l152cdiscovery.html) features the STM32L152RCT6.

This program was developed and compiled by using STM32CubeIE 1.13.2

The board features two user LEDs besides the power LED:
    - green LED `LD3` connected to the I/O `PB7` of the STM32L152RCT6.
    - blue LED `LD4` connected to the I/O `PB6` of the STM32L152RCT6.

Besides the reset button there is one user button
    -  `B1 USER` is connected to the I/O `PA0` of the STM32L152RCT6

Using the HAL one first needs to enable the GPIO in `stm32l1xx_hal_conf.h`

```
#define HAL_GPIO_MODULE_ENABLED
```

Further, the GPIO clocks need to be initialised, e.g.:
```
  __HAL_RCC_GPIOB_CLK_ENABLE();
```

To configure the pins one can make use of the provided `GPIO_InitTypeDef` and for example set for the greed LED LD3:
```
static GPIO_InitTypeDef GPIO_InitStruct;

GPIO_InitStruct.Pin     = GPIO_PIN_7;
GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull    = GPIO_PULLUP;
GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_VERY_HIGH;

// And initialise it
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
```

The above defines mask the register. So let us look at the following struct:
```
typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00      */
  __IO uint32_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04      */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08      */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C      */
  __IO uint32_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10      */
  __IO uint32_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14      */
  __IO uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,        Address offset: 0x18      */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C      */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function register,            Address offset: 0x20-0x24 */
} GPIO_TypeDef;
```
This struct shows the register for one GPIO pin bank. For the bank B for the pin above that would be `GPIOB`, which lies at
```
GPIOB_BASE = AHBPERIPH_BASE + 0x0000 0400UL = PERIPH_BASE +  0x0002 0000 UL + 0x0000 0400UL = 0x4000 0000UL + 0x0002 0000UL + 0x0000 0400UL = 0x4004 0400UL
```
This adress can be seen is the start of the above struct.
It can be also found in the Memory map, 5. Memory mapping Fig.9, in the [datasheet](https://www.st.com/resource/en/datasheet/stm32l151cc.pdf)

## TLDR
1.What are the hardware registers that cause the LED to turn on and off?

  For the blue LED thats BSRR at Inside at offset `0x18` in `GPIOB` at 0x4004 0400UL
  
2.What are the registers that you read in order to find out the state of the button?

 For the B1 User Button thats the input data register `IDR` at offset 0x10 inside pin bank A which starts at 0x4004 0000UL
 
3.Can you read the register directly and see the button change in a debugger or by printing out thes value of the memory at the register’s address?

 Yes by looking at the above register.


