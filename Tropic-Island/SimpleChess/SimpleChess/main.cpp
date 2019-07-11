#include <iostream>
#include "BasicGame.h"
//#include <SDL/SDL_main.h>

using namespace std;

int main(int argc, char**argv)
{
	setlocale(LC_ALL, "Russian");
	/*
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
	}
	SDL_Quit();
	*/
	BasicGame*game = new BasicGame();
	game->Execute();

	//std::cin.ignore();
	return 0;
}