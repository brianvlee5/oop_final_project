#include "System.h"
#include <SDL.h>
#include <stdio.h>
#include "SDL_image.h"

int System::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;  // load support for the JPG and PNG image formats
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 0;
	}
	return 1;
}

void System::close()
{
	IMG_Quit();
	SDL_Quit();
}