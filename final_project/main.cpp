//original
#include <stdio.h>
#include <stdlib.h>

//sdl related
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"

//self added
#include "constants.h"
#include "System.h"
#include "RenderWindow.h"
#include "Map.h"
#include "StaticObject.h"
//#include "AnimeObject.h"

SDL_Texture* texture = NULL;


int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}

	RenderWindow window("Elden's rOng", 20, 20, WIDTH, HEIGHT);

	StaticObject kirby("../images/kirby.png", window.getRenderer());
	kirby.setPosition(WIDTH / 2 - kirby.getWidth(), 370);
	Map demo1("../images/mapdemo1.png", window.getRenderer());
	SDL_Event e;

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					kirby.setVX(kirby.getVX() - 5);
					break;
				case SDLK_RIGHT:
					kirby.setVX(kirby.getVX() + 5);
					break;
				case SDLK_DOWN:
					kirby.setVY(kirby.getVY() + 5);
					break;
				case SDLK_UP:
					kirby.setVY(kirby.getVY() - 5);
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					kirby.setVX(kirby.getVX() + 5);
					break;
				case SDLK_RIGHT:
					kirby.setVX(kirby.getVX() - 5);
					break;
				case SDLK_UP:
					kirby.setVY(kirby.getVY() + 5);
					break;
				case SDLK_DOWN:
					kirby.setVY(kirby.getVY() - 5);
					break;
				}
			}
		}
		

		

		window.clear();
		kirby.move();
		demo1.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });
		kirby.draw(window.getRenderer(), { kirby.getX(),kirby.getY(),kirby.getWidth() / 5,kirby.getHeight() / 5}, {NULL});

		window.display();

	}
	

	SDL_DestroyTexture(texture);
	demo1.close();
	kirby.close();
	window.close();
	sdl.close();

	return 0;
}