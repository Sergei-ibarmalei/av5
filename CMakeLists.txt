cmake_minimum_required(VERSION 3.16.3)
project(prog)
set(SOURCES
    sdlcore/sdlcore.c
    gamecore/gamecore.c
    inits/inits.c
    random/rand.c
    main.c)

SET(CMAKE_C_COMPILER /usr/bin/clang)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2
    SDL2_image
    SDL2_ttf)

target_compile_options(${PROJECT_NAME} PRIVATE
$<$<NOT:$<C_COMPILER_ID:MSVC>>: -O3 -Wall -Wextra -Wpedantic>)