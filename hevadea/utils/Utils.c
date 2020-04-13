#include <math.h>
#include <unistd.h>

#include "hevadea/logger.h"
#include "hevadea/utils/Utils.h"

void __attribute__((noreturn)) PANIC(const char *why)
{
    log_fatal("%s", why);

    _exit(-1);
}

void iterate_spiral(int x, int y, int size, iterate_callback_t callback, void *arg)
{
    int d = 0; // current direction; 0=RIGHT, 1=DOWN, 2=LEFT, 3=UP
    int c = 0; // counter
    int s = 1; // chain size

    // starting point
    int offx = ((int)floor(size)) - 1;
    int offy = ((int)floor(size)) - 1;

    for (int k = 1; k <= (2 * size - 1); k++)
    {
        for (int j = 0; j < (k < (2 * size - 1) ? 2 : 3); j++)
        {
            for (int i = 0; i < s; i++)
            {
                if (callback(x + offx - size, y + offy - size, arg) == ITERATION_STOP)
                {
                    return;
                }

                c++;

                switch (d)
                {
                case 0:
                    offy = offy + 1;
                    break;
                case 1:
                    offx = offx + 1;
                    break;
                case 2:
                    offy = offy - 1;
                    break;
                case 3:
                    offx = offx - 1;
                    break;
                }
            }
            d = (d + 1) % 4;
        }
        s = s + 1;
    }

    if (callback(x + offx - size, y + offy - size, arg) == ITERATION_STOP)
    {
        return;
    }
}

void iterate_square(int x, int y, int size, iterate_callback_t callback, void *arg)
{
    for (int offx = -size; offx < size; offx++)
    {
        for (int offy = -size; offy < size; offy++)
        {
            if (callback(x + offx, y + offy, arg) == ITERATION_STOP)
            {
                return;
            }
        }
    }
}