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
#include "AnimeObject.h"
#include "Collision.h"

SDL_Texture* texture = NULL;


int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}

	RenderWindow window("Elden's rOng", 300, 170, WIDTH, HEIGHT);

	SDL_Rect test1, test2;
	StaticObject kirby("../images/kirby.png", window.getRenderer());
	AnimeObject pooh("../images/pooh/", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Map demo1("../images/mapdemo1.png", window.getRenderer());
	SDL_Event e;

	kirby.setPosition(WIDTH / 2 - kirby.getWidth() / 10, 370);
	pooh.setPosition(WIDTH / 2 - kirby.getWidth() / 4, 370);
	pooh.startTimer(50);

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
//				system("CLS");
//				printf("x: %d\ny: %d\nw:%d\n", pooh.getX(), pooh.getY(), pooh.getWidth()/4);
//				printf("\ncamera X: %d\ncamera Y:%d\n", demo1.getcamera(kirby).x, demo1.getcamera(kirby).y);
//				printf("\ncamera W: %d\ncamera D:%d\n", demo1.getcamera(kirby).w, demo1.getcamera(kirby).h);
				
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					pooh.setVX(pooh.getVX() - VELOCITY);
					kirby.setVX(kirby.getVX() - VELOCITY);
					break;
				case SDLK_RIGHT:
					pooh.setVX(pooh.getVX() + VELOCITY);
					kirby.setVX(kirby.getVX() + VELOCITY);
					break;
				case SDLK_DOWN:
//					break;
					pooh.setVY(pooh.getVY() + VELOCITY);
					kirby.setVY(kirby.getVY() + VELOCITY);
					break;
				case SDLK_UP:
//					break;
					pooh.setVY(pooh.getVY() - VELOCITY);
					kirby.setVY(kirby.getVY() - VELOCITY);
					break;
				case SDLK_SPACE:
					pooh.setJumpFlag(1);
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
					
				case SDLK_LEFT:
					pooh.setVX(pooh.getVX() + VELOCITY);
					kirby.setVX(kirby.getVX() + VELOCITY);
					break;
				case SDLK_RIGHT:
					pooh.setVX(pooh.getVX() - VELOCITY);
					kirby.setVX(kirby.getVX() - VELOCITY);
					break;
					
				case SDLK_UP:
//					break;
					pooh.setVY(pooh.getVY() + VELOCITY);
					kirby.setVY(kirby.getVY() + VELOCITY);
					break;
				case SDLK_DOWN:
//					break;
					pooh.setVY(pooh.getVY() - VELOCITY);
					kirby.setVY(kirby.getVY() - VELOCITY);
		  			break;
				case SDLK_SPACE:
					pooh.setJumpFlag(0);
					break;
				}
			}
			
		}
		

		test2 = demo1.getcamera(pooh);
		pooh.move(test2);
		window.clear();
		//kirby.move();
		test1 = demo1.getcamera(pooh);
		demo1.draw(window.getRenderer(), { ALLREGION }, demo1.getcamera(pooh));
		//pooh.draw(window.getRenderer());
		pooh.draw(window.getRenderer(), { pooh.getX()-test1.x,pooh.getY()-test1.y,pooh.getWidth()/4,pooh.getHeight()/4}, {NULL});
		window.display();

	}
	SDL_DestroyTexture(texture);
	demo1.close();
	kirby.close();
	window.close();
	sdl.close();

	return 0;
}

