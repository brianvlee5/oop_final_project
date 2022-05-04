#pragma once
#include <SDL.h>
#include "AnimeObject.h"
#include "constants.h"

void poohKeyboard(SDL_Event e, AnimeObject& pooh) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if(e.key.keysym.sym== SDLK_LEFT|| e.key.keysym.sym == SDLK_RIGHT)
			pooh.startTimer(150);

		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			pooh.setVX(pooh.getVX() - VELOCITY);
			break;
		case SDLK_RIGHT:
			pooh.setVX(pooh.getVX() + VELOCITY);
			break;
/*		
		case SDLK_DOWN:
			pooh.setVY(pooh.getVY() + VELOCITY);
			break;
		case SDLK_UP:
			pooh.setVY(pooh.getVY() - VELOCITY);
			break;
*/		
		case SDLK_SPACE:
			pooh.setJumpFlag(1);
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		pooh.stopTimer();
		switch (e.key.keysym.sym)
		{

		case SDLK_LEFT:
			pooh.setVX(pooh.getVX() + VELOCITY);
			break;
		case SDLK_RIGHT:
			pooh.setVX(pooh.getVX() - VELOCITY);
			break;
/*
		case SDLK_UP:
			pooh.setVY(pooh.getVY() + VELOCITY);
			break;
		case SDLK_DOWN:
			pooh.setVY(pooh.getVY() - VELOCITY);
			break;
*/
		case SDLK_SPACE:
			pooh.setJumpFlag(0);
			break;
		}
	}
}