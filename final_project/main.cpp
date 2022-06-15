#include "main.h"
using namespace std;

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



