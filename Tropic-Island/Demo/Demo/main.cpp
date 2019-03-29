
#include "Game.h"
#include <iostream>

int main()
{
	Game*game = new Game();
	game->Execute();
	std::cout << "Hello world!\n";
	std::cin.ignore();
	return 0;
}