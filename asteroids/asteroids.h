
//asteroids.h
#include "vector.h"
#define VERTS 10

enum sizes {SMALL, MEDIUM, LARGE};

struct asteroid {

	int alive;
	enum sizes size;
	float hit_radius;
	float rotation;
	struct vector2d location;
	struct vector2d velocity;
	struct vector2d obj_vert[VERTS];
	struct vector2d world_vert[VERTS];
};

void init_asteroids(struct asteroid asteroids[], int size);
void update_asteroids(struct asteroid asteroids[], int size);
void draw_asteroids(uint32_t* pixel_buffer, struct asteroid asteroids[], int size);
int shrink_asteroid(struct asteroid* a, int size);
void spawn_asteroids(struct asteroid a[], int length, int size, struct vector2d v);
void bounds_asteroids(struct asteroid asteroids[], int size);
int collision_asteroids(struct asteroid asteroids[], int size, struct vector2d* v, float radius);
