
project(DangerousFlight)
cmake_minimum_required(VERSION 2.8)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)


