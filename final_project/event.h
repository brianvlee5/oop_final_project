#pragma once
#include <SDL.h>
#include "AnimeObject.h"
#include "Attack.h"
#include "constants.h"
int toward;

void attackKeyboard(SDL_Event e, Attack& a, AnimeObject pooh) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_s:
			a.setDir(toward);
			a.setShownFlag(true);
			a.setPosition(pooh.getX(), pooh.getY());
			a.startTimerLine(25);
			break;
		case SDLK_a:
			a.setShownFlag(false);
			a.stopTimer();
			break;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{

		
	}
}
void poohKeyboard(SDL_Event e, AnimeObject& pooh) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
			pooh.startTimer(150);

		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			toward = -1;
			pooh.setVX(pooh.getVX() - VELOCITY);
			break;
		case SDLK_RIGHT:
			toward = 1;
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
		case SDLK_s:
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