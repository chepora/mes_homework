# Blinky on the Adafruit Trinket M0

The [Adafruit Trinket M0](https://www.adafruit.com/product/3500) features the ATSAMD21E18A ARM Cortex-M0+.

The board features two user LEDs besides the power LED:
    - the red LED D13 which is connected to PA10
    - APA102 which is a RGB DotStar LED

Unfortunately, there is only one reset button - but enough free GPIO pins to connect a button.
    - PA06 lies on PIN 4 right next to the GND pin

