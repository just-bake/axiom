#pragma once
#include <axiom/core/error.h>
#include <stdbool.h>

typedef struct axiom_window axiom_window;
typedef struct axiom_window_api axiom_window_api;

typedef void (*AXIOM_WINDOW_API_INIT_FUNCTION)(void);
typedef axiom_window *(*AXIOM_WINDOW_API_CREATE_WINDOW_FUNCTION)(int width, int height, const char *title);
typedef void (*AXIOM_WINDOW_API_DESTROY_WINDOW_FUNCTION)(axiom_window **window);
typedef void (*AXIOM_WINDOW_API_TERMINATE_FUNCTION)(void);

axiom_window_api *axiom_create_window_api(const char *name,
                                          AXIOM_WINDOW_API_INIT_FUNCTION init,
                                          AXIOM_WINDOW_API_CREATE_WINDOW_FUNCTION create_window, AXIOM_WINDOW_API_DESTROY_WINDOW_FUNCTION destroy_window,
                                          AXIOM_WINDOW_API_TERMINATE_FUNCTION terminate,
                                          AxisError *err);

void axiom_destroy_window_api(axiom_window_api **api, AxisError *err);

axiom_window *axiom_create_window(axiom_window_api *api, int width, int height, char *title, AxisError *err);
void axiom_destroy_window(axiom_window_api *api, axiom_window **window, AxisError *err);

void axoim_validate_axiom_window_api(axiom_window_api *window_api, AxisError *err);