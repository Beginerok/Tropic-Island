#pragma once
#define WINAPI_ 1
#define SDLAPI_ 0
#define QTAPI_ 0
#define DBAPI_ 0
#include "Scene1.h"
//#include "Scene2.h"
#if WINAPI_ == 1
	#include "WindowsWinApi.h"
#elif SDLAPI_ == 1
	#include "WindowsSDLApi.h"
#elif QTAPI_ == 1	
	#include <QtWidgets/QApplication>
	#include "MyWidget.h"
	#include "Logic.h"
#endif
#include "Sound.h"

class Game
{
public:
	Scene1 *Scene1_;
	Sound* Sound_;
	//Scene2* Scene2_;
#if WINAPI_ == 1
	WindowsWinApi *WindowsWinApi_;
#elif SDLAPI_ == 1
	SDL_Window*window;
	SDL_Event event_;
	WindowsSDLApi *WindowsSDLApi_;
#elif QTAPI_ == 1

#endif
	Game();
#if WINAPI_==1 || SDLAPI_==1
	void draw_screen();
	void setup_opengl(int width, int height);
#endif
	int Execute(int argc,char*argv[]);
	bool run;
	bool loading;
	void Exit();
	int iter;
	Logic *Logic_;
	bool bonus,firsttime,online;
	~Game();
	bool wait,showline;
	int tmpcounter;
	int number;
};

