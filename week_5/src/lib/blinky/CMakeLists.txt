
set(SRC_FILES blinky.c
              ./include/blinky.h
        )

add_library(blinky ${SRC_FILES})

target_link_libraries(blinky pico_stdlib console led)
target_include_directories(blinky PUBLIC ./include/)
