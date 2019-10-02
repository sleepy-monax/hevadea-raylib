#include <hevadea/vector.h>

vector_t vector_X(vector_t vec)
{
    return (vector_t){vec.X, 0};
}

vector_t vector_Y(vector_t vec)
{
    return (vector_t){0, vec.Y};
}

vector_t vector_scale(vector_t vec, double scale)
{
    return (vector_t){vec.X * scale, vec.Y * scale};
}