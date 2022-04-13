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


	SDL_Event e;

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		Map demo1("../images/mapdemo1.png", window.getRenderer());

		window.clear();

		demo1.draw(window.getRenderer(), { ALLREGION }, { 300, 307, 150, 150 });

		window.display();

	}
	

	SDL_DestroyTexture(texture);

	window.close();
	sdl.close();

	return 0;
}