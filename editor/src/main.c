#include <axiom/engine.h>
#include <axiom/windowing/axiom_glfw_window.h>

#include <stdlib.h>

int main()
{
    AxisError err;
    axiom_window_api *api = axiom_create_glfw_window_api(&err);
    if (err != AXIOM_SUCCESS)
    {
        axiom_perror("WINDOW API NOT INIT", err);
        return EXIT_FAILURE;
    }

    axiom_create_window(api, 800, 600, "test", &err);
    if (err != AXIOM_SUCCESS)
    {
        axiom_perror("WINDOW API NOT INIT", err);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}