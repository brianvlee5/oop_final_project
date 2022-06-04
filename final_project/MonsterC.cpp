#include "MonsterC.h"
MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	TPcd = 0;
}

MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	TPcd = 0;
}


void MonsterC::AIstate(AnimeObject2& mainch)
{

	if (fabs(getX() - mainch.getX()) < 500 && fabs(getY() - mainch.getY()) < 100)
		AImode = TRACE;
	else
		AImode = WANDER;

	switch (AImode)
	{
	case TRACE:
	{
		if (getX() - mainch.getX() < 0)
		{
			setVX(2);
			if (tile[getMapnum()][getDPX(1, 1) - 1][getDPX(1, 0)] == 0 && (tile[getMapnum()][getDPX(1, 1)][getDPX(1, 0)] == 1 || tile[getMapnum()][getDPX(3, 1)][getDPX(3, 0)] == 1))
				setJumpFlag(1);
		}
		else if (getX() - mainch.getX() > 0)
		{
			setVX(-2);
			if (tile[getMapnum()][getDPX(2, 1) - 1][getDPX(2, 0)] == 0 && (tile[getMapnum()][getDPX(2, 1)][getDPX(2, 0)] == 1 || tile[getMapnum()][getDPX(0, 1)][getDPX(0, 0)] == 1))
				setJumpFlag(1);
		}
		else
			setVX(0);
		break;
	}
	case WANDER:
	{
		if (tile[getMapnum()][getDPY(2, 1)][getDPY(2, 0)] == 0 && tile[getMapnum()][getDPY(3, 1)][getDPY(3, 0)] == 1)
			WANDERmode = PLATFORMLB;
		else if (tile[getMapnum()][getDPY(2, 1)][getDPY(2, 0)] == 1 && tile[getMapnum()][getDPY(3, 1)][getDPY(3, 0)] == 0)
			WANDERmode = PLATFORMRB;
		else if (tile[getMapnum()][getDPX(1, 1)][getDPX(1, 0)] == 1 || tile[getMapnum()][getDPX(3, 1)][getDPX(3, 0)] == 1)
			WANDERmode = WALLR;
		else if (tile[getMapnum()][getDPX(2, 1)][getDPX(2, 0)] == 1 || tile[getMapnum()][getDPX(0, 1)][getDPX(0, 0)] == 1)
			WANDERmode = WALLL;
		else
			WANDERmode = FLOOR;

		switch (WANDERmode)
		{
		case WALLL:
			setVX(2);
			break;
		case WALLR:
			setVX(-2);
			break;
		case PLATFORMLB:
			setVX(2);
			break;
		case PLATFORMRB:
			setVX(-2);
			break;
		case FLOOR:
		{

		}
		}
		break;
	}


	}

	move();

}

void MonsterC::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
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
			printf("tpcd: %d\n", p->TPcd);
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
	thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}

void MonsterC::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}