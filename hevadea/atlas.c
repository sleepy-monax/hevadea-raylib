#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#include <hevadea/atlas.h>
#include <hevadea/array.h>
#include <hevadea/sprite.h>
#include <hevadea/filesystem.h>
#include <hevadea/rectangle.h>

Texture2D atlas_texture;
array_t *atlas_sprites = NULL;
const char *atlas_sprites_path = NULL;

typedef struct
{
    bool packed;
    const char *name;
    Image image;
    rectangle_t bound;
} atlas_packing_unite_t;

static void atlas_unit_to_pack_destroy_callback(void *element, void *args)
{
    (void)args;
    atlas_packing_unite_t *unit = (atlas_packing_unite_t *)element;
    UnloadImage(unit->image);
}

const char *sprite_path_to_name(const char *path)
{
    for (int i = 0; *path == atlas_sprites_path[i]; i++)
    {
        path++;
    }

    char *sprite_name = calloc(strlen(path) - strlen(".png") + 1, 1);
    memcpy(sprite_name, path, strlen(path) - strlen(".png"));
    return sprite_name;
}

static iterate_state_t atlas_unit_load_callback(const char *path, filesystem_file_type_t type, void *args)
{
    array_t *unites = (array_t *)args;

    if (type != FILESYSTEM_FILE)
        return ITERATION_CONTINUE;

    atlas_packing_unite_t unit = {
        .packed = false,
        .name = sprite_path_to_name(path),
        .image = LoadImage(path),
        .bound = {
            0,
            0,
            unit.image.width,
            unit.image.height,
        },
    };

    array_pushback(unites, &unit, sizeof(atlas_packing_unite_t));

    return ITERATION_CONTINUE;
}

int atlas_packing_unite_cmp(const void *a, const void *b)
{
    int sa = ((atlas_packing_unite_t *)a)->image.width * ((atlas_packing_unite_t *)a)->image.height;
    int sb = ((atlas_packing_unite_t *)b)->image.width * ((atlas_packing_unite_t *)b)->image.height;

    if (sa > sb)
        return -1;

    if (sa < sb)
        return 1;

    return 0;
}

atlas_packing_unite_t *atlas_get_unit_to_pack(array_t *atlas_unit_to_pack, position_t pos, unsigned int atlas_size)
{
    for (size_t i = 0; i < array_count(atlas_unit_to_pack); i++)
    {
        atlas_packing_unite_t *sprite = array_index(atlas_unit_to_pack, i);

        if (!sprite->packed &&
            (pos.X + sprite->bound.Width < atlas_size) &&
            (pos.Y + sprite->bound.Height < atlas_size))
        {
            return sprite;
        }
    }

    return NULL;
}

atlas_packing_unite_t *atlas_unit_at(array_t *atlas_unit_to_pack, rectangle_t rect)
{
    for (size_t i = 0; i < array_count(atlas_unit_to_pack); i++)
    {
        atlas_packing_unite_t *sprite = array_index(atlas_unit_to_pack, i);

        if (sprite->packed && rectangle_coliding(sprite->bound, rect))
        {
            return sprite;
        }
    }

    return NULL;
}

void atlas_load(void)
{
    atlas_sprites_path = "./assets/sprites/";

    array_t *atlas_unit_to_pack = array_create(sizeof(atlas_packing_unite_t));

    // Look recusivly for all sprites
    filesystem_iterate(atlas_sprites_path, atlas_unit_load_callback, atlas_unit_to_pack);

    // Sort units by size
    array_sort(atlas_unit_to_pack, atlas_packing_unite_cmp);

    Image atlas = GenImageColor(512, 512, (Color){0, 0, 0, 0});

    size_t unit_packed_count = 0;
    while (unit_packed_count < array_count(atlas_unit_to_pack))
    {
        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {
                atlas_packing_unite_t *spr_to_pack = atlas_get_unit_to_pack(atlas_unit_to_pack, (position_t){x, y}, 512);

                if (spr_to_pack != NULL)
                {
                    spr_to_pack->bound.X = x;
                    spr_to_pack->bound.Y = y;

                    atlas_packing_unite_t *spr_at = atlas_unit_at(atlas_unit_to_pack, spr_to_pack->bound);

                    if (spr_at == NULL)
                    {
                        spr_to_pack->packed = true;

                        ImageDraw(&atlas,
                                  spr_to_pack->image,
                                  (Rectangle){0, 0, spr_to_pack->bound.Width, spr_to_pack->bound.Height},
                                  (Rectangle){spr_to_pack->bound.X, spr_to_pack->bound.Y, spr_to_pack->bound.Width, spr_to_pack->bound.Height},
                                  WHITE);

                        unit_packed_count++;

                        x += spr_to_pack->bound.Width;
                    }
                    else if (spr_at != NULL)
                    {
                        x += spr_at->bound.Width;
                    }
                }
            }
        }
    }

    atlas_texture = LoadTextureFromImage(atlas);
    // Destroy the packing unit list

    atlas_sprites = array_create(sizeof(sprite_t));

    for (size_t i = 0; i < array_count(atlas_unit_to_pack); i++)
    {
        atlas_packing_unite_t *unite = array_index(atlas_unit_to_pack, i);

        sprite_t sprite = {
            .name = unite->name,

            .X = unite->bound.X,
            .Y = unite->bound.Y,
            .Width = unite->bound.Width,
            .Height = unite->bound.Height,
        };

        array_pushback(atlas_sprites, &sprite, sizeof(sprite_t));
    }

    array_destroy(atlas_unit_to_pack, atlas_unit_to_pack_destroy_callback, NULL);
    UnloadImage(atlas);
}

void atlas_unload(void)
{
    for (size_t i = 0; i < array_count(atlas_sprites); i++)
    {
        sprite_t *sprite = array_index(atlas_sprites, i);

        free((char *)sprite->name);
    }

    array_destroy(atlas_sprites, NULL, NULL);
    UnloadTexture(atlas_texture);
}

texture2d_t atlas_get_texture(void)
{
    return (texture2d_t){
        .id = atlas_texture.id,
        .width = atlas_texture.width,
        .height = atlas_texture.height,
        .mipmaps = atlas_texture.mipmaps,
        .format = atlas_texture.format,
    };
}

sprite_t atlas_sprite_by_name(const char *name)
{
    for (size_t i = 0; i < array_count(atlas_sprites); i++)
    {
        sprite_t *sprite = array_index(atlas_sprites, i);

        if (strcmp(name, sprite->name) == 0)
        {
            return *sprite;
        }
    }

    return atlas_sprite_by_name("none");
}