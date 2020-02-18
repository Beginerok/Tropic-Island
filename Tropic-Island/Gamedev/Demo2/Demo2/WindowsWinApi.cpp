#include "WindowsWinApi.h"
#include <iostream>

WindowsWinApi::WindowsWinApi()
{
	CountButtons = 5;
	F = new bool[CountButtons];
	for (int i = 0; i<CountButtons; i++)
		setF(false, i);
	done = false;
	SetBet_(8);
	keyboard__ = new Window();
	pressbutton = 0;
	upbutton = 1;
}
int WindowsWinApi::getAny()
{
	int retval = 5;
	for (int i = 0; i<CountButtons; i++)
		if (getF(i))
			retval = i;
	return retval;
}
bool WindowsWinApi::GetAny()
{
	bool retval = false;
	for (int i = 0; i<CountButtons; i++)
		if (getF(i))
			retval = true;
	return retval;
}
bool WindowsWinApi::getF(int n)
{
	return F[n];
}
void WindowsWinApi::setF(bool status, int n)
{
	F[n] = status;
}
bool*WindowsWinApi::GetF()
{
	return F;
}
void WindowsWinApi::Update(bool bonus, Logic *Logic_)
{
	keyboard__->Update();
	IsMouseButtonDown(GetPressedKey(), bonus);
	IsMouseButtonUp(GetPressedKey(), bonus, Logic_);
	IsKeyDown(GetPressedKey(), bonus);
	IsKeyUp(GetPressedKey(), bonus, Logic_);
}
bool WindowsWinApi::IsMouseButtonDown(byte key, bool bonus)
{
	if (keyboard__->msg_->message == WM_RBUTTONDOWN || keyboard__->msg_->message == WM_LBUTTONDOWN && !bonus)
	{
		GetButtonDownCoords();
		if (point.y >478 && point.y<496)
		{
			if (point.x >123 && point.x<190)
				setF(true, 0);
			if (point.x >228 && point.x<296)
				setF(true, 1);
			if (point.x > 330 && point.x < 401)
			{
				upbutton += 1;
				setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
			}
			if (point.x > 436 && point.x < 506)
				setF(true, 3);
			if (point.x >543 && point.x<608)
				setF(true, 4);
		}
		return true;
	}
	else
		if (keyboard__->msg_->message == WM_RBUTTONDOWN || keyboard__->msg_->message == WM_LBUTTONDOWN && bonus && !GetAny())
		{
			GetButtonDownCoords();
			std::cout << point.x << " " << point.y << std::endl;
			if (point.y >478 && point.y<496)
			{
				if (point.x >123 && point.x<190)
					setF(true, 0);
				if (point.x >228 && point.x<296)
					setF(true, 1);
				if (point.x > 330 && point.x < 401)
				{
					upbutton += 1;
					setF(true, 2);
					pressbutton += 1;
					std::cout << "press button:" << pressbutton << std::endl;
				}
				if (point.x > 436 && point.x < 506)
					setF(true, 3);
				if (point.x >543 && point.x<608)
					setF(true, 4);
			}
			return true;
		}
	if (VK_RBUTTON == key)
	{
		GetButtonDownCoords();
		return true;
	}
	return false;
}
bool WindowsWinApi::IsMouseButtonUp(byte key, bool bonus, Logic *Logic_)
{
	if (keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP && !bonus)
	{
		GetButtonDownCoords();
		//if (point.y >478 && point.y<496)
		{
			//if (point.x >123 && point.x<190)
			if (getF(0))
				setF(false, 0);
			//if (point.x >228 && point.x<296)
			if (getF(1))
				setF(false, 1);
			//if (point.x >330 && point.x<401)
			if (getF(2))
			{
				pressbutton = 1;
				upbutton = 0;
				setF(false, 2);
				std::cout << "press button:" << pressbutton << std::endl;
				keyboard__->db->Query();
			}
			//if (point.x >436 && point.x<506)
			{
				if (getF(3))
				{
					SetBet_(GetBet_() + 1);
					setF(false, 3);
				}
			}
			//if (point.x >543 && point.x<608)
			{
				if (getF(4))
				{
					setF(false, 4);
					setdone(true);
				}
			}
		}
		return true;
	}
	else
		if (keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP && bonus && GetAny())
		{
			GetButtonDownCoords();
			//if (point.y >478 && point.y<496)
			{
				//if (point.x >123 && point.x<190)
				if (getF(0))
					setF(false, 0);
				//if (point.x >228 && point.x<296)
				if (getF(1))
					setF(false, 1);
				//if (point.x >330 && point.x<401)
				if (getF(2))
				{
					pressbutton = 1;
					upbutton = 0;
					setF(false, 2);
					std::cout << "press button:" << pressbutton << std::endl;
				}
				//if (point.x >436 && point.x<506)
				{
					if (getF(3))
					{
						SetBet_(GetBet_() + 1);
						setF(false, 3);
					}
				}
				//if (point.x >543 && point.x<608)
				{
					if (getF(4))
					{
						setF(false, 4);
						setdone(true);
					}
				}
			}
			return true;
		}
	if (VK_RBUTTON == key)
	{
		return true;
	}
	return false;
}

POINT WindowsWinApi::GetButtonDownCoords()
{
	point.x = keyboard__->x;
	point.y = keyboard__->y;
	//std::cout << "Coordinats x:" << event_.button.x << "y:"<< event_.button.y << std::endl;
	return point;
}
bool WindowsWinApi::IsKeyDown(byte key, bool bonus)
{
	if (keyboard__->msg_->message == WM_KEYDOWN && !bonus)
	{
		switch (key)
		{
		case VK_F1:
		{
			setF(true, 0);
			//setF(false, 0);
			break;
		}
		case VK_F2:
		{
			setF(true, 1);
			//setF(false, 1);
			break;
		}
		case VK_F3:
		{
			setF(true, 2);
			pressbutton += 1;
			std::cout << "press button:" << pressbutton << std::endl;
			//setF(false, 2);
			break;
		}
		case VK_F4:
		{
			//SetBet_(GetBet_()+1);
			setF(true, 3);
			//setF(false, 3);
			break;
		}
		case VK_F5:
		{
			setF(true, 4);
			//setF(false, 4);
			break;
		}
		}
		}
	else
		if (keyboard__->msg_->message == WM_KEYDOWN && bonus && !GetAny())
		{
			switch (key)
			{
			case VK_F1:
			{
				setF(true, 1);
				break;
			}
			case VK_F2:
			{
				setF(true, 0);
				break;
			}
			case VK_F3:
			{
				setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
				break;
			}
			case VK_F4:
			{
				setF(true, 3);
				break;
			}
			case VK_F5:
			{
				setF(true, 4);
				break;
			}
			}
			}
	return(true);
		}
bool WindowsWinApi::IsKeyUp(byte key, bool bonus, Logic *Logic_)
{
	if (keyboard__->msg_->message == WM_KEYUP && !bonus)
	{
		switch (key)
		{
		case VK_F1:
		{
			setF(false, 0);
			//setF(true, 0);
			break;
		}
		case VK_F2:
		{
			setF(false, 1);
			//setF(true, 1);
			break;
		}
		case VK_F3:
		{
			setF(false, 2);
			pressbutton = 0;
			std::cout << "press button:" << pressbutton << std::endl;
			//setF(true, 2);
			break;
		}
		case VK_F4:
		{
			if (getF(3))
				SetBet_(GetBet_() + 1);
			setF(false, 3);
			//setF(true, 3);
			break;
		}
		case VK_F5:
		{
			setF(false, 4);
			//setF(true, 4);
			setdone(true);
			break;
		}
		}
		}
	else
		if (keyboard__->msg_->message == WM_KEYUP && bonus && GetAny())
		{
			switch (key)
			{
			case VK_F1:
			{
				setF(false, 1);
				break;
			}
			case VK_F2:
			{
				setF(false, 0);
				break;
			}
			case VK_F3:
			{
				setF(false, 2);
				pressbutton = 0;
				std::cout << "press button:" << pressbutton << std::endl;
				//Logic_->SetRandom();
				Logic_->SetDrum();
				break;
			}
			case VK_F4:
			{
				setF(false, 3);
				break;
			}
			case VK_F5:
			{
				setF(false, 4);
				break;
			}
			}
			}
	return(true);
		}

byte WindowsWinApi::GetPressedKey()
{
	return keyboard__->wparam_;
}

bool WindowsWinApi::IsExit()
{
	return(keyboard__->msg_->message == WM_CLOSE);
}
bool WindowsWinApi::getdone()
{
	return done;
}
void WindowsWinApi::setdone(bool state)
{
	done = state;
}
int WindowsWinApi::GetBet_()
{
	return bet;
}
void WindowsWinApi::SetBet_(int bet_)
{
	if (bet_>8)
		bet = 0;
	else
		bet = bet_;
}
int WindowsWinApi::GetCountF()
{
	return CountButtons;
}

WindowsWinApi::~WindowsWinApi()
{
	delete F;
	delete keyboard__;
}