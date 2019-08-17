#pragma once
#include "Scene1.h"
#define WINAPI_ 1
#define SDLAPI_ 0
#define QTAPI_ 0
#if WINAPI_ == 1
	#include "WindowsWinApi.h"
#else
	#include "WindowsSDLApi.h"
#endif
class Game
{
public:
	Scene1 *Scene1_;
#if WINAPI_ == 1
	WindowsWinApi *WindowsWinApi_;
#else
	SDL_Window*window;
	SDL_Event event_;
	WindowsSDLApi *WindowsSDLApi_;
#endif
	Game();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute();
	bool run;
	bool loading;
	void Exit();
	int iter;
	Logic *Logic_;
	bool bonus;
	~Game();
};

