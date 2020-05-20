#pragma once
#include "WindowsSDLApi.h"
class Game
{
public:
	SDL_Window*window;
	SDL_Event event_;
	WindowsSDLApi *WindowsSDLApi_;
	Game();
	void draw_screen();
	void setup_opengl(int width, int height);
	int Execute(); 
	void BeganActive();
	void SetCoordinats();

	void Move_Up();

	void Move_Down();

	void Move_Right();

	void Move_Left();
	bool run;
	void Exit();
	int** Matrix;
	int** QuadCoorXleft, **QuadCoorXright, **QuadCoorYup, **QuadCoorYdown;
	int  ActiveX,ActiveY,Active,oldx,oldy;
	double* ChessX,*ChessY,ChessyX,ChessyY;
	~Game();
};

