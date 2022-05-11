#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h> // Using truetype font
#include "RenderWindow.h"
#include <SDL_mixer.h> // Using SDL2_mixer
#include "constants.h"
#include "Mixer.h"
/* New in this example */
#include "System.h"
#include "Fischinger.h"

using namespace std;
/***********************/
// Numbers of Fischinger components
const int WNUM = 16;
const int HNUM = 11;
void mouseHandleEvent(SDL_Event* e, Fischinger fcg);
// Mouse event handler
// Update activate status of Fischinger components when click on corresponding area of screen
void mouseHandleEvent(SDL_Event* e, Fischinger fcg)
{
	int x, y;
	// If mouse event happened
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		SDL_GetMouseState(&x, &y);
		if (e->button.button == SDL_BUTTON_LEFT && fcg.getActivate(y / fcg.getH(), x / fcg.getW()))
		{
			fcg.setActivate(false, y / fcg.getH(), x / fcg.getW());
		}
		else
		{
			fcg.setActivate(true, y / fcg.getH(), x / fcg.getW());
		}
	}
}
// When using SDL, you have to use "int main(int argc, char* args[])"
// int main() and void main() are not allowed
int main(int argc, char* args[])
{
	System sdl;
	// Start up SDL and create window
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("OOP SDL Tutorial", 20, 20, WIDTH, HEIGHT);
	// Initialize path of tone wave files
	char tone_Path[HNUM][100] = { "../audio/p01.mp3","../audio/p02.mp3", "../audio/p03.mp3", 
		"../audio/p04.mp3", "../audio/p05.mp3", "../audio/p06.mp3", 
		"../audio/p07.mp3", "../audio/p08.mp3", "../audio/p09.mp3", 
		"../audio/p10.mp3", "../audio/p11.mp3"
	 };
	// Declare Fischinger object
	
	Fischinger f(window.getRenderer(), HNUM, WNUM, tone_Path);
	for (int i = 0; i < HNUM; i++)
	{
		for (int j = 0; j < WNUM; j++)
		{
			//printf("%d %d\n", i * HEIGHT / HNUM, j * WIDTH / WNUM);
			window.addVPregion({ {  j * WIDTH / WNUM, i * HEIGHT / HNUM, WIDTH / WNUM, HEIGHT / HNUM} });
		}

	}
	// Initialize seed of random
	srand(12345);
	// start timer callback functions, runplay() and runEffect(), of Fischinger
	f.startRunPlay(500);
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			// Call mouse event handler
			mouseHandleEvent(&e, f);
		}
		
		// Clear screen
		window.clear();
		// Draw Fischinger components

		
		for (int i = 0; i < HNUM; i++)
		{
			for (int j = 0; j < WNUM; j++)
			{
				//printf("%d %d\n", i * HEIGHT / HNUM, j * WIDTH / WNUM);
				window.setVP(-1);
				f.draw(i, j, 0);
			}

		}

		for (int i = 0; i < HNUM; i++)
		{		
			for (int j = 0; j < WNUM; j++)
			{
				//printf("%d %d\n", i * HEIGHT / HNUM, j * WIDTH / WNUM);
				window.setVP(i*WNUM+j);
				f.draw(i, j, 1);
			}
			
		}

		

		
		// Update screen
		window.display();
	}
	// Free Fischinger object
	f.close();
	//Free resources and close SDL
	window.close();
	sdl.close();
	return 0;
}