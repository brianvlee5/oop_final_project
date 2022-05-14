#pragma once
#include <SDL.h>
#include "AnimeObject.h"
#include "AnimeObject2.h"
#include "Attack.h"
#include <math.h>
#include "constants.h"
int toward;
int ii = 0;
void attackKeyboard(SDL_Event e, Attack *a, AnimeObject2& p) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			if (!a[0].getShownFlag())
			{
				if (toward == 1)
					a[0].setFlip(SDL_FLIP_NONE);
				if (toward == -1)
					a[0].setFlip(SDL_FLIP_HORIZONTAL);
				a[0].setDir(toward);
				a[0].setShownFlag(true);
				a[0].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[0].startTimerLine(25);
			}
			else if(!a[ii + 1].getShownFlag())
			{
				if (toward == 1)
					a[1].setFlip(SDL_FLIP_NONE);
				if (toward == -1)
					a[1].setFlip(SDL_FLIP_HORIZONTAL);
				a[1].setDir(toward);
				a[1].setShownFlag(true);
				a[1].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[1].startTimerLine(25);
			}
			else if (!a[ii + 2].getShownFlag())
			{
				if (toward == 1)
					a[2].setFlip(SDL_FLIP_NONE);
				if (toward == -1)
					a[2].setFlip(SDL_FLIP_HORIZONTAL);
				a[2].setDir(toward);
				a[2].setShownFlag(true);
				a[2].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[2].startTimerLine(25);
			}
			else if (!a[ii + 3].getShownFlag())
			{
				if (toward == 1)
					a[3].setFlip(SDL_FLIP_NONE);
				if (toward == -1)
					a[3].setFlip(SDL_FLIP_HORIZONTAL);
				a[3].setDir(toward);
				a[3].setShownFlag(true);
				a[3].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[3].startTimerLine(25);
			}
/*			else if (!a[ii + 4].getShownFlag())
			{
				a[4].setDir(toward);
				a[4].setShownFlag(true);
				a[4].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[4].startTimerLine(25);
			}
			else if (!a[ii + 5].getShownFlag())
			{
				a[5].setDir(toward);
				a[5].setShownFlag(true);
				a[5].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[5].startTimerLine(25);
			}
*/
			break;
		case SDLK_w:
			if (!a[4].getShownFlag())
			{
				a[4].setDir(toward);
				a[4].setShownFlag(true);
				a[4].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[4].setVx(2 * VELOCITY);
				a[4].setVy(-4 * VELOCITY);
				a[4].startTimerParabola(25);
			}
			else if (!a[5].getShownFlag())
			{
				a[5].setDir(toward);
				a[5].setShownFlag(true);
				a[5].setPosition(p.getX() + p.getWidth() / 2, p.getY());
				a[5].setVx(2 * VELOCITY);
				a[5].setVy(-4 * VELOCITY);
				a[5].startTimerParabola(25);
			}
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
