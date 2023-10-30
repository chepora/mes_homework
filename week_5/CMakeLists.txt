cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(console_poc)

pico_sdk_init()

set(PICO_BOARD "adafruit_feather_rp2040")

add_subdirectory(src)

target_link_libraries(console_poc pico_stdlib hardware_gpio)
