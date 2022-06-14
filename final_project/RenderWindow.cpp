#include "RenderWindow.h"
#include <stdio.h>

RenderWindow::RenderWindow()
{
	initialize();
}

RenderWindow::RenderWindow(const char* caption, int winx, int winy, int width, int height)
{
	// Create window	
	// SDL_WINDOWPOS_UNDEFINED: Used to indicate that you don't care what the window position is.
	window = SDL_CreateWindow(caption, winx, winy, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	// Create renderer	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	printf("SDL system initializes successfully!!!\n");
}

void RenderWindow::close()
{
	// Destroy renderer	
	// Destroy window		
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
}

void RenderWindow::clear(Uint32 color)
{
	SDL_SetRenderDrawColor(renderer, color / 0x1000000, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100);
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}

void RenderWindow::addVPregion(vector<SDL_Rect> r)
{
	for (int i = 0; i < r.size(); i++)
	{
		region.push_back(r[i]);
	}
}

void RenderWindow::setVP(int n)
{
	// SDL_RenderSetViewport
	if (n == ALLREGION)
	{
		// NULL to set the viewport to the entire target
		SDL_RenderSetViewport(renderer, NULL);
	}
	else
	{
		SDL_RenderSetViewport(renderer, &region[n]);
	}
}

int RenderWindow::getVPnum()
{
	return region.size();
}

SDL_Rect* RenderWindow::getRegion(int n)
{
	return &region[n];
}

void RenderWindow::clearVP()
{
	SDL_Rect fullViewport = { 0, 0, WIDTH, HEIGHT };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderFillRect(renderer, &fullViewport);
}

void RenderWindow::clearVP(Uint32 color)
{
	SDL_Rect fullViewport = { 0, 0, WIDTH, HEIGHT };

	SDL_SetRenderDrawColor(renderer, color / 0x1000000, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100);
	SDL_RenderFillRect(renderer, &fullViewport);
}

void RenderWindow::clearVP(Uint32 color, int n)
{
	SDL_Rect fullViewport = { 0, 0, WIDTH, HEIGHT };

	SDL_RenderSetViewport(renderer, &region[n]);

	SDL_SetRenderDrawColor(renderer, color / 0x1000000, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100);
	SDL_RenderFillRect(renderer, &fullViewport);
}

void RenderWindow::initialize()
{
	window = nullptr;
	renderer = nullptr;
}