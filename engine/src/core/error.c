// engine/src/core/error.c
#include <axiom/core/error.h>
#include <stdio.h>

const char *axiom_strerror(AxisError error)
{
    switch (error)
    {
    // Core errors
    case AXIOM_SUCCESS:
        return "Success";
    case AXIOM_ENOMEM:
        return "Out of memory";
    case AXIOM_EINVALID:
        return "Invalid argument";
    case AXIOM_ENOTIMPL:
        return "Not implemented";
    case AXIOM_ENOTFOUND:
        return "Not found";
    case AXIOM_EPERM:
        return "Permission denied";

    // Window errors
    case AXIOM_WINDOW_EAPI:
        return "Window API error";
    case AXIOM_WINDOW_API_EINIT:
        return "Window API does not have init function";
    case AXIOM_WINDOW_API_ETERMINATE:
        return "Window API does not have terminate function";
    case AXIOM_WINDOW_API_ECREATE:
        return "Window API does not have create window function";
    case AXIOM_WINDOW_API_EDESTROY:
        return "Window API does not have destroy window function";
    case AXIOM_WINDOW_ECREATE:
        return "Failed to create window";
    case AXIOM_WINDOW_EDESTROY:
        return "Failed to destroy window";

    // ECS errors
    case AXIOM_ECS_EWORLD:
        return "ECS world error";
    case AXIOM_ECS_EENTITY:
        return "ECS entity error";
    case AXIOM_ECS_ECOMPONENT:
        return "ECS component error";

    // Graphics errors
    case AXIOM_GFX_ECONTEXT:
        return "Graphics context error";
    case AXIOM_GFX_ESHADER:
        return "Shader compilation error";
    case AXIOM_GFX_ETEXTURE:
        return "Texture loading error";

    // Asset errors
    case AXIOM_ASSET_ELOAD:
        return "Asset loading error";
    case AXIOM_ASSET_EPARSE:
        return "Asset parsing error";
    case AXIOM_ASSET_EFORMAT:
        return "Unsupported asset format";

    default:
        return "Unknown error";
    }
}

void axiom_perror(const char *prefix, AxisError error)
{
    if (error == AXIOM_SUCCESS)
    {
        return;
    }

    if (prefix)
    {
        fprintf(stderr, "%s: %s\n", prefix, axiom_strerror(error));
    }
    else
    {
        fprintf(stderr, "%s\n", axiom_strerror(error));
    }
}