#pragma once
#include "Scene1.h"
#include "Window.h"
class Game
{
public:
	Scene1 *Scene1_;
	Window *Window_;
	Game();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute();
	bool run;
	bool loading;
	void Exit();
	~Game();
};

