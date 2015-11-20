
//player.c

#include <math.h>
#include <stdio.h>
#include "renderer.h"
#include "vector.h"

#define VERTS 3

struct vector2d location = {0, 0};
struct vector2d velocity = {0, 0};
struct vector2d obj_vert[VERTS] = {{0, 1.5}, {-1, -1}, {1, -1}};
struct vector2d world_vert[VERTS] = {{0, 0}, {0, 0}, {0, 0}};

void translate() {
	
	int i = 0;
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	
	for(i = 0; i < VERTS; i++) {

		multiply_vector(&obj_vert[i], -1);
		multiply_vector(&obj_vert[i], 10);
		add_vector(&world_vert[i], &obj_vert[i]);
		add_vector(&world_vert[i], &translation);
	}
}

void apply_force(struct vector2d v) {

	add_vector(&velocity, &v);
}

void draw_player(uint32_t* pixel_buffer) {
	
	int i = 0;

	for (i = 0; i < VERTS; i++) {
	
		//dont draw any pixels that are outside of the pixel buffer
		if (world_vert[i].x < 0 || world_vert[i].y < 0) {
			
			continue;
		}
		
		//dont draw any pixels that are outside of the pixel buffer
		if (world_vert[i].x >= SCREEN_WIDTH || world_vert[i].y >= SCREEN_HEIGHT) {
			
			continue;
		}

		draw_pixel(pixel_buffer, world_vert[i].x, world_vert[i].y, 0xffffffff);	
	}

}

void move_player() {
	
	add_vector(&location, &velocity);
	
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	int i = 0; 

	for (i =0; i < VERTS; i++) {
		
		world_vert[i] = add_vector_new(&obj_vert[i], &location);	
		add_vector(&world_vert[i], &translation);
	}
}

void bounds_player() {
	
	if (location.y < -SCREEN_HEIGHT / 2) {
		
		location.y = SCREEN_HEIGHT / 2;
	}
}


