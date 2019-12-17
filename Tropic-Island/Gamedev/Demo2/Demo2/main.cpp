
#include "Game.h"
#include <iostream>
//#include <SDL/SDL_main.h>
#include "md5.h"

using std::cout; using std::endl;

int main(int argc,char**argv)
{
	setlocale(LC_ALL, "Russian");
	/*
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();
	*/

	cout << "md5 of 'grape': " << md5("00000000") << endl;
	Game*game = new Game();
	game->Execute();
	
	//std::cin.ignore();
	return 0;
}