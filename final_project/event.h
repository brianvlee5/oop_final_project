#pragma once
#include <SDL.h>
#include "AnimeObject.h"
#include "AnimeObject2.h"
#include "Attack.h"
#include "constants.h"
int toward;
int ii = 0;
void attackKeyboard(SDL_Event e, Attack *a, AnimeObject2& p) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_s:
			if (!a[ii].getShownFlag())
			{
				a[ii].setDir(toward);
				a[ii].setShownFlag(true);
				a[ii].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii].startTimerLine(25);
			}
			else if(!a[ii + 1].getShownFlag())
			{
				a[ii + 1].setDir(toward);
				a[ii + 1].setShownFlag(true);
				a[ii + 1].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii + 1].startTimerLine(25);
			}
			else if (!a[ii + 2].getShownFlag())
			{
				a[ii + 2].setDir(toward);
				a[ii + 2].setShownFlag(true);
				a[ii + 2].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii + 2].startTimerLine(25);
			}
			else if (!a[ii + 3].getShownFlag())
			{
				a[ii + 3].setDir(toward);
				a[ii + 3].setShownFlag(true);
				a[ii + 3].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii + 3].startTimerLine(25);
			}
			else if (!a[ii + 4].getShownFlag())
			{
				a[ii + 4].setDir(toward);
				a[ii + 4].setShownFlag(true);
				a[ii + 4].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii + 4].startTimerLine(25);
			}
			else if (!a[ii + 5].getShownFlag())
			{
				a[ii + 5].setDir(toward);
				a[ii + 5].setShownFlag(true);
				a[ii + 5].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[ii + 5].startTimerLine(25);
			}
			break;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
	}
}
void poohKeyboard(SDL_Event e, AnimeObject2& pooh) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
			pooh.startTimer(150);

		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			toward = -1;
			pooh.setFlip(SDL_FLIP_HORIZONTAL);
			pooh.setVX(pooh.getVX() - VELOCITY);
			break;
		case SDLK_RIGHT:
			toward = 1;
			pooh.setFlip(SDL_FLIP_NONE);
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
		case SDLK_b:
			pooh.setMapFlag(1);
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
		case SDLK_b:
			pooh.setMapFlag(0);
			break;
		}
	}
}
