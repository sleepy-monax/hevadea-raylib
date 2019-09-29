#pragma once

#include <hevadea/position.h>
#include <hevadea/rectangle.h>

position_t camera_get_position(void);

void camera_set_position(position_t position);

void camera_render_begin(void);

void camera_render_end(void);

void camera_move(void);

void camera_debug_draw(void);

rectangle_t camera_load_bound(void);

rectangle_t camera_unload_bound(void);