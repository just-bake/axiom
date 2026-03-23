
option(AXIOM_BUILD_WINDOW_MODULE "Build the window module" ON)

if(AXIOM_BUILD_WINDOW_MODULE)
    add_subdirectory(window)
endif()