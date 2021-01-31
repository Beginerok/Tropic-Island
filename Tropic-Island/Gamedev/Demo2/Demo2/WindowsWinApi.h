#pragma once
#include <Windows.h>
#include "Logic.h"
#include "Window.h"

class WindowsWinApi
{
public:
	WindowsWinApi();
	~WindowsWinApi();

	int getAny();
	bool GetAny();
	bool getF(int n);
	void setF(bool status, int n);
	bool* GetF();

	void Update(bool bonus, Logic *Logic_);
	bool IsMouseButtonDown(byte key, bool bonus);
	bool IsMouseButtonUp(byte key, bool bonus/*, Logic *Logic_*/);
	bool IsKeyDown(byte key, bool bonus);
	bool IsKeyUp(byte key, bool bonus, Logic *Logic_);
	POINT GetButtonDownCoords();
	bool IsExit();
	byte GetPressedKey();

	bool getdone();
	void setdone(bool state);
	int GetBet_();
	void SetBet_(int bet_);
	int GetCountF();
	Window *keyboard__;
	int pressbutton;
	int upbutton;

protected:
	bool done;
	bool *F;
	int CountButtons;
	int bet;
	POINT point;

};

