#include "NPC.h"
NPC::NPC(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{

}

NPC::NPC(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{

}

bool NPC::npcAABB(AnimeObject2& mainch)
{
	if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
		mainch.getX() + mainch.getVx() < getX() + getWidth() / SHRINK &&
		getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
		mainch.getY() < getY() + getHeight() / SHRINK)
	{
		return true;
	}
	else
		return false;
}

void NPC::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}
void NPC::stopAI()
{
	AIinterval = 0;
}

Uint32 NPC::AIState(Uint32 interval, void* param)
{
	return interval;
}




void NPC::draw(SDL_Rect dst, SDL_Rect src)
{
	SDL_Rect* d = &dst, * s = &src;
	/*
		if (dst.x == ALLREGION)
		{
			d = NULL;
		}
	*/
	if (src.x == ALLREGION)
	{
		s = NULL;
	}
	//thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	//thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}

void NPC::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}
void NPC::setAImode(int mode)
{
	AImode = mode;
}