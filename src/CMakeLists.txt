
add_executable(DF df.c sprite.c alphachannel.c spec.c bottom.c environment.c gear.c missle.c explode.c SDL_rotozoom.c player.c ui.c)

target_link_libraries(DF ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})

add_custom_command(TARGET DF PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:DF>/res)

