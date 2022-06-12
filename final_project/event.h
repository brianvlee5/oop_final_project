#pragma once
#include <SDL.h>
#include "AnimeObject2.h"
#include "Attack.h"
#include <math.h>
#include <stdlib.h>
#include "constants.h"
#include "GSManager.h"
#include "NPC.h"

static int toward = 1;


static void attackKeyboard(SDL_Event e, std::vector<Attack>& a, AnimeObject2& p) {
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
					a[0].setVx(2 * VELOCITY);
					a[0].startTimerLine(25);
				}
				else if (!a[1].getShownFlag())
				{
					if (toward == 1)
						a[1].setFlip(SDL_FLIP_NONE);
					if (toward == -1)
						a[1].setFlip(SDL_FLIP_HORIZONTAL);
					a[1].setDir(toward);
					a[1].setShownFlag(true);
					a[1].setPosition(p.getX() + p.getWidth() / 2, p.getY());
					a[1].setVx(2 * VELOCITY);
					a[1].startTimerLine(25);
				}
				break;
			case SDLK_w:
				if (!a[2].getShownFlag())
				{
					a[2].setDir(toward);
					a[2].setShownFlag(true);
					a[2].setPosition(p.getX() + p.getWidth() / 2, p.getY());
					a[2].setVx(2 * VELOCITY);
					a[2].setVy(-4 * VELOCITY);
					a[2].startTimerParabola(25);
				}
				else if (!a[3].getShownFlag())
				{
					a[3].setDir(toward);
					a[3].setShownFlag(true);
					a[3].setPosition(p.getX() + p.getWidth() / 2, p.getY());
					a[3].setVx(2 * VELOCITY);
					a[3].setVy(-4 * VELOCITY);
					a[3].startTimerParabola(25);
				}
				break;
			case SDLK_e:
				if (!a[4].getShownFlag())
				{
					a[4].setDir(toward);
					a[4].setShownFlag(true);
					a[4].setPosition(p.getX() + p.getWidth() / 2, p.getY());
					a[4].setVx(2 * VELOCITY);
					a[4].setVy(1 * VELOCITY);
					a[4].startTimerBounce(25);
				}
				else if (!a[5].getShownFlag())
				{
					a[5].setDir(toward);
					a[5].setShownFlag(true);
					a[5].setPosition(p.getX() + p.getWidth() / 2, p.getY());
					a[5].setVx(2 * VELOCITY);
					a[5].setVy(1 * VELOCITY);
					a[5].startTimerBounce(25);
				}
				break;
			case SDLK_r:
				int angle = rand() % 360;
				int r = sqrt((p.getHeight()/2) * (p.getHeight() / 2) + (p.getWidth()/2)* (p.getWidth() / 2)) * 6 / 4;
				for (int i = 6; i < 10; i++)
				{
					angle = (angle + 90) % 360;
					a[i].setShownFlag(true);
					a[i].startTimerMulti(20, r, angle);
				}
				break;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_b:
			for (int i = 0; i < a.size(); i++)
			{
				a[i].setMapnum(p.getMapnum());
			}
			break;
		}
	}
}

static void poohKeyboard(SDL_Event e, AnimeObject2& p) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
			p.startFrameTimer(150);
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
				toward = -1;
				p.setDir(-1);
				p.setFlip(SDL_FLIP_HORIZONTAL);
				p.setVx(p.getVx() - VELOCITY);
				break;
			case SDLK_RIGHT:
				toward = 1;
				p.setDir(1);
				p.setFlip(SDL_FLIP_NONE);
				p.setVx(p.getVx() + VELOCITY);
				break;
			case SDLK_SPACE:
				p.setJumpFlag(1);
				break;
			case SDLK_b:
				p.setMapFlag(1);
				break;
			case SDLK_f:
				p.startRush(20);
				break;
			case SDLK_2:
				p.usePotion();
				break;
			case SDLK_1:
				p.setKey(true);
				break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		p.stopFrameTimer();
		switch (e.key.keysym.sym)
		{

			case SDLK_LEFT:
				p.setVx(p.getVx() + VELOCITY);
				break;
			case SDLK_RIGHT:
				p.setVx(p.getVx() - VELOCITY);
				break;
			case SDLK_SPACE:
				p.setJumpFlag(0);
				break;
			case SDLK_b:
				p.setMapFlag(0);
				break;
		}
	}
}

static void npcKeyBoard(SDL_Event e, AnimeObject2& mainch, NPC& npc)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_b:
			{
				if (npc.npcAABB(mainch) && mainch.getPotionNum()<9)
				{
					mainch.setCoin(mainch.getCoin() - 5);
					mainch.setPotionNum(mainch.getPotionNum() + 1);

				}	
				break;
			}
				
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		
	}
}

