
cmake_minimum_required(VERSION 2.8)
project(DangerousFlight)

include(FindSDL)
include(FindSDL_image)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_libraries(${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} m)
include_directories(${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR})

add_subdirectory(src)

