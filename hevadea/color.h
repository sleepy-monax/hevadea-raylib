#pragma once

#include <stdint.h>

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} color_t;

#define COLOR_WHITE \
    (color_t) { 255, 255, 255, 255 }

#define COLOR_GRAY \
    (color_t) { 125, 125, 125, 255 }

#define COLOR_BLACK \
    (color_t) { 0, 0, 0, 255 }

#define COLOR_RED \
    (color_t) { 255, 0, 0, 255 }

#define COLOR_GREEN \
    (color_t) { 0, 255, 0, 255 }

#define COLOR_BLUE \
    (color_t) { 0, 0, 255, 255 }

#define COLOR_YELLOW \
    (color_t) { 255, 255, 0, 255 }

#define COLOR_MAGENTA \
    (color_t) { 255, 0, 255, 255 }

#define COLOR_CYAN \
    (color_t) { 0, 255, 255, 255 }
