set(SRC_FILES console.c
              ./include/console.h
              consoleCommands.c
              ./include/consoleCommands.h
              consoleIo.c
              ./include/consoleIo.h
        )

add_library(console ${SRC_FILES})

target_link_libraries(console pico_stdlib)
target_include_directories(console PUBLIC ./include/)
