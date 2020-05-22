#pragma once
#include "WindowsSDLApi.h"
#include <vector>
#include <algorithm>
#include <iterator>
struct chessai
{
	bool ai;
	int value;
};
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
	void CheckFinishGame();
	void AI(); 
	void ReccurentWalk();
	bool Move_UpAI(int i, int j);
	bool Move_DownAI(int i, int j);
	bool Move_RightAI(int i, int j);
	bool Move_LeftAI(int i, int j);
	bool Check_MoveLeft(int value);
	bool Check_MoveUp(int value);
	POINT FindMatrix(int value);
	bool Check_MoveDown(int value);
	bool Check_MoveRight(int value);
	bool run;
	void Exit();
	int** Matrix;
	int** QuadCoorXleft, **QuadCoorXright, **QuadCoorYup, **QuadCoorYdown;
	int  ActiveX,ActiveY,Active,oldx,oldy;
	double* ChessX,*ChessY;
	bool firstplayer, secondplayer,*ai;
	int current, currentI, currentJ;
	std::vector<chessai> Ai;
	~Game();
};

