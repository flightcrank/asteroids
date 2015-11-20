
//player.h

#include "vector.h"

void draw_player(uint32_t* pixel_buffer);

void move_player();

void bounds_player();

void translate();

void apply_force(struct vector2d v);

void rotate_player(float degrees);

struct vector2d get_direction();

