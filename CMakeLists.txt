

cmake_minimum_required(VERSION 2.8)
project(CA80W)

set(CMAKE_LD_FLAGS -mwindows)
include_directories(${PROJECT_SOURCE_DIR}/include)
if(WIN32)
    link_libraries(mingw32 SDLmain SDL SDL_image m)
else(WIN32)
    link_libraries(SDL SDL_image m)
endif(WIN32)
add_subdirectory(src)

