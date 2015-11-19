
//renderer.c

#include <stdint.h>
#include <stdio.h>
#include "renderer.h"

void draw_pixel(uint32_t* pixel_buffer, int x, int y, uint32_t colour) {
	
	uint32_t position = y * SCREEN_WIDTH + x;
	pixel_buffer[position] = colour;
}

void clear_pixels(uint32_t* pixel_buffer, uint32_t colour) {

	int i = 0;
	int buffer_size = SCREEN_WIDTH * SCREEN_HEIGHT;

	for (i = 0; i < buffer_size; i++) {
		
		pixel_buffer[i] = colour;
	}

}
