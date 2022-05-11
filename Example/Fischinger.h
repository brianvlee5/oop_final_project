#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_mixer.h>
#include "Mixer.h"
class Fischinger
{
public:
	Fischinger();
	Fischinger(SDL_Renderer* renderer, int hn, int wn, char tone_Path[][100]);
	void setActivate(bool a, int hn, int wn);
	bool getActivate(int hn, int wn);
	int getW();
	int getH();
	void draw(int i, int j, bool a);
	void startRunPlay(Uint32 t);
	void startRunEffect(Uint32 t);
	void close();
private:
	struct Fisch
	{
		// for tone
		bool activate; // true: selected by user, false: deselected by user
		bool runActivate; // true: playing tone, false: not playing tone
		int w; // width of each compoenent
		int h; // height of each compoenent
		Mixer tone; // Mixer Chunk of tone
		// for visual effect
		bool effectActivate; // true: playing effect
		int r; // radius of effect
		int alpha; // alpha channel
		int cr, cg, cb; // colors of r, g ,b
	} **fcg;
	SDL_Renderer* renderer;
	int hnum; // Fischinger element numbers of height
	int wnum; // Fischinger element numbers of width
	SDL_TimerID timerRPid;
	SDL_TimerID timerREid;
	static Uint32 runPlay(Uint32 interval, void* param); // Timer callback
	static Uint32 runEffect(Uint32 interval, void* param); // Timer callback
};