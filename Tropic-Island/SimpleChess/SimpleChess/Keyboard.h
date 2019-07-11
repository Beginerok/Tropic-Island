#ifndef keyboard_H
#define keyboard_H

#include <Windows.h>
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
//#pragma comment(lib,"ILU.lib")
//#pragma comment(lib,"DevIl.lib")
#pragma comment(lib,"SDL2.lib")
//#include "Logic.h"

class Keyboard
{
public:
	Keyboard();
	int getAny();
	void Update(SDL_Event event_);
	bool IsMouseButtonDown(byte key, SDL_Event event_);
	bool IsMouseButtonUp(byte key, SDL_Event event_);
	bool IsKeyDown(byte key, SDL_Event event_);
	bool IsKeyUp(byte key, SDL_Event event_);
	POINT GetButtonDownCoords(SDL_Event event_);
	bool IsExit(SDL_Event event_);
	byte GetPressedKey(SDL_Event event_);

	bool getdone();
	void setdone(bool state);
	bool getF(int n);
	void setF(bool status, int n);
	int GetBet_();
	void SetBet_(int bet_);
	int GetCountF();
	bool*GetF();
	bool GetAny();

	int pressbutton;
	virtual ~Keyboard();
protected:
	bool done;
	bool *F;
	int CountButtons;
	int bet;
	POINT point;
};
#endif