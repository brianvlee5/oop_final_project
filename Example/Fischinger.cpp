#include "Fischinger.h"
#include "constants.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
Fischinger::Fischinger()
{
}
// 1. Set renderer, hnum and wnum
// 2. Create array of Fischinger components
// 3. Initialize the values of data members of all Fischinger components
Fischinger::Fischinger(SDL_Renderer* ren, int hn, int wn, char tone_Path[][100])
{
	// Set renderer, hnum and wnum
	renderer = ren;
	// Create array of Fischinger components
	fcg = new Fisch * [hn];
	for (int i = 0; i < hn; i++)
		fcg[i] = new Fisch[wn];

	// Initialize the values of data members of all Fischinger components
	for (int i = 0; i < hn; i++) {
		for (int j = 0; j < wn; j++) {
			fcg[i][j].w = WIDTH / wn;
			fcg[i][j].h = HEIGHT / hn;

			fcg[i][j].tone.setPath(tone_Path[i]);
			fcg[i][j].tone.setType(EFFECT);
			fcg[i][j].tone.load();

			fcg[i][j].effectActivate = false;
			fcg[i][j].activate = false;
			fcg[i][j].runActivate = false;

			fcg[i][j].r = 2;
			fcg[i][j].alpha = rand()%255;
			if (fcg[i][j].alpha > 170)
				fcg[i][j].alpha = 170;
			fcg[i][j].cr = rand() % 255, fcg[i][j].cg = rand() % 255, fcg[i][j].cb = rand() % 255;
		}
	}
	hnum = hn;
	wnum = wn;
}
// Set the activate status of Fischinger component [hn][wn]
void Fischinger::setActivate(bool a, int hn, int wn)
{
	fcg[hn][wn].activate = a;
}
// Get the activate status of Fischinger component [hn][wn]
bool Fischinger::getActivate(int hn, int wn)
{
	return fcg[hn][wn].activate;
}
// Get the width of each Fischinger component
// Because each component is equal in size, you can choose any one of them
int Fischinger::getW()
{
	return fcg[0][0].w;
}
// Get the height of each Fischinger component
// Because each component is equal in size, you can choose any one of them
int Fischinger::getH()
{
	return fcg[0][0].h;
}
// Draw visual music on renderer according to parameters of Fischinger components
// 1. Draw basic components or activate components or runActivate components according to activate / runActivate status of Fischinger components
// 2. Draw visual effects according to effectActivate status of Fischinger components
//
//https ://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html
void Fischinger::draw(int i, int j, bool a)
{
	if (a==0)
	{
		if (fcg[i][j].runActivate == 0)
		{
			if (getActivate(i, j))
			{
				filledCircleColor(renderer, getW() / 2, getH() / 2, 5, 0xAA00BBFF);
			}
			else
				circleColor(renderer, getW() / 2, getH() / 2, 5, 0xAA00BBFF);
		}
		else
		{
			filledCircleColor(renderer, getW() / 2, getH() / 2, 5, 0xAAAABBCC);
		}
	}
	else {
		if (fcg[i][j].effectActivate)
		{
			if (fcg[i][j].r < 500)
			{
				int n = i + j;
				switch (n%3)
				{
				case 0:
					rectangleRGBA(renderer, getW() * j + getW() / 2 - fcg[i][j].r, getH() * i + getH() / 2 - fcg[i][j].r, getW() * j + getW() / 2 + fcg[i][j].r, getH() * i + getH() / 2 + fcg[i][j].r
						, fcg[i][j].cr, fcg[i][j].cg, fcg[i][j].cb, fcg[i][j].alpha);
					break;
				case  1:
					aaFilledEllipseRGBA(renderer, getW() * j + getW() / 2, getH() * i + getH() / 2, fcg[i][j].r, fcg[i][j].r, fcg[i][j].cr, fcg[i][j].cg, fcg[i][j].cb, fcg[i][j].alpha);
					break;
				case 2:
					aacircleRGBA(renderer, getW() * j + getW() / 2, getH() * i + getH() / 2, fcg[i][j].r, fcg[i][j].cr, fcg[i][j].cg, fcg[i][j].cb, fcg[i][j].alpha);
					break;
				}
				fcg[i][j].r++;
				fcg[i][j].alpha--;
			}
			else if(fcg[i][j].r>50 || fcg[i][j].alpha<0)
			{
				fcg[i][j].r = 2;
				fcg[i][j].alpha = 125;
				fcg[i][j].effectActivate = 0;
			}
	
		}
	}
}
// Start running timer callback funtion
void Fischinger::startRunPlay(Uint32 t)
{
	timerRPid = SDL_AddTimer(t, runPlay, this); // Set Timer callback
}
// Start running timer callback funtion
void Fischinger::startRunEffect(Uint32 t)
{
	timerREid = SDL_AddTimer(t, runEffect, this);
}
// 1. Free the sound effects by using Mix_FreeMusic()/Mix_FreeChunk()
// 2. Delete fcg components
// 3. Remove timer by timer id
void Fischinger::close()
{
	// Free the sound effects and fcg components
	for (int i = 0; i < hnum; i++)
		for (int j = 0; j < wnum; j++)
			fcg[i][j].tone.close();
	for (int i = 0; i < hnum; i++)
		delete[]fcg[i];
	delete[]fcg;
	// Remove timer in case the call back was not called
	SDL_RemoveTimer(timerRPid);
	SDL_RemoveTimer(timerREid);
}
// Timer callback function
// 1. Update runActivate status of Fischinger components
// 2. Play tone and update effectActivate status according to active status of Fischinger components
// Hint: you can use static variable if needed
Uint32 Fischinger::runPlay(Uint32 interval, void* param)
{
	static int num = 0;
	Fischinger* p = (Fischinger*)param;

	for (int i = 0; i < 11; i++)
	{
		if (num == 0)
		{
			p->fcg[i][15].runActivate = false;
		}
		else
		{
			p->fcg[i][num - 1].runActivate = false;
		}
		p->fcg[i][num].runActivate = true;

		if (p->fcg[i][num].runActivate && p->fcg[i][num].activate)
		{
			p->fcg[i][num].tone.playEffect(0);
			p->fcg[i][num].effectActivate = true;
		}
	}
	num = (num + 1) % 16;
	return interval;
}
// Timer callback function
// 1. Update visual effects parameters according to effectActivate status of Fischinger components
// 2. Reset visual effects parameters of Fischinger components if the stop requirement of effect meets
// You can determine the stop requirement by yourself. EX: judge the radius size or alpha channel of color
Uint32 Fischinger::runEffect(Uint32 interval, void* param)
{
	Fischinger* p = (Fischinger*)param;
/*
	for (int i = 0; i < p->hnum; i++) {
		for (int j = 0; j < p->wnum; j++) {
			if (p->fcg[i][j].effectActivate) {
				p->fcg[i][j].alpha--;
				p->fcg[i][j].r += 3;

				if (p->fcg[i][j].alpha < 0)
					p->fcg[i][j].r = 0, p->fcg[i][j].alpha = 125;
				if (p->fcg[i][j].r > 250)
					p->fcg[i][j].r = 0;
			}
		}
	}
*/
	return interval;

}