#pragma once

#include <axiom/core/error.h>
#include <axiom/windowing/window.h>

#include <stdio.h>

#define AXIOM_CALL(call, msg)                                \
    do                                                       \
    {                                                        \
        (call);                                              \
        if (err != AXIOM_SUCCESS)                            \
        {                                                    \
            fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__); \
            axiom_perror((msg), err);                        \
            exit(EXIT_FAILURE);                              \
        }                                                    \
    } while (0)

#define AXIOM_CHECK_ERR(msg)                                 \
    do                                                       \
    {                                                        \
        if (err != AXIOM_SUCCESS)                            \
        {                                                    \
            fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__); \
            axiom_perror((msg), err);                        \
            return EXIT_FAILURE;                             \
        }                                                    \
    } while (0)
