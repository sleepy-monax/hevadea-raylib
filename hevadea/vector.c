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

vector_t vector_reverse(vector_t vec)
{
    return (vector_t){-vec.X, -vec.Y};
}

vector_t vector_add(vector_t left, vector_t right)
{
    return (vector_t){left.X + right.X, left.Y + right.Y};
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

direction_t vector_to_direction(vector_t vec)
{
    if (vec.X < -0.5)
    {
        return DIRECTION_WEST;
    }
    else if (vec.X > 0.5)
    {
        return DIRECTION_EAST;
    }

    if (vec.Y < 0)
    {
        return DIRECTION_NORTH;
    }
    else if (vec.Y > 0)
    {
        return DIRECTION_SOUTH;
    }

    return DIRECTION_SOUTH;
}
