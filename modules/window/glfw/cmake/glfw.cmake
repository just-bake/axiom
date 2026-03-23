include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)