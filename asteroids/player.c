
//player.c

#include <stdio.h>
#include "renderer.h"
#include "player.h"

#define VERTS 3
#define BULLETS 3

struct vector2d location = {0, 0};
struct vector2d velocity = {0, 0};
struct vector2d obj_vert[VERTS] = {{0, 1.5}, {-1, -1}, {1, -1}};
struct vector2d world_vert[VERTS] = {{0, 0}, {0, 0}, {0, 0}};
struct bullet bullets[BULLETS];

void init_player() {
	
	int i = 0;
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	//convert player verts from object space to world space
	for(i = 0; i < VERTS; i++) {

		multiply_vector(&obj_vert[i], -1);
		multiply_vector(&obj_vert[i], 10.5);
		add_vector(&world_vert[i], &obj_vert[i]);
		add_vector(&world_vert[i], &translation);
	}
	
	for(i = 0; i < BULLETS; i++) {
		
		bullets[i].alive = FALSE;
	}
}

void apply_force(struct vector2d v) {

	add_vector(&velocity, &v);
}

struct vector2d get_direction() {

	struct vector2d direction = obj_vert[0];
	normalise_vector(&direction);

	return direction;
}

void shoot_bullet() {
	
	int i = 0;

	for (i = 0; i < BULLETS; i++) {
		
		if (bullets[i].alive == FALSE) {
			
			bullets[i].alive = TRUE;
			bullets[i].location = world_vert[0];
			bullets[i].velocity = get_direction();
			multiply_vector(&bullets[i].velocity, 4.4);
			break;
		}
	}
}

void draw_player(uint32_t* pixel_buffer) {
	
	int i = 0;

	draw_line(pixel_buffer, world_vert[0].x, world_vert[0].y, world_vert[1].x, world_vert[1].y, 0xffffffff);
	draw_line(pixel_buffer, world_vert[1].x, world_vert[1].y, world_vert[2].x, world_vert[2].y, 0xffffffff);
	draw_line(pixel_buffer, world_vert[2].x, world_vert[2].y, world_vert[0].x, world_vert[0].y, 0xffffffff);

	//draw vers representing the player
	for (i = 0; i < VERTS; i++) {
	
		//draw_pixel(pixel_buffer, world_vert[i].x, world_vert[i].y, 0xff00ffff);	
	}

	//draw verts representing the bullets
	for (i = 0; i < BULLETS; i++) {

		if (bullets[i].alive == TRUE) {
			
			draw_pixel(pixel_buffer, bullets[i].location.x, bullets[i].location.y, 0xffffffff);	
		}
	}

	//draw vert representing ships location
	struct vector2d cpy = {location.x, location.y};
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	add_vector(&cpy, &translation);

	draw_pixel(pixel_buffer, cpy.x, cpy.y, 0x00ff00ff);	
}

void update_player() {
	
	limit_vector(&velocity, 2.5);
	add_vector(&location, &velocity);
	
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

	int i = 0; 

	for (i =0; i < VERTS; i++) {
		
		world_vert[i] = add_vector_new(&obj_vert[i], &location);	
		add_vector(&world_vert[i], &translation);
	}
	
	for (i = 0; i < BULLETS; i++) {
		
		add_vector(&bullets[i].location, &bullets[i].velocity);
	}
}

void rotate_player(float degrees) {
	
	int i = 0;

	for (i =0; i < VERTS; i++) {
	
		rotate_vector(&obj_vert[i], degrees);
	}
}

void bounds_player() {
	
	int i = 0;
	
	if (location.x < -SCREEN_WIDTH / 2) {
		
		location.x = SCREEN_WIDTH / 2;
	}
	
	if (location.x > SCREEN_WIDTH / 2) {
		
		location.x = -SCREEN_WIDTH / 2;
	}

	if (location.y < -SCREEN_HEIGHT / 2) {
		
		location.y = SCREEN_HEIGHT / 2;
	}
	
	if (location.y > SCREEN_HEIGHT / 2) {
		
		location.y = -SCREEN_HEIGHT / 2;
	}

	//bullet is out of bounds, reset bullet to be shot again
	//bullets are in world space
	for (i = 0; i < BULLETS; i++) {
		
		if (bullets[i].location.x < 0 || bullets[i].location.x >= SCREEN_WIDTH) {
			
			bullets[i].alive = FALSE;
		}
		
		if (bullets[i].location.y < 0 || bullets[i].location.y >= SCREEN_HEIGHT) {
			
			bullets[i].alive = FALSE;
		}
	}
}

