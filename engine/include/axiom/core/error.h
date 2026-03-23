// engine/include/engine/error.h
#pragma once

// Generic error codes
typedef enum
{
    AXIOM_SUCCESS = 0,

    // Core engine errors (0-999)
    AXIOM_ENOMEM = 1,
    AXIOM_EINVALID = 2,
    AXIOM_ENOTIMPL = 3,
    AXIOM_ENOTFOUND = 4,
    AXIOM_EPERM = 5,

    // Window errors (1000-1999)
    AXIOM_WINDOW_EAPI = 1000,
    AXIOM_WINDOW_API_EINIT = 1001,
    AXIOM_WINDOW_API_ETERMINATE = 1002,
    AXIOM_WINDOW_API_ECREATE = 1003,
    AXIOM_WINDOW_API_EDESTROY = 1004,
    AXIOM_WINDOW_ECREATE = 1005,
    AXIOM_WINDOW_EDESTROY = 1006,

    // ECS errors (2000-2999)
    AXIOM_ECS_EWORLD = 2000,
    AXIOM_ECS_EENTITY = 2001,
    AXIOM_ECS_ECOMPONENT = 2002,

    // Graphics errors (3000-3999)
    AXIOM_GFX_ECONTEXT = 3000,
    AXIOM_GFX_ESHADER = 3001,
    AXIOM_GFX_ETEXTURE = 3002,

    // Asset errors (4000-4999)
    AXIOM_ASSET_ELOAD = 4000,
    AXIOM_ASSET_EPARSE = 4001,
    AXIOM_ASSET_EFORMAT = 4002,
} AxisError;

// Get human-readable error message
const char *axiom_strerror(AxisError error);

// Print error to stderr
void axiom_perror(const char *prefix, AxisError error);
