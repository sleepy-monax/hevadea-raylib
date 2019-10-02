#include <math.h>
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

double vector_lenght(vector_t vec)
{
    return sqrt(vec.X * vec.X + vec.Y * vec.Y);
}

vector_t vector_normalized(vector_t vec)
{
    double len = vector_lenght(vec);
    vector_t result = vec;

    result.X = vec.X / len;
    result.Y = vec.Y / len;

    return result;
}