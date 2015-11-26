
//asteroids.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "renderer.h"
#include "asteroids.h"

void init_asteroids(struct asteroid asteroids[], int size) {
	
	int i = 0;
	int j = 0;
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	
	for (i = 0; i < size; i++) {
		
		int sign_x = rand() % 100;
		int sign_y = rand() % 100;
		
		//start asteroid in random location
		int lx = rand() % SCREEN_WIDTH / 2;
		int ly = rand() % SCREEN_HEIGHT / 2;
	
		//give asteroid random velocity
		float vx = (float) (rand() % 500) / 1000;
		float vy = (float) (rand() % 500) / 1000;
		
		float degrees =  (float) (rand() %  100 + 1000) / 1000;	
		
		//50% chance the sign of the variable will be switched to negative
		if (sign_x >= 50) {
			
			vx = -vx;
			lx = -lx;
			degrees = -degrees;
		}
		
		//50% chance the sign of the variable will be switched to negative
		if (sign_y >= 50) {
			
			vy = -vy;
			ly = -ly;
		}

		asteroids[i].hit_radius = 35;
		asteroids[i].rotation = degrees;
		asteroids[i].location.x = lx;
		asteroids[i].location.y = ly;
		asteroids[i].velocity.x = vx;
		asteroids[i].velocity.y = vy;
		asteroids[i].obj_vert[0].x = .0;
		asteroids[i].obj_vert[0].y = .4;
		asteroids[i].obj_vert[1].x = .2;
		asteroids[i].obj_vert[1].y = .3;
		asteroids[i].obj_vert[2].x = .2;
		asteroids[i].obj_vert[2].y = .1;
		asteroids[i].obj_vert[3].x = .4;
		asteroids[i].obj_vert[3].y = .0;
		asteroids[i].obj_vert[4].x = .3;
		asteroids[i].obj_vert[4].y = -.2;
		asteroids[i].obj_vert[5].x = .1;
		asteroids[i].obj_vert[5].y = -.2;
		asteroids[i].obj_vert[6].x = .0;
		asteroids[i].obj_vert[6].y = -.3;
		asteroids[i].obj_vert[7].x = -.2;
		asteroids[i].obj_vert[7].y = -.2;
		asteroids[i].obj_vert[8].x = -.4;
		asteroids[i].obj_vert[8].y = 0;
		asteroids[i].obj_vert[9].x = -.3;
		asteroids[i].obj_vert[9].y = .3;
		
		for (j = 0; j < VERTS; j++) {
			
			//coverts verts from obj space to world space and traslate world space to screen space
			multiply_vector(&asteroids[i].obj_vert[j], 88);
			add_vector(&asteroids[i].world_vert[j], &asteroids[i].obj_vert[j]);
			add_vector(&asteroids[i].world_vert[j], &translation);
		}
	}
}

void update_asteroids(struct asteroid asteroids[], int size) {

	int i = 0; 
	int j = 0; 
	struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	
	for (i = 0; i < size; i++) {
		
		//updates each asteroids location based off its velicity vector
		add_vector(&asteroids[i].location, &asteroids[i].velocity);
		
		//update each vert of the asteroid to reflect the changes made to the asteroids location vector
		//and rotation amount, then translate the new vert location to screen space
		for (j = 0; j < VERTS; j++) {
				
			asteroids[i].world_vert[j] = add_vector_new(&asteroids[i].obj_vert[j], &asteroids[i].location);
			add_vector(&asteroids[i].world_vert[j], &translation);
			rotate_vector(&asteroids[i].obj_vert[j], asteroids[i].rotation);
		}
	}
}

void draw_asteroids(uint32_t* pixel_buffer, struct asteroid asteroids[], int size) {

	int i = 0;

	for (i = 0; i < size; i++) {
	
		draw_line(pixel_buffer, asteroids[i].world_vert[0].x, asteroids[i].world_vert[0].y, asteroids[i].world_vert[1].x, asteroids[i].world_vert[1].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[1].x, asteroids[i].world_vert[1].y, asteroids[i].world_vert[2].x, asteroids[i].world_vert[2].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[2].x, asteroids[i].world_vert[2].y, asteroids[i].world_vert[3].x, asteroids[i].world_vert[3].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[3].x, asteroids[i].world_vert[3].y, asteroids[i].world_vert[4].x, asteroids[i].world_vert[4].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[4].x, asteroids[i].world_vert[4].y, asteroids[i].world_vert[5].x, asteroids[i].world_vert[5].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[5].x, asteroids[i].world_vert[5].y, asteroids[i].world_vert[6].x, asteroids[i].world_vert[6].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[6].x, asteroids[i].world_vert[6].y, asteroids[i].world_vert[7].x, asteroids[i].world_vert[7].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[7].x, asteroids[i].world_vert[7].y, asteroids[i].world_vert[8].x, asteroids[i].world_vert[8].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[8].x, asteroids[i].world_vert[8].y, asteroids[i].world_vert[9].x, asteroids[i].world_vert[9].y, 0xffffffff);
		draw_line(pixel_buffer, asteroids[i].world_vert[9].x, asteroids[i].world_vert[9].y, asteroids[i].world_vert[0].x, asteroids[i].world_vert[0].y, 0xffffffff);

		/*
		//draw vert representing ships location
		struct vector2d cpy = {asteroids[i].location.x, asteroids[i].location.y};
		struct vector2d translation = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		add_vector(&cpy, &translation);

		draw_pixel(pixel_buffer, cpy.x, cpy.y, 0x00ff00ff);
		*/
	}
}


void bounds_asteroids(struct asteroid asteroids[], int size) {

	int i = 0;

	for (i = 0 ; i < size; i++) {
		
		if (asteroids[i].location.x < -SCREEN_WIDTH / 2) {
			
			asteroids[i].location.x = SCREEN_WIDTH / 2;
		}
	
		if (asteroids[i].location.x > SCREEN_WIDTH / 2) {
			
			asteroids[i].location.x = -SCREEN_WIDTH / 2;
		}
		
		if (asteroids[i].location.y < -SCREEN_HEIGHT / 2) {
			
			asteroids[i].location.y = SCREEN_HEIGHT / 2;
		}
	
		if (asteroids[i].location.y > SCREEN_HEIGHT / 2) {
			
			asteroids[i].location.y = -SCREEN_HEIGHT / 2;
		}
	}
}


int collision_asteroids(struct asteroid asteroids[], int size, struct vector2d* v, float radius) {


	int i = 0;

	for (i = 0; i < size; i++) {

		float sum = asteroids[i].hit_radius + radius;
		float a = pow(asteroids[i].location.x - v->x, 2);
		float b = pow(asteroids[i].location.y - v->y, 2);
		float distance = sqrt(a + b);
		
		if (distance < sum) {
			
			return 1;
		}
	}

	return 0;
}
