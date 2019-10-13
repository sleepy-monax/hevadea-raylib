#pragma once

#include <hevadea/direction.h>

typedef struct
{
    double X;
    double Y;
} vector_t;

vector_t vector_X(vector_t vec);

vector_t vector_Y(vector_t vec);

vector_t vector_scale(vector_t vec, double scale);

vector_t vector_reverse(vector_t vec);

double vector_lenght(vector_t vec);

vector_t vector_normalized(vector_t vec);

vector_t vector_add(vector_t left, vector_t right);

direction_t vector_to_direction(vector_t vec);
