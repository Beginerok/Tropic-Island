#pragma once

#include "Keyboard.h"
#include "Scene.h"
class BasicGame
{
public:
	Keyboard *keyboard_;
	Scene*scene_;
	BasicGame();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute();
	bool run;
	bool loading;
	void Exit();

	SDL_Window*window;
	SDL_Event event_;

	int iter;
	//Logic *Logic_;
	~BasicGame();
};

