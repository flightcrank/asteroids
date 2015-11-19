
//renderer.h

#include <stdint.h>

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//assing a colour to a single pixel
void draw_pixel(uint32_t* pixel_buffer, int x, int y, uint32_t colour);

//assign a colour to all pixels
void clear_pixels(uint32_t* pixel_buffer, uint32_t colour);

