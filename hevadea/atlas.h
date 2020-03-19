#pragma once

#include "hevadea/sprite.h"
#include <hevadea/texture2d.h>

void atlas_load(void);
void atlas_unload(void);

texture2d_t atlas_get_texture(void);

sprite_t atlas_sprite_by_name(const char *name);