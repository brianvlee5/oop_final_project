#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include <SDL_image.h>
#include <SDL_ttf.h> // Using truetype font
#include "RenderWindow.h"
#include <SDL_mixer.h> // Using SDL2_mixer
#include "constants.h"
#include "Mixer.h"
/* New in this example */
#include "System.h"
#include "Fischinger.h"
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
		if (e->button.button == SDL_BUTTON_LEFT && fcg.getActivate(y/ fcg.getH(), x/ fcg.getW())==0)
		{
			fcg.setActivate(1, y / fcg.getH(), x / fcg.getW());
		}
		else
		{
			fcg.setActivate(0, y / fcg.getH(), x / fcg.getW());
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
	RenderWindow window("OOP SDL Tutorial", 100, 40, WIDTH, HEIGHT);
	// Initialize path of tone wave files
	char tone_Path[HNUM][100] = { "../audio/s01.wav", "../audio/s02.wav", "../audio/s03.wav", "../audio/s04.wav", 
		"../audio/s05.wav", "../audio/s06.wav", "../audio/s07.wav", "../audio/s08.wav", "../audio/s09.wav", "../audio/s10.wav", "../audio/s11.wav"};
	// Declare Fischinger object
	Fischinger f(window.getRenderer(), HNUM, WNUM, tone_Path);

	for (int i = 0; i < HNUM; i++)
		for (int j = 0; j < WNUM; j++)
			window.addVPregion({ {  j * WIDTH / WNUM, i * HEIGHT / HNUM, WIDTH / WNUM, HEIGHT / HNUM} });
	
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
			for (int j = 0; j < WNUM; j++) {
				window.setVP(-1);
				f.draw(i, j, 1);
			}
		for (int i = 0; i < HNUM; i++)
			for (int j = 0; j < WNUM; j++) {
				window.setVP(i * WNUM + j);
				f.draw(i, j, 0);
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