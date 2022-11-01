#pragma once
#define WINAPI_ 0
#define SDLAPI_ 1
#define QTAPI_ 0
#define DBAPI_ 0
#include "Scene1.h"
#include "Scene2.h"
#ifdef _WIN32
	#include "WindowsWinApi.h"
#else
	#include "WindowsSDLApi.h"
#endif
#include "Sound.h"
class Game
{
public:
	Scene1 *Scene1_;
	Sound* Sound_;
	Scene2* Scene2_;
#ifdef _WIN32
	WindowsWinApi *WindowsWinApi_;
#else
	SDL_Window*window;
	SDL_Event event_;
	WindowsSDLApi *WindowsSDLApi_;
#endif
	Game();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute(int argc,char*argv[]);
	bool run;
	bool loading;
	void Exit();
	int iter;
	Logic *Logic_;
	bool bonus,firsttime,online;
	~Game();
	float xx;
	bool wait,showline;
	std::time_t now;
	tm* ltm;
	int tmpcounter;
	int number;
};

