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
#include "Attack.h"
#include "Image.h"
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

	Coordinate coord, coo, enemycord;
	SDL_Rect forpooh;//for pooh's move
	AnimeObject pooh("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Attack fire("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00);
	Monster enemy("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	pooh.setPosition(200, 370);
	enemy.setPosition(1320, 400);
	enemy.setVX(2);
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
			attackKeyboard(e, fire, pooh);
		}
		
		pooh.move();
		enemy.AIstart();
		demo1.setcamera(pooh);
		window.clear();
		coord.calMapCamera(demo1, pooh);
		coo.calMap(demo1, fire);
		enemycord.calMapCamera(demo1, enemy);
		demo1.draw({ ALLREGION }, demo1.getcamera());
		pooh.draw({coord.getpCX(),coord.getpCY(),pooh.getWidth() / SHRINK,pooh.getHeight() / SHRINK},{NULL});
		enemy.draw({ enemycord.getpCX(),enemycord.getpCY(),pooh.getWidth() / SHRINK,pooh.getHeight() / SHRINK }, { NULL });
		fire.draw({ ALLREGION }, { coo.getpCX(),coo.getpCY(),fire.getWidth(),fire.getHeight()});
		window.display();
	}
	SDL_DestroyTexture(texture);
	pooh.close();
	demo1.close();
	fire.close();
	window.close();
	sdl.close();

	return 0;
}