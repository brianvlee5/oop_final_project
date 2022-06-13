#include "MonsterI.h"

MonsterI::MonsterI()
	:Monster()
{
	initialize();
}
MonsterI::MonsterI(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	initialize();
}

MonsterI::MonsterI(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	initialize();
}

void MonsterI::gotKey(AnimeObject2& mainch)
{
	if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
		mainch.getX() < getX() + getWidth() / SHRINK &&
		getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
		mainch.getY() < getY() + getHeight() / SHRINK &&
		mainch.getMapnum()==3)
	{

		setDeadFlag(true);
		mainch.setKey(true);
	}
}
void MonsterI::gateAABB(AnimeObject2& mainch)
{
	if (mainch.getVx() > 0)
	{
		if (getX() < mainch.getX() + mainch.getVx() + mainch.getWidth() / SHRINK &&
			mainch.getX() < getX() + getWidth() / SHRINK &&
			getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
			mainch.getY() < getY() + getHeight() / SHRINK)
		{
			if (mainch.getKey())
			{
				setDeadFlag(true);
			}
			else
				mainch.setGateFlag(true);
		}
		else
			mainch.setGateFlag(false);
	}
	else if (mainch.getVx() < 0)
	{
		if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
			mainch.getX() + mainch.getVx() < getX() + getWidth() / SHRINK &&
			getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
			mainch.getY() < getY() + getHeight() / SHRINK)
		{
			if (mainch.getKey())
				setDeadFlag(true);
			else
				mainch.setGateFlag(true);
		}
		else
			mainch.setGateFlag(false);
	}
	
	
}

void MonsterI::princessAABB(AnimeObject2& mainch)
{
	if (!mainch.getIVFlag())
	{
		if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
			mainch.getX() + mainch.getVx() < getX() + getWidth() / SHRINK &&
			getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
			mainch.getY() < getY() + getHeight() / SHRINK)
		{
			setWinFlag(true);
		}
	}
}

void MonsterI::setWinFlag(bool f)
{
	winFlag = f;
}
bool MonsterI::getWinFlag()
{
	return winFlag;
}

void MonsterI::setMchptr(AnimeObject2& mainch)
{

}

void MonsterI::startAI(Uint32 t)
{

}

void MonsterI::stopAI()
{

}

void MonsterI::initialize()
{
	winFlag = false;
}