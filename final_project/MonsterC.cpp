#include "MonsterC.h"
MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	TPcd = 0;
}

MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	TPcd = 0;
}


void MonsterC::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}
void MonsterC::stopAI()
{
	AIinterval = 0;
}

Uint32 MonsterC::AIState(Uint32 interval, void* param)
{
	MonsterC* p = (MonsterC*)param;
	if (fabs(p->getX() - p->Mchptr->getX()) < 500 && fabs(p->getY() - p->Mchptr->getY()) < 75 && p->TPcd<=0)
		p->AImode = TELEPORT;
	else
		p->AImode = WAIT;

	switch (p->AImode)
	{
		case TELEPORT:
		{
			int dist;
			dist = rand() % 200;
			if (p->getX() - p->Mchptr->getX() < 0)
			{
				p->setVX(dist);
			}
			else if (p->getX() - p->Mchptr->getX() > 0)
			{
				p->setVX(-dist);
			}
			p->move();
			p->TPcd = 50;
			return interval;
			break;
		}
		case WAIT:
		{
			p->TPcd--;
			return interval;
			break;
		}
	}
}




void MonsterC::draw(SDL_Rect dst, SDL_Rect src)
{
	SDL_Rect* d = &dst, * s = &src;

	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}
//	thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	//thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}

void MonsterC::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}
void MonsterC::setAImode(int mode)
{
	AImode = mode;
}