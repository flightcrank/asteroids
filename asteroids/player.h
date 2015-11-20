
//player.h

#include "vector.h"

enum boolean {TRUE, FALSE};

struct bullet {
	
	struct vector2d location;
	struct vector2d velocity;
	enum boolean alive;
};

void init_player();

void draw_player(uint32_t* pixel_buffer);

void shoot_bullet();

void update_player();

void bounds_player();

void apply_force(struct vector2d v);

void rotate_player(float degrees);

struct vector2d get_direction();

