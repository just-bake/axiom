#include <axiom/windowing/axiom_glfw_window.h>

#include <stdlib.h>

static void __axiom_glfw_init__()
{
}

static axiom_window *__axiom_glfw_create_window__(int width, int height, const char *title)
{
    (void)width;
    (void)height;
    (void)title;
    return NULL;
}

static void __axiom_glfw_destroy_window__(axiom_window **window)
{
    (void)window;
}

static void __axiom_glfw_terminate__()
{
}

axiom_window_api *axiom_create_glfw_window_api(AxisError *err)
{
    axiom_window_api *api = axiom_create_window_api("GLFW Window api", __axiom_glfw_init__, __axiom_glfw_create_window__, __axiom_glfw_destroy_window__, __axiom_glfw_terminate__, err);
    if (err != AXIOM_SUCCESS)
    {
        return NULL;
    }
    return api;
}