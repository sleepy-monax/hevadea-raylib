#include <stdlib.h>
#include <hevadea/random.h>

double random_next_double(void)
{
    return ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
}

vector_t random_next_vector(void)
{
    return (vector_t){random_next_double(), random_next_double()};
}
