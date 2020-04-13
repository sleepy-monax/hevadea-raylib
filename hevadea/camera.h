#pragma once

#include "hevadea/chunk.h"
#include "hevadea/gametime.h"
#include "hevadea/position.h"
#include "hevadea/rectangle.h"

position_t camera_get_position(void);

position_t camera_get_focus(void);

void camera_set_focus(position_t position);

void camera_render_begin(void);

void camera_render_end(void);

void camera_update(gametime_t gametime);

void camera_debug_draw(void);

rectangle_t camera_load_bound(void);

rectangle_t camera_unload_bound(void);

rectangle_t camera_screen_bound(void);

void camera_interate_on_screen_chunk(void *target, ChunkIterateCallback callback);
