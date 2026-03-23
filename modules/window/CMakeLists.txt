
option(AXIOM_WINDOW_BACKEND_GLFW "Build GLFW window backend" ON)
option(AXIOM_WINDOW_BACKEND_SDL2 "Build SDL2 window backend" OFF)

if(AXIOM_WINDOW_BACKEND_GLFW)
    add_subdirectory(glfw)
endif()