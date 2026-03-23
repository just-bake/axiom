#include <axiom/engine.h>
#include <axiom/windowing/axiom_glfw_window.h>

#include <stdlib.h>

int main()
{
    AxisError err;
    axiom_window_api *api = axiom_create_glfw_window_api(&err);

    AXIOM_CALL(axiom_init_window_api(api, &err), "WINDOW API NOT INITIALIZED");
    AXIOM_CALL(axiom_create_window(api, 800, 600, "test", &err), "WINDOW CREATION FAILED");
    AXIOM_CALL(axiom_terminate_window_api(api, &err), "COULD NOT TERMINATE");
    AXIOM_CALL(axiom_destroy_window_api(&api, &err), "COULD NOT DESTROY WINDOW API");

    return EXIT_SUCCESS;
}