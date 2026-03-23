#include <axiom/windowing/axiom_glfw_window.h>

#include <GLFW/glfw3.h>

#include <stdlib.h>

static void __axiom_glfw_init__(AxisError *err)
{
    if (!glfwInit())
    {
        *err = AXIOM_WINDOW_API_EINIT;
    }
}

static axiom_window *__axiom_glfw_create_window__(int width, int height, const char *title, AxisError *err)
{
    GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!handle)
    {
        *err = AXIOM_WINDOW_ECREATE;
    }

    axiom_window *window = create_window(width, height, title, handle, err);
    if ((*err) != AXIOM_SUCCESS)
    {
        glfwDestroyWindow(handle);
        return NULL;
    }
    return window;
}

static void __axiom_glfw_destroy_window__(axiom_window **window, AxisError *err)
{
    (void)window;
}

static void __axiom_glfw_terminate__(AxisError *err)
{
    glfwTerminate();
}

axiom_window_api *axiom_create_glfw_window_api(AxisError *err)
{
    axiom_window_api *api = axiom_create_window_api("GLFW Window api", __axiom_glfw_init__, __axiom_glfw_create_window__, __axiom_glfw_destroy_window__, __axiom_glfw_terminate__, err);
    if ((*err) != AXIOM_SUCCESS)
    {
        return NULL;
    }
    return api;
}