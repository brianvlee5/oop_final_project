//original
#include <stdio.h>
#include <stdlib.h>

//sdl related
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "event.h"

//self added
#include "constants.h"
#include "System.h"
#include "RenderWindow.h"
#include "Map.h"
#include "StaticObject.h"
#include "AnimeObject.h"
#include "Coordinate.h"
#include "Monster.h"

SDL_Texture* texture = NULL;

int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("Elden's rOng", 300, 170, WINDOWW, WINDOWH);
	Monster enemy1("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Monster enemy2("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Monster enemy3("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Coordinate coord, enemy1cord, enemy2cord, enemy3cord;
	SDL_Rect forpooh;//for pooh's move
	AnimeObject pooh("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	pooh.setPosition( 200, 370);
	enemy1.setPosition(100, 370);
	enemy2.setPosition(1364, 400);
	enemy3.setPosition(2696, 1730);
	enemy1.setVX(2);
	enemy2.setVX(2);
	enemy3.setVX(2);
//	pooh.startTimer(40);

	Map demo1("../images/mapdemo4.png", window.getRenderer());

	SDL_Event e;

	bool quit = false;
	while (!quit)
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			poohKeyboard(e, pooh);
		}

		enemy1.AIstart();
		enemy2.AIstart();
		enemy3.AIstart();
		pooh.move();
		demo1.setcamera(pooh);
		window.clear();
		coord.calMapCamera(demo1, pooh);
		enemy1cord.calMapCamera(demo1, enemy1);
		enemy2cord.calMapCamera(demo1, enemy2);
		enemy3cord.calMapCamera(demo1, enemy3);
		demo1.draw({ ALLREGION }, demo1.getcamera());

		pooh.draw({ coord.getpCX(), coord.getpCY(), pooh.getWidth() / SHRINK,pooh.getHeight() / SHRINK}, {NULL});
		enemy1.draw({ enemy1cord.getpCX(), enemy1cord.getpCY(), enemy1.getWidth() / SHRINK,enemy1.getHeight() / SHRINK }, { NULL });
		enemy1.draw({ enemy2cord.getpCX(), enemy2cord.getpCY(), enemy2.getWidth() / SHRINK,enemy2.getHeight() / SHRINK }, { NULL });
		enemy1.draw({ enemy3cord.getpCX(), enemy3cord.getpCY(), enemy3.getWidth() / SHRINK,enemy3.getHeight() / SHRINK }, { NULL });
		window.display();
	}
	SDL_DestroyTexture(texture);
	pooh.close();
	demo1.close();
	window.close();
	sdl.close();

	return 0;
}