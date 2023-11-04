add_subdirectory(lib)

add_executable(console_poc
    main.c)

target_link_libraries(console_poc pico_stdlib led console)

# enable usb output, disable uart output
pico_enable_stdio_usb(console_poc 0)
pico_enable_stdio_uart(console_poc 1)

pico_add_extra_outputs(console_poc)
