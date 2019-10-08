#include <hevadea/sprites.h>
#include <hevadea/logger.h>
#include <hevadea/color.h>

#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#define _XOPEN_SOURCE 500
#define __USE_XOPEN_EXTENDED
#include <ftw.h>

void loading_screen(const char *message, double progress)
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawRectangle(0, GetScreenHeight() - 26, GetScreenWidth() * progress, 26, ORANGE);
    DrawText(message, 3, GetScreenHeight() - 26 + 3, 20, BLACK);

    int text_width = MeasureText("Loading...", 40);
    DrawText("Loading...", GetScreenWidth() / 2 - text_width / 2, GetScreenHeight() / 2 - 20, 40, BLACK);

    EndDrawing();
}

typedef struct
{
    // FIXME: only use for packing the sprites on the atlas...
    bool packed;
    Image image;

    const char *name;
    rectangle_t rect;
} sprite_instance_t;

static Texture2D sprites_atlas;
static sprite_instance_t *sprites_instances = NULL;
static size_t sprites_count = 0;
static size_t sprites_allocated = 0;
static const char *sprites_path = NULL;

const char *sprite_path_to_name(const char *path)
{
    for (int i = 0; *path == sprites_path[i]; i++)
    {
        path++;
    }

    char *sprite_name = calloc(strlen(path) - strlen(".png") + 1, 1);
    memcpy(sprite_name, path, strlen(path) - strlen(".png"));
    return sprite_name;
}

void sprites_grow_array(void)
{
    if (sprites_allocated == 0)
    {
        sprites_allocated = 128;
        sprites_instances = calloc(sprites_allocated, sizeof(sprite_instance_t));
    }
    else
    {
        size_t new_allocated = sprites_allocated * 2;
        sprites_instances = realloc(sprites_instances, new_allocated * sizeof(sprite_instance_t));

        log_info("Expended the sprite array from %d to %d at 0x%08x", sprites_allocated, new_allocated, sprites_instances);

        sprites_allocated = new_allocated;
    }
}

void spites_load_sprite(const char *path, const char *name)
{
    if (sprites_count == sprites_allocated)
    {
        sprites_grow_array();
    }

    sprites_instances[sprites_count].packed = false;
    sprites_instances[sprites_count].name = name;
    sprites_instances[sprites_count].image = LoadImage(path);
    sprites_instances[sprites_count].rect.Width = sprites_instances[sprites_count].image.width;
    sprites_instances[sprites_count].rect.Height = sprites_instances[sprites_count].image.height;

    sprites_count++;
}

static int tree_walker_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    if (typeflag != FTW_F)
        return 0;

    (void)sb;
    (void)ftwbuf;

    spites_load_sprite(fpath, sprite_path_to_name(fpath));

    return 0;
}

int sprite_instance_cmp(const void *a, const void *b)
{
    int sa = ((sprite_instance_t *)a)->image.width * ((sprite_instance_t *)a)->image.height;
    int sb = ((sprite_instance_t *)b)->image.width * ((sprite_instance_t *)b)->image.height;

    if (sa > sb)
        return -1;

    if (sa < sb)
        return 1;

    return 0;
}

sprite_instance_t *sprites_at(rectangle_t rect)
{
    for (size_t i = 0; i < sprites_count; i++)
    {
        sprite_instance_t *sprite = &sprites_instances[i];

        if (sprite->packed && rectangle_coliding(sprite->rect, rect))
        {
            return sprite;
        }
    }

    return NULL;
}

sprite_instance_t *sprite_to_pack(position_t pos, unsigned int atlas_size)
{
    for (size_t i = 0; i < sprites_count; i++)
    {
        sprite_instance_t *sprite = &sprites_instances[i];

        if (!sprite->packed &&
            (pos.X + sprite->rect.Width < atlas_size) &&
            (pos.Y + sprite->rect.Height < atlas_size))
        {
            return sprite;
        }
    }

    return NULL;
}

void sprites_load(void)
{
    sprites_path = "./assets/sprites/";

    nftw(sprites_path, tree_walker_callback, 16, 0);

    qsort(sprites_instances, sprites_count, sizeof(sprite_instance_t), sprite_instance_cmp);

    //int atlas_size = 512;
    Image atlas = GenImageColor(512, 512, (Color){0, 0, 0, 0});

    size_t sprites_packed_count = 0;
    while (sprites_packed_count < sprites_count)
    {
        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {
                sprite_instance_t *spr_to_pack = sprite_to_pack((position_t){x, y}, 512);

                if (spr_to_pack != NULL)
                {
                    spr_to_pack->rect.X = x;
                    spr_to_pack->rect.Y = y;

                    sprite_instance_t *spr_at = sprites_at(spr_to_pack->rect);

                    if (spr_at == NULL)
                    {
                        //log_info("Blitting %s", spr_to_pack->name);
                        char buffer[1024];
                        sprintf(buffer, "Packing %s...", spr_to_pack->name);
                        loading_screen(buffer, sprites_packed_count / (double)sprites_count);

                        spr_to_pack->packed = true;

                        ImageDraw(&atlas,
                                  spr_to_pack->image,
                                  (Rectangle){0, 0, spr_to_pack->rect.Width, spr_to_pack->rect.Height},
                                  (Rectangle){spr_to_pack->rect.X, spr_to_pack->rect.Y, spr_to_pack->rect.Width, spr_to_pack->rect.Height},
                                  WHITE);

                        sprites_packed_count++;

                        x += spr_to_pack->rect.Width;
                    }
                    else if (spr_at != NULL)
                    {
                        x += spr_at->rect.Width;
                    }
                }
            }
        }
    }

    log_info("Saving image");

    sprites_atlas = LoadTextureFromImage(atlas);
    UnloadImage(atlas);
}

void sprites_unload(void)
{
}

sprite_t sprites_by_name(const char *name)
{
    for (size_t i = 0; i < sprites_count; i++)
    {
        if (strcmp(name, sprites_instances[i].name) == 0)
        {
            return (sprite_t){
                sprites_instances[i].rect.X,
                sprites_instances[i].rect.Y,
                sprites_instances[i].rect.Width,
                sprites_instances[i].rect.Height,
            };
        }
    }

    // FIXME: Stackoverflow if there is no "none" sprite
    return sprites_by_name("none");
}

void sprite_draw(sprite_t sprite, position_t position, color_t color)
{
    DrawTexturePro(sprites_atlas,
                   (Rectangle){sprite.X, sprite.Y, sprite.Width, sprite.Height},
                   (Rectangle){position.X, position.Y, sprite.Width, sprite.Height},
                   (Vector2){0, 0},
                   0,
                   (Color){color.R, color.G, color.B, color.A});
}

sprite_t sprite_subsprite(sprite_t sprite, int split_x, int split_y, int x, int y)
{
    double unit_x = sprite.Width / split_x;
    double unit_y = sprite.Height / split_y;

    return (sprite_t){sprite.X + unit_x * x, sprite.Y + unit_y * y, unit_x, unit_y};
}
