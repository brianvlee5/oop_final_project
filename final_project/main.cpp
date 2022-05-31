#include "main.h"

using namespace std;

//SDL_Texture* texture = NULL;
/*
void spacial_hash(const vector<Monster>& Mv, vector<vector<Monster>>& MvM)
{
	for (int i = 0; i < Mv.size(); i++)
	{
		//0 -> 1st quadrant, and so on
		if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[0].push_back(Mv[i]);
		else if (Mv[i].getX() >= WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[1].push_back(Mv[i]);
		else if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() >= HEIGHT / 2)
			MvM[2].push_back(Mv[i]);
		else
			MvM[3].push_back(Mv[i]);
	}
}*/

int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("Elden's rOng", 120, 50, WINDOWW, WINDOWH);
	GSManager gsm;

	gsm.startGame(window);

	window.close();
	sdl.close();
	

	return 0;
}



