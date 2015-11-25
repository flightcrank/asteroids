
//renderer.c

#include "renderer.h"

int draw_line(uint32_t* pixel_buffer, int x1, int y1, int x2, int y2, uint32_t colour) {


	//plot the first point
	draw_pixel(pixel_buffer, x1, y1, colour);

	//make sure we draw the line always from left to right
	if (x1 > x2) {

		int temp_x = x1;
		int temp_y = y1;

		x1 = x2;
		y1 = y2;

		x2 = temp_x;
		y2 = temp_y;
	}
	
	int dx = x2 - x1;
	int dy = y2 - y1;

	//the length of the line is greater along the X axis
	if (dx >= fabs(dy)) {
		
		float slope = (float) dy / dx;
	
		//line travels from top to bottom
		if (y1 <= y2) {

			float ideal_y = y1 + slope;
			int y = (int) round(ideal_y);
			float error = ideal_y - y;

			int i = 0;
			
			//loop through all the X values
			for(i = 1; i <= dx; i++) {
				
				int x = x1 + i;
				
				draw_pixel(pixel_buffer, x, y, colour);
				
				error += slope;

				if (error  >= 0.5) {
				
					y++;
					error -= 1;
				}
			}
		}
		
		//line travels from bottom to top
		if (y1 > y2) {
			
			float ideal_y = y1 + slope;
			int y = (int) round(ideal_y);
			float error = ideal_y - y;

			int i = 0;
			
			//loop through all the x values
			for(i = 1; i <= dx; i++) {
				
				int x = x1 + i;
				
				draw_pixel(pixel_buffer, x, y, colour);
				
				error += slope;

				if (error  <= -0.5) {
				
					y--;
					error += 1;
				}
			}
		}


	}

	//the length of the line is greater along the Y axis
	if (fabs(dy) > dx) {
		
		float slope = (float) dx / dy;
		
		//line travels from top to bottom
		if (y1 < y2) {
			
			float ideal_x = x1 + slope;
			int x = (int) round(ideal_x);
			float error = ideal_x - x;

			int i = 0;
			
			//loop through all the y values
			for(i = 1; i <= dy; i++) {
				
				int y = y1 + i;
				
				draw_pixel(pixel_buffer, x, y, colour);
				
				error += slope;

				if (error  >= 0.5) {
				
					x++;
					error -= 1;
				}
			}
		}
		
		//draw line from bottom to top
		if (y1 > y2) {
			
			float ideal_x = x1 - slope;
			int x = (int) round(ideal_x);
			float error = ideal_x - x;

			int i = 0;
			
			//loop through all the y values
			for(i = 1; i <= fabs(dy); i++) {
				
				int y = y1 - i;
				
				draw_pixel(pixel_buffer, x, y, colour);
				
				error += slope;

				if (error  <= -0.5) {
				
					x++;
					error += 1;
				}
			}
		}
	}

	return 0;	
}

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

