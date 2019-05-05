#pragma once
#include "Scene1.h"
//#include "Window.h"
#include "keyboard.h"
class Game
{
public:
	Scene1 *Scene1_;
	keyboard *keyboard_;
#ifdef _WINDOWS_2
	Window *Window_;
#endif
	Game();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute();
	bool run;
	bool loading;
	void Exit();
#ifndef _WINDOWS_2
	SDL_Window*window;
	SDL_Event event_;
#endif
	int iter;
	Logic *Logic_;
	~Game();
};

