
//player.c

#include <math.h>
#include "renderer.h"
#include "vector.h"

struct vector2d location = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
struct vector2d velocity = {.7, .24};

void draw_player(uint32_t* pixel_buffer) {

	draw_pixel(pixel_buffer, location.x, location.y, 0xffffffff);	
}

void move_player() {

	location.x += velocity.x;
	location.y += velocity.y;
}

void bounds_player() {
	
	if (location.x > SCREEN_WIDTH - fabs(velocity.x)|| location.x < 0 + fabs(velocity.x)) {
		
		velocity.x *= -1;
	}
	
	if (location.y > SCREEN_HEIGHT -  fabs(velocity.y)|| location.y <= 0 + fabs(velocity.y)) {
		
		velocity.y *= -1;
	}
}
