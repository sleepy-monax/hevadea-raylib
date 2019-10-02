#pragma once

typedef struct
{
    double X;
    double Y;
} vector_t;

vector_t vector_X(vector_t vec);

vector_t vector_Y(vector_t vec);

vector_t vector_scale(vector_t vec, double scale);

double vector_lenght(vector_t vec);

vector_t vector_normalized(vector_t vec);
