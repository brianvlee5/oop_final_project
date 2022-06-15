#include "System.h"
#include <SDL.h>
#include <stdio.h>
#include "SDL_image.h"
#include <SDL_ttf.h> 
#include <SDL_mixer.h>

System::System()
{
	failed = false;
}
System::System(bool f)
{
	failed = f;
}
int System::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		failed = true;
		return 0;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;  // load support for the JPG and PNG image formats
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		failed = true;
		return 0;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		failed = true;
		return 0;
	}
	return 1;
}

void System::close()
{
	IMG_Quit();
	SDL_Quit();
}