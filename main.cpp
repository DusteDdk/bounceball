#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ball.hpp"

typedef struct {
	int screenWidth;
	int screenHeight;
	bool fullscreen;
	bool clear;
} config_t;

int main(int, char**) {

	config_t config;

	config.fullscreen=true;
	config.screenWidth=1024;
	config.screenHeight=768;
	config.clear=true;
	int sdlFullscreenFlag = 0;


	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// If configured to fullscreen, get the current desktop resolution, and use that instead.
	if(config.fullscreen) {
		SDL_DisplayMode modeInfo;
		SDL_GetCurrentDisplayMode(0, &modeInfo);
		config.screenWidth = modeInfo.w;
		config.screenHeight = modeInfo.h;
		sdlFullscreenFlag=SDL_WINDOW_FULLSCREEN_DESKTOP;
	}


	// Initialize the SDL_Image library for loading PNG files
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "IMG_Init error:" << IMG_GetError() << std::endl;
		return 1;
	}

	// Create a window
	SDL_Window *win = SDL_CreateWindow("Bounce!", 100, 100, config.screenWidth, config.screenHeight, SDL_WINDOW_SHOWN | sdlFullscreenFlag);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create a renderer (That's what draws stuff in the window)
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Load an image
	SDL_Surface *img = IMG_Load("./ball.png");
	if (img == nullptr) {
		std::cout << "IMG_load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	// Make the image into a texture, suitable for rendering with our renderer
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Ball *ball = new Ball(tex, img->clip_rect, 100,100, 25.8,2.6);

	SDL_Event event;

	// This is the main loop
	bool run = true;

//	SDL_GL_SetSwapInterval(0);

	while (run) {
		// Handle events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					run = false;
					break;
				case SDLK_c:
					config.clear=!config.clear;
					break;
				}
				break;
				case SDL_QUIT:
					run = false;
				break;
			}
		}

		//First clear the renderer
		if(config.clear) {
			SDL_RenderClear(ren);
		}

		ball->move(1);
		ball->draw(ren);
		ball->reactInsideBox( 0,0, config.screenWidth,config.screenHeight);

		//Update the screen
		SDL_RenderPresent(ren);
	}

	delete ball;
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
