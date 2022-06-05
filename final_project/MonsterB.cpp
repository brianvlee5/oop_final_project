#include "MonsterB.h"


MonsterB::MonsterB(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{

}

MonsterB::MonsterB(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{

}

Uint32 MonsterB::AIState(Uint32 interval, void* param)
{
	MonsterB* p = (MonsterB*)param;

	switch (p->AImode)
	{
		case WAIT:
		{
			if (p->WaitTime > 0)
			{
				p->WaitTime--;
			}
			else
			{
				p->AImode = WANDER;
				p->WanderTime = 50;

				if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 0 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 1)
					p->WANDERmode = RIGHT;
				else if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 1 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 0)
					p->WANDERmode = LEFT;
				else if (tile[p->getMapnum()][p->getDPX(1, 1)][p->getDPX(1, 0)] == 1 || tile[p->getMapnum()][p->getDPX(3, 1)][p->getDPX(3, 0)] == 1)
					p->WANDERmode = LEFT;
				else if (tile[p->getMapnum()][p->getDPX(2, 1)][p->getDPX(2, 0)] == 1 || tile[p->getMapnum()][p->getDPX(0, 1)][p->getDPX(0, 0)] == 1)
					p->WANDERmode = RIGHT;
				else
					p->WANDERmode = rand() % 2;
			}
			return interval;
			break;
		}
		case WANDER:
		{
			if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 0 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 1)
			{
				p->WaitTime = 50;
				p->AImode = WAIT;
			}
			else if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 1 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 0)
			{
				p->WaitTime = 50;
				p->AImode = WAIT;
			}
			else if (tile[p->getMapnum()][p->getDPX(1, 1)][p->getDPX(1, 0)] == 1 || tile[p->getMapnum()][p->getDPX(3, 1)][p->getDPX(3, 0)] == 1)
			{
				p->WaitTime = 50;
				p->AImode = WAIT;
			}
			else if (tile[p->getMapnum()][p->getDPX(2, 1)][p->getDPX(2, 0)] == 1 || tile[p->getMapnum()][p->getDPX(0, 1)][p->getDPX(0, 0)] == 1)
			{
				p->WaitTime = 50;
				p->AImode = WAIT;
			}
			else if (p->WanderTime > 0)
			{
				if (p->WANDERmode == LEFT)
					p->setVX(2);
				else
					p->setVX(-2);

				p->move();
				p->WanderTime--;
			}
			else
			{
				p->WaitTime = 50;
				p->AImode = WAIT;
			}

			return interval;
			break;
		}
	}
}

void MonsterB::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}

void MonsterB::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}


void MonsterB::draw(SDL_Rect dst, SDL_Rect src)
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
	thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}