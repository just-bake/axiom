
cmake_minimum_required(VERSION 3.20)
project(axiom_window_glfw_module LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(glfw)

file(GLOB_RECURSE AXIOM_WINDOW_GLFW_MODULE_SOURCES "src/*.c")

add_library(axiom_window_glfw_module ${AXIOM_WINDOW_GLFW_MODULE_SOURCES})

target_include_directories(axiom_window_glfw_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(axiom_window_glfw_module PUBLIC
    axiom_engine
    glfw
)