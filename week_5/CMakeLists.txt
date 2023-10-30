cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

pico_sdk_init()

project(console_poc)

add_subdirectory(src)

target_link_libraries(console_poc pico_stdlib hardware_gpio)
