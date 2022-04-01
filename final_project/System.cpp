#include <stdio.h>
#include <SDL.h>
#include "System.h"

int System::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}
}

void System::close()
{
	SDL_Quit();
}