cmake_minimum_required(VERSION 3.20)
project(axiom_editor LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE AXIOM_EDITOR_SOURCES "src/*.c")

add_executable(axiom_editor ${AXIOM_EDITOR_SOURCES})

target_include_directories(axiom_editor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(axiom_editor PUBLIC
    axiom_engine
    axiom_window_glfw_module
)