
//player.c

#include <math.h>
#include "renderer.h"
#include "vector.h"

#define VERTS 3

struct vector2d velocity = {0, 0};
struct vector2d obj_vert[VERTS] = {{0, 1.5}, {-1, -1}, {1, -1}};
struct vector2d world_vert[VERTS] = {{0, 0}, {0, 0}, {0, 0}};

void translate() {
	
	int i = 0;
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	
	for(i = 0; i < VERTS; i++) {

		add_vector(&world_vert[i], &obj_vert[i]);
		multiply_vector(&world_vert[i], -1);
		multiply_vector(&world_vert[i], 10);
		add_vector(&world_vert[i], &translation);
	}

}

void apply_force(struct vector2d v) {

	add_vector(&velocity, &v);
}

void draw_player(uint32_t* pixel_buffer) {

	draw_pixel(pixel_buffer, world_vert[0].x, world_vert[0].y, 0xffffffff);	
	draw_pixel(pixel_buffer, world_vert[1].x, world_vert[1].y, 0xffffffff);	
	draw_pixel(pixel_buffer, world_vert[2].x, world_vert[2].y, 0xffffffff);	
}

void move_player() {


	int i = 0; 

	for (i =0; i < VERTS; i++) {
		
		add_vector(&world_vert[i], &velocity);
	}
}

void bounds_player() {
/*	
	if (location.x > SCREEN_WIDTH - fabs(velocity.x)|| location.x < 0 + fabs(velocity.x)) {
		
		velocity.x *= -1;
	}
	
	if (location.y > SCREEN_HEIGHT -  fabs(velocity.y)|| location.y <= 0 + fabs(velocity.y)) {
		
		velocity.y *= -1;
	}
*/
}


