#include "WindowsWinApi.h"

WindowsWinApi::WindowsWinApi()
{
	CountButtons = 10;
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
	int retval = -1;//5
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
	for (int i = 0; i < CountButtons; i++)
		F[i] = false;
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
	if ((keyboard__->msg_->message == WM_RBUTTONDOWN || keyboard__->msg_->message == WM_LBUTTONDOWN) && !bonus)
	{
		//std::cout << "DOWN" << std::endl;
		GetButtonDownCoords();
		if (point.y >460 && point.y<475)
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
			}
			if (point.x > 436 && point.x < 506)
				setF(true, 3);
			if (point.x >543 && point.x<608)
				setF(true, 4);
		}
		keyboard__->msg_->message = WM_NULL;
		return true;
	}
	else
		if ((keyboard__->msg_->message == WM_RBUTTONDOWN || keyboard__->msg_->message == WM_LBUTTONDOWN) && bonus)
		{
			//std::cout << "bonus_DOWN" << std::endl;
			GetButtonDownCoords();
			if ((point.y >290) && (point.y<373))
			{
				if ((point.x > 41) && (point.x < 129) && !getF(5))
					setF(true, 5);
				if ((point.x > 176) && (point.x < 260) && !getF(6))
					setF(true, 6);
				if ((point.x > 304) && (point.x < 393) && !getF(7))
					setF(true, 7);
				if ((point.x > 438) && (point.x < 527) && !getF(8))
					setF(true, 8);
				if ((point.x > 568) && (point.x < 655) && !getF(9))
					setF(true, 9);
			}
			keyboard__->msg_->message = WM_NULL;
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
	if ((keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP) && !bonus)
	{
		GetButtonDownCoords();
		//std::cout << "UP" << std::endl;
		if (getF(0))
			setF(false, 0);
		if (getF(1))
			setF(false, 1);
		if (getF(2))
		{
#if DBAPI_ == 1
			keyboard__->db->Query();
#else
			//Logic_->SetDrum();
#endif
			pressbutton = 1;
			upbutton = 0;
			setF(false, 2);
		}
		if (getF(3))
		{
			SetBet_(GetBet_() + 1);
			setF(false, 3);
		}
		if (getF(4))
		{
			setF(false, 4);
			setdone(true);
		}
		keyboard__->msg_->message = WM_NULL;
		return true;
	}
	else
		if ((keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP) && bonus)
		{
			//std::cout << "bonus_UP"<< std::endl;
			GetButtonDownCoords();
			if (getF(5))
				setF(false, 5);
			if (getF(6))
				setF(false, 6);
			if (getF(7))
				setF(false, 7);
			if (getF(8))
			{
				SetBet_(GetBet_() + 1);
				setF(false, 8);
			}
			if (getF(9))
				setF(false, 9);
			keyboard__->msg_->message = WM_NULL;
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
	//std::cout << "Coordinats x:" << keyboard__->x << "y:"<< keyboard__->y << std::endl;
	/*
	for (int i = 0; i < CountButtons; i++)
		if(F[i])
			std::cout << "[" << i << "]=" << std::endl;
			*/
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