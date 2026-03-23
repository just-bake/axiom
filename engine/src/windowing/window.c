#include <axiom/windowing/window.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct axiom_window
{
    void *handle;
    int width;
    int height;
    char title;
};

struct axiom_window_api
{
    char *name;
    AXIOM_WINDOW_API_INIT_FUNCTION init;
    AXIOM_WINDOW_API_CREATE_WINDOW_FUNCTION create_window;
    AXIOM_WINDOW_API_DESTROY_WINDOW_FUNCTION destroy_window;
    AXIOM_WINDOW_API_TERMINATE_FUNCTION terminate;
};

axiom_window_api *axiom_create_window_api(const char *name,
                                          AXIOM_WINDOW_API_INIT_FUNCTION init,
                                          AXIOM_WINDOW_API_CREATE_WINDOW_FUNCTION create_window, AXIOM_WINDOW_API_DESTROY_WINDOW_FUNCTION destroy_window,
                                          AXIOM_WINDOW_API_TERMINATE_FUNCTION terminate,
                                          AxisError *err)
{
    if (!name)
    {
        *err = AXIOM_EINVALID;
        return NULL;
    }

    axiom_window_api *api = (axiom_window_api *)malloc(sizeof(axiom_window_api));
    if (!api)
    {
        *err = AXIOM_ENOMEM;
        return NULL;
    }

    api->name = (char *)malloc(strlen(name) + 1);
    if (!api->name)
    {
        free(api);
        *err = AXIOM_ENOMEM;
        return NULL;
    }
    strcpy(api->name, name);

    api->init = init;
    api->create_window = create_window;
    api->destroy_window = destroy_window;
    api->terminate = terminate;

    *err = AXIOM_SUCCESS;
    return api;
}

void axiom_destroy_window_api(axiom_window_api **api, AxisError *err)
{
    if (!api || !(*api))
    {
        *err = AXIOM_EINVALID;
        return;
    }

    if ((*api)->name)
    {
        free((*api)->name);
    }

    free(*api);
    *api = NULL;
}

axiom_window *axiom_create_window(axiom_window_api *api, int width, int height, char *title, AxisError *err)
{
    if (!api)
    {
        *err = AXIOM_EINVALID;
        return NULL;
    }

    axiom_window *window = api->create_window(width, height, title);
    if (!window)
    {
        *err = AXIOM_WINDOW_ECREATE;
        return NULL;
    }

    return window;
}

void axiom_destroy_window(axiom_window_api *api, axiom_window **window, AxisError *err)
{
    if (!window | !(*window) || !api)
    {
        *err = AXIOM_EINVALID;
        return;
    }

    axoim_validate_axiom_window_api(api, err);
    if (err != AXIOM_SUCCESS)
    {
        return;
    }

    api->destroy_window(window);
    if ((*window))
        *err = AXIOM_WINDOW_EDESTROY;
    return;
}

void axoim_validate_axiom_window_api(axiom_window_api *window_api, AxisError *err)
{
    if (!window_api)
        *err = AXIOM_EINVALID;

    if (!window_api->init)
        *err = AXIOM_WINDOW_API_EINIT;

    if (!window_api->terminate)
        *err = AXIOM_WINDOW_API_ETERMINATE;

    if (!window_api->create_window)
        *err = AXIOM_WINDOW_API_ECREATE;

    if (!window_api->destroy_window)
        *err = AXIOM_WINDOW_API_EDESTROY;
}