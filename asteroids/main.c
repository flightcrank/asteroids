
//main.c

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "player.h"
#include "asteroids.h"

#define ASTEROIDS 27
#define LIVES 3

int init(int width, int height);

SDL_Window* window = NULL;			//The window we'll be rendering to
SDL_Renderer *renderer;				//The renderer SDL will use to draw to the screen
SDL_Texture *screen;				//The texture representing the screen	
uint32_t* pixels = NULL;			//The pixel buffer to draw to
struct asteroid asteroids[ASTEROIDS];		//The asteroids
struct player p;				//The player
struct player lives[LIVES];			//Player lives left
    
int main (int argc, char* args[]) {

	//SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT) == 1) {
		
		return 0;
	}

	int i = 0;
	int j = 0;
	int offset = 0;
	struct vector2d translation = {-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2};

	//set up icons used to represent player lives
	for (i = 0; i < LIVES; i++) {
			
		init_player(&lives[i]);
		lives[i].lives = 1;

		//shrink lives
		for (j = 0; j < P_VERTS; j++) {
		
			divide_vector(&lives[i].obj_vert[j], 2);
		}

		//convert screen space vector into world space
		struct vector2d top_left = {20 + offset, 20};
		add_vector(&top_left, &translation);
		lives[i].location = top_left;
		update_player(&lives[i]);
		offset += 20;
	}

	//set up player and asteroids in world space
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
							
							if (p.lives > 0) {
								
								shoot_bullet(&p);
							}

							break; 
					}
			}
		}

		//draw to the pixel buffer
		clear_pixels(pixels, 0x00000000);
		draw_player(pixels, &p);
		draw_player(pixels, &lives[0]);
		draw_player(pixels, &lives[1]);
		draw_player(pixels, &lives[2]);
		draw_asteroids(pixels, asteroids, ASTEROIDS);
		update_player(&p);
		bounds_player(&p);
		bounds_asteroids(asteroids, ASTEROIDS);

		int res = collision_asteroids(asteroids, ASTEROIDS, &p.location, p.hit_radius);

		if (res != -1) {
			
			p.lives--;
			p.location.x = 0;
			p.location.y = 0;
			p.velocity.x = 0;
			p.velocity.y = 0;

			int i = LIVES - 1;

			for ( i = LIVES; i >= 0; i--) {
				
				if(lives[i].lives > 0) {
					
					lives[i].lives = 0;
					break;
				}
			}
		}
		
		int i = 0;
		struct vector2d translation = {-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2};

		for (i = 0; i < BULLETS; i++) {
				
			//only check for collision for bullets that are shown on screen
			if (p.bullets[i].alive == TRUE) {
				
				//convert bullet screen space location to world space to compare
				//with asteroids world space to detect a collision
				struct vector2d world = add_vector_new(&p.bullets[i].location, &translation);
				int index = collision_asteroids(asteroids, ASTEROIDS, &world, 1);
				
				//collision occured
				if (index != -1) {
					
					asteroids[index].alive = 0;
					p.bullets[i].alive = FALSE;

					if (asteroids[index].size != SMALL) {
						
						spawn_asteroids(asteroids, ASTEROIDS, asteroids[index].size, asteroids[index].location);
					}
				}
			}
		}
		
		update_asteroids(asteroids, ASTEROIDS);

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

