
//renderer.c

#include <stdint.h>
#include <stdio.h>
#include "renderer.h"

int draw_pixel(uint32_t* pixel_buffer, int x, int y, uint32_t colour) {
	
	//dont draw any pixels that are outside of the pixel buffer
	if (x < 0 || y < 0) {
			
		return 1;
	}
	
	//dont draw any pixels that are outside of the pixel buffer
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
			
		return 1;
	}

	uint32_t position = y * SCREEN_WIDTH + x;
	pixel_buffer[position] = colour;

	return 0;
}

void clear_pixels(uint32_t* pixel_buffer, uint32_t colour) {

	int i = 0;
	int buffer_size = SCREEN_WIDTH * SCREEN_HEIGHT;

	for (i = 0; i < buffer_size; i++) {
		
		pixel_buffer[i] = colour;
	}
}

