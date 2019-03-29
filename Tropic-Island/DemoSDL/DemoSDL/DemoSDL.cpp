// DemoSDL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
	Game*game = new Game();
	game->Execute();
    return 0;
}

