set(SRC_FILES led.c
              ./include/led.h
        )

add_library(led ${SRC_FILES})


target_link_libraries(led pico_stdlib)
target_include_directories(led PUBLIC ./include/)
