#include "System.h"
#include <stdio.h>
#include <SDL.h> // Using SDL
#include <SDL_image.h>  // Using SDL2 image extension library 
#include <SDL_ttf.h> // Using truetype font


// SDL_mixer is a library we use to make audio playing easier 
// because original SDL audio api can get complicated.
// https://www.libsdl.org/projects/SDL_mixer/
// https://github.com/libsdl-org/SDL_mixer
// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
// Using SDL2_mixer
#include <SDL_mixer.h>


int System::init()
{	
	/****************************************************/
	// Initialize SDL	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		// Error Handling		
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}
	/****************************************************/
		
	// Initialize SDL_ttf		
	if (TTF_Init() == -1)
	{			
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}	
	

	// Initialize SDL_mixer
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_11.html
	// SDL must be initialized with SDL_INIT_AUDIO before this call. 
	// frequency would be 44100 for 44.1KHz, which is CD audio rate. 
	// Most games use 22050, because 44100 requires too much CPU power on older computers. 
	// chunksize is the size of each mixed sample. 
	// The smaller this is the more your hooks will be called. 
	// If make this too small on a slow system, sound may skip. 
	// If made to large, sound effects will lag behind the action more. 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}

	return 1;
}

void System::close()
{	
	// Quit Mixer subsystem
	// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_10.html
	Mix_Quit();

	// Shutdown and cleanup the truetype font API.		
	TTF_Quit();
	
	// Quit SDL subsystems
	SDL_Quit();
}


