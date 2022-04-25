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

	Coordinate coord;
	SDL_Rect forpooh;//for pooh's move
	AnimeObject pooh("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	pooh.setPosition( WIDTH / 2 - pooh.getWidth() / SHRINK, 370);
	pooh.startTimer(40);

	Map demo1("../images/mapdemo1.png", window.getRenderer());

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

		forpooh = demo1.getcamera(pooh);
		pooh.move(forpooh);
		window.clear();
		coord.calMapCamera(demo1, pooh);
		demo1.draw({ ALLREGION }, demo1.getcamera(pooh));
		pooh.draw({ coord.getpCX(), coord.getpCY(), pooh.getWidth() / SHRINK,pooh.getHeight() / SHRINK}, {NULL});
		window.display();
	}
	SDL_DestroyTexture(texture);
	pooh.close();
	demo1.close();
	window.close();
	sdl.close();

	return 0;
}