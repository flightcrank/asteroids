
//main.c

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "player.h"
#include "asteroids.h"

#define ASTEROIDS 3

int init(int width, int height);

SDL_Window* window = NULL;			//The window we'll be rendering to
SDL_Renderer *renderer;				//The renderer SDL will use to draw to the screen
SDL_Texture *screen;				//The texture representing the screen	
uint32_t* pixels = NULL;			//The pixel buffer to draw to
struct asteroid asteroids[ASTEROIDS];		//The asteroids
struct player p;				//The player
    
int main (int argc, char* args[]) {

	//SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT) == 1) {
		
		return 0;
	}

	//set up player in world space
	init_player(&p);
	init_asteroids(asteroids, ASTEROIDS);

	int sleep = 0;
	int quit = 0;
	SDL_Event event;
	Uint32 next_game_tick = SDL_GetTicks();
	
	//render loop
	while(quit == 0) {
		
		//check for new events every frame
		SDL_PumpEvents();

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if (state[SDL_SCANCODE_ESCAPE]) {
		
			quit = 1;
		}
			
		if (state[SDL_SCANCODE_UP]) {

			struct vector2d thrust = get_direction(&p);
			multiply_vector(&thrust, .06);
			apply_force(&p.velocity, thrust);
		}
		
		if (state[SDL_SCANCODE_LEFT]) {
			
			rotate_player(&p, -4);
		}

		if (state[SDL_SCANCODE_RIGHT]) {
			
			rotate_player(&p, 4);
		}

		while (SDL_PollEvent(&event)) {
		
			switch(event.type) {
					
				case SDL_KEYDOWN:
					
					switch( event.key.keysym.sym ) {
					
						case SDLK_SPACE:
						
							shoot_bullet(&p);
							break; 
					}
			}
		}

		//draw to the pixel buffer
		clear_pixels(pixels, 0x00000000);
		draw_player(pixels, &p);
		draw_asteroids(pixels, asteroids, ASTEROIDS);
		update_player(&p);
		update_asteroids(asteroids, ASTEROIDS);
		bounds_player(&p);
		bounds_asteroids(asteroids, ASTEROIDS);
		collision_asteroids(asteroids, ASTEROIDS, &p.location, p.hit_radius);
		
		int i = 0;
		struct vector2d translation = {-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2};

		for (i = 0; i < BULLETS; i++) {
			
			//convert bullet screen space location to world space to compare
			//with asteroids world space to detect a collision
			struct vector2d world = add_vector_new(&p.bullets[i].location, &translation);
			int res = collision_asteroids(asteroids, ASTEROIDS, &world, 1);

			if (res == 1) {
				
				p.bullets[i].alive = FALSE; 
			}
		}

		//draw buffer to the texture representing the screen
		SDL_UpdateTexture(screen, NULL, pixels, SCREEN_WIDTH * sizeof (Uint32));

		//draw to the screen
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, screen, NULL, NULL);
		SDL_RenderPresent(renderer);
				
		//time it takes to render 1 frame in milliseconds
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();
	
		if( sleep >= 0 ) {
            				
			SDL_Delay(sleep);
		}
	}

	//free the screen buffer
	free(pixels);
	
	//Destroy window 
	SDL_DestroyWindow(window);

	//Quit SDL subsystems 
	SDL_Quit(); 
	 
	return 0;
}

int init(int width, int height) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		
		return 1;
	} 
	
	//Create window	
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
	
	//set up screen texture
	screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//allocate pixel buffer
	pixels = (Uint32*) malloc((SCREEN_WIDTH * SCREEN_HEIGHT) * sizeof(Uint32));


	if (window == NULL) { 
		
		printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		
		return 1;
	}

	if (screen == NULL) { 
		
		printf ("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
		
		return 1;
	}
	
	if (pixels == NULL) {
	
		printf ("Error allocating pixel buffer");
		
		return 1;
	}

	return 0;
}

