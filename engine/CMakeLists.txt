cmake_minimum_required(VERSION 3.20)
project(axiom_engine LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add engine cmake modules to path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(flecs)

file(GLOB_RECURSE AXIOM_ENGINE_SOURCES "src/*.c")

add_library(axiom_engine ${AXIOM_ENGINE_SOURCES})

target_include_directories(axiom_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(axiom_engine PUBLIC
    flecs::flecs
)

axiom_enable_strict_warnings(axiom_engine)