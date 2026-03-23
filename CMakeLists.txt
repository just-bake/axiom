cmake_minimum_required(VERSION 3.20)
project(axiom 
    LANGUAGES C
    VERSION 0.1.0
    DESCRIPTION "A 2D/3D game engine with an integrated editor"
)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Compiler flags
function(axiom_enable_strict_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
        )
    endif()
endfunction()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================================
# BUILD OPTIONS
# ============================================================================

option(AXIOM_BUILD_ENGINE "Build the engine core" ON)
option(AXIOM_BUILD_EDITOR "Build the editor" ON)
option(AXIOM_BUILD_LAUNCHER "Build the editor launcher" ON)
option(AXIOM_BUILD_RUNTIME "Build the game runtime" ON)
option(AXIOM_BUILD_EXAMPLES "Build example projects" OFF)
option(AXIOM_BUILD_TESTS "Build unit tests" OFF)

# Engine-specific options
option(AXIOM_BUILD_RENDERING_MODULE "Build the rendering module" OFF)
option(AXIOM_BUILD_AUDIO_MODULE "Build the audio module" OFF)
option(AXIOM_BUILD_PHYSICS_MODULE "Build the physics module" OFF)
option(AXIOM_BUILD_SCRIPTING_MODULE "Build the scripting module" OFF)

# Window backend options

# Rendering backend options (for future use)
option(AXIOM_GRAPHICS_OPENGL "Enable OpenGL rendering" ON)
option(AXIOM_GRAPHICS_VULKAN "Enable Vulkan rendering" OFF)
option(AXIOM_GRAPHICS_DIRECTX12 "Enable DirectX 12 rendering" OFF)
option(AXIOM_GRAPHICS_METAL "Enable Metal rendering" OFF)

# Feature options
option(AXIOM_ENABLE_PROFILING "Enable profiling and statistics" ON)
option(AXIOM_ENABLE_VALIDATION "Enable debug validation" ON)
option(AXIOM_ENABLE_HOTRELOAD "Enable hot reload in editor" ON)
option(AXIOM_ENABLE_LOGGING "Enable logging system" ON)

# Scripting language options (for future use)
option(AXIOM_SCRIPT_LUA "Enable Lua scripting" OFF)
option(AXIOM_SCRIPT_CSHARP "Enable C# scripting" OFF)
option(AXIOM_SCRIPT_CPP "Enable C++ native plugins" OFF)
option(AXIOM_SCRIPT_RUST "Enable Rust/WASM scripting" OFF)

# ============================================================================
# VALIDATION
# ============================================================================

if(NOT AXIOM_BUILD_ENGINE)
    message(FATAL_ERROR "AXIOM_BUILD_ENGINE must be ON (editor and other components depend on it)")
endif()

if(AXIOM_BUILD_EDITOR AND NOT AXIOM_BUILD_WINDOW_MODULE)
    message(FATAL_ERROR "AXIOM_BUILD_EDITOR requires AXIOM_BUILD_WINDOW_MODULE")
endif()

if(AXIOM_BUILD_EDITOR AND NOT AXIOM_BUILD_LAUNCHER)
    message(WARNING "AXIOM_BUILD_EDITOR is ON but AXIOM_BUILD_LAUNCHER is OFF - editor won't be executable")
endif()

# ============================================================================
# CONFIGURATION DEFINES
# ============================================================================

add_compile_definitions(
    $<$<BOOL:${AXIOM_ENABLE_PROFILING}>:AXIOM_ENABLE_PROFILING>
    $<$<BOOL:${AXIOM_ENABLE_VALIDATION}>:AXIOM_ENABLE_VALIDATION>
    $<$<BOOL:${AXIOM_ENABLE_HOTRELOAD}>:AXIOM_ENABLE_HOTRELOAD>
    $<$<BOOL:${AXIOM_ENABLE_LOGGING}>:AXIOM_ENABLE_LOGGING>
)

# ============================================================================
# ENGINE CORE
# ============================================================================

if(AXIOM_BUILD_ENGINE)
    add_subdirectory(engine)
endif()

# ============================================================================
# MODULES
# ============================================================================

if(AXIOM_BUILD_ENGINE)
    add_subdirectory(modules)
endif()

# ============================================================================
# EDITOR
# ============================================================================

if(AXIOM_BUILD_EDITOR)
    if(NOT AXIOM_BUILD_ENGINE)
        message(FATAL_ERROR "Editor requires engine to be built")
    endif()
    if(NOT AXIOM_BUILD_WINDOW_MODULE)
        message(FATAL_ERROR "Editor requires window module to be built")
    endif()
    add_subdirectory(editor)
endif()

# ============================================================================
# LAUNCHER (EDITOR ENTRY POINT)
# ============================================================================

if(AXIOM_BUILD_LAUNCHER)
    if(NOT AXIOM_BUILD_EDITOR)
        message(WARNING "Launcher requires editor - set AXIOM_BUILD_EDITOR=ON")
    else()
        add_subdirectory(launcher)
    endif()
endif()

# ============================================================================
# RUNTIME (GAME ENTRY POINT)
# ============================================================================

if(AXIOM_BUILD_RUNTIME)
    if(NOT AXIOM_BUILD_ENGINE)
        message(WARNING "Runtime requires engine - set AXIOM_BUILD_ENGINE=ON")
    else()
        add_subdirectory(runtime)
    endif()
endif()

# ============================================================================
# EXAMPLES
# ============================================================================

if(AXIOM_BUILD_EXAMPLES)
    if(NOT AXIOM_BUILD_ENGINE)
        message(WARNING "Examples require engine to be built")
    else()
        add_subdirectory(examples)
    endif()
endif()

# ============================================================================
# TESTS
# ============================================================================

if(AXIOM_BUILD_TESTS)
    enable_testing()
    if(NOT AXIOM_BUILD_ENGINE)
        message(WARNING "Tests require engine to be built")
    else()
        add_subdirectory(tests)
    endif()
endif()

# ============================================================================
# BUILD SUMMARY
# ============================================================================

message(STATUS "")
message(STATUS "========== Axiom Engine Build Configuration ==========")
message(STATUS "")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "Compiler: ${CMAKE_C_COMPILER_ID}")
message(STATUS "")
message(STATUS "--- Core Components ---")
message(STATUS "Engine:              ${AXIOM_BUILD_ENGINE}")
message(STATUS "Editor:              ${AXIOM_BUILD_EDITOR}")
message(STATUS "Editor Launcher:     ${AXIOM_BUILD_LAUNCHER}")
message(STATUS "Game Runtime:        ${AXIOM_BUILD_RUNTIME}")
message(STATUS "Examples:            ${AXIOM_BUILD_EXAMPLES}")
message(STATUS "Tests:               ${AXIOM_BUILD_TESTS}")
message(STATUS "")
message(STATUS "--- Engine Modules ---")
message(STATUS "Window Module:       ${AXIOM_BUILD_WINDOW_MODULE}")
message(STATUS "Rendering Module:    ${AXIOM_BUILD_RENDERING_MODULE}")
message(STATUS "Audio Module:        ${AXIOM_BUILD_AUDIO_MODULE}")
message(STATUS "Physics Module:      ${AXIOM_BUILD_PHYSICS_MODULE}")
message(STATUS "Scripting Module:    ${AXIOM_BUILD_SCRIPTING_MODULE}")
message(STATUS "")
message(STATUS "--- Window Backends ---")
message(STATUS "GLFW Backend:        ${AXIOM_WINDOW_BACKEND_GLFW}")
message(STATUS "SDL2 Backend:        ${AXIOM_WINDOW_BACKEND_SDL2}")
message(STATUS "")
message(STATUS "--- Graphics Backends ---")
message(STATUS "OpenGL:              ${AXIOM_GRAPHICS_OPENGL}")
message(STATUS "Vulkan:              ${AXIOM_GRAPHICS_VULKAN}")
message(STATUS "DirectX 12:          ${AXIOM_GRAPHICS_DIRECTX12}")
message(STATUS "Metal:               ${AXIOM_GRAPHICS_METAL}")
message(STATUS "")
message(STATUS "--- Scripting Languages ---")
message(STATUS "Lua:                 ${AXIOM_SCRIPT_LUA}")
message(STATUS "C#:                  ${AXIOM_SCRIPT_CSHARP}")
message(STATUS "C++ Plugins:         ${AXIOM_SCRIPT_CPP}")
message(STATUS "Rust/WASM:           ${AXIOM_SCRIPT_RUST}")
message(STATUS "")
message(STATUS "--- Features ---")
message(STATUS "Profiling:           ${AXIOM_ENABLE_PROFILING}")
message(STATUS "Validation:          ${AXIOM_ENABLE_VALIDATION}")
message(STATUS "Hot Reload:          ${AXIOM_ENABLE_HOTRELOAD}")
message(STATUS "Logging:             ${AXIOM_ENABLE_LOGGING}")
message(STATUS "")
message(STATUS "========================================================")
message(STATUS "")