#include "hevadea/sprite.h"

sprite_t sprite_subsprite(sprite_t sprite, int split_x, int split_y, int x, int y)
{
    double unit_x = sprite.Width / split_x;
    double unit_y = sprite.Height / split_y;

    return (sprite_t){sprite.name, sprite.X + unit_x * x, sprite.Y + unit_y * y, unit_x, unit_y};
}