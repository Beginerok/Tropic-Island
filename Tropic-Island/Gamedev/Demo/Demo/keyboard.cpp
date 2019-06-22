#include "keyboard.h"
keyboard::keyboard()
{
	CountButtons=5;
	F=new bool[CountButtons];
	for(int i=0;i<CountButtons;i++)
		setF(false,i);
	done = false;
	SetBet_(8);
#ifdef _WINDOWS_2
	keyboard__=new Keyboard();
#endif
	pressbutton = 0;
}
int keyboard::getAny()
{
	int retval=5;
	for(int i=0;i<CountButtons;i++)
		if(getF(i))
			retval=i;
	return retval;
}
bool keyboard::GetAny()
{
	bool retval = false;
	for (int i = 0; i<CountButtons; i++)
		if (getF(i))
			retval = true;
	return retval;
}
bool keyboard::getF(int n)
{
	return F[n];
}
void keyboard::setF(bool status,int n)
{
	F[n] = status;
}
bool*keyboard::GetF()
{
	return F;
}
#ifndef _WINDOWS_2
    void keyboard::Update(bool bonus, Logic *Logic_,SDL_Event event_)
#else
    void__ keyboard::Update(bool bonus, Logic *Logic_)
#endif
{
#ifdef _WINDOWS_2
	keyboard__->Update();
	IsMouseButtonDown(GetPressedKey(),bonus);
	IsMouseButtonUp(GetPressedKey(), bonus, Logic_);
	IsKeyDown(GetPressedKey(), bonus);
	IsKeyUp(GetPressedKey(), bonus,Logic_);
#else
	IsMouseButtonDown(GetPressedKey(event_),bonus,event_);
	IsMouseButtonUp(GetPressedKey(event_), bonus, Logic_,event_);
	IsKeyDown(GetPressedKey(event_), bonus,event_);
	IsKeyUp(GetPressedKey(event_), bonus,Logic_,event_);
#endif
}
#include <iostream>

#ifdef _WINDOWS_2
    bool keyboard::IsMouseButtonDown(byte key,bool bonus)
#else
    bool keyboard::IsMouseButtonDown(byte key,bool bonus,SDL_Event event_)
#endif
{
#ifndef _WINDOWS_2
    SDL_PollEvent(&event_);
#endif
#ifdef _WINDOWS_2
	if(keyboard__->msg_->message==WM_RBUTTONDOWN || keyboard__->msg_->message==WM_LBUTTONDOWN &&!bonus)
#else
    if(event_.type == SDL_MOUSEBUTTONDOWN && !bonus)
#endif
	{

#ifdef _WINDOWS_2
		GetButtonDownCoords();
#else
		GetButtonDownCoords(event_);

#endif
		if(point.y >478 && point.y<496)
		{
			if(point.x >123 && point.x<190)
				setF(true, 0);
			if(point.x >228 && point.x<296)
				setF(true, 1);
			if (point.x > 330 && point.x < 401)
			{
				setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
			}
			if (point.x > 436 && point.x < 506)
				setF(true, 3);
			if(point.x >543 && point.x<608)
				setF(true, 4);
		}
		return true;
	}
	else

#ifdef _WINDOWS_2
		if (keyboard__->msg_->message == WM_RBUTTONDOWN || keyboard__->msg_->message == WM_LBUTTONDOWN && bonus&& !GetAny())
#else
    if(event_.type == SDL_MOUSEBUTTONDOWN && bonus&&!GetAny())
#endif
		{
#ifdef _WINDOWS_2
			GetButtonDownCoords();
#else
			GetButtonDownCoords(event_);
#endif
			std::cout << point.x << " " << point.y<<std::endl;
			if (point.y >478 && point.y<496)
			{
				if (point.x >123 && point.x<190)
					setF(true, 0);
				if (point.x >228 && point.x<296)
					setF(true, 1);
				if (point.x > 330 && point.x < 401)
				{
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

#ifdef _WINDOWS_2
	if(VK_RBUTTON==key)
#else
    if(event_.type == SDL_MOUSEBUTTONDOWN)
#endif
	{
#ifdef _WINDOWS_2
		GetButtonDownCoords();
#else
		GetButtonDownCoords(event_);
#endif
		return true;
	}
	return false;
}

#ifndef _WINDOWS_2
    bool keyboard::IsMouseButtonUp(byte key, bool bonus, Logic *Logic_,SDL_Event event_)
#else
    bool keyboard::IsMouseButtonUp(byte key, bool bonus, Logic *Logic_)
#endif
{
#ifndef _WINDOWS_2
    SDL_PollEvent(&event_);
#endif
#ifdef _WINDOWS_2
	if(keyboard__->msg_->message==WM_RBUTTONUP || keyboard__->msg_->message==WM_LBUTTONUP &&!bonus)
#else
    if(event_.type == SDL_MOUSEBUTTONUP && !bonus)
#endif
	{
#ifdef _WINDOWS_2
		GetButtonDownCoords();
#else
		GetButtonDownCoords(event_);
#endif
		//if (point.y >478 && point.y<496)
		{
			//if (point.x >123 && point.x<190)
			if(getF(0))
				setF(false, 0);
			//if (point.x >228 && point.x<296)
			if (getF(1))
				setF(false, 1);
			//if (point.x >330 && point.x<401)
			if (getF(2))
			{
				setF(false, 2);
				pressbutton = 0;
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
	else

#ifdef _WINDOWS_2
		if (keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP && bonus && GetAny())
#else
    if(event_.type == SDL_MOUSEBUTTONUP && bonus&&!GetAny() && event_.key.repeat == 0)
#endif
		{
#ifdef _WINDOWS_2			
			GetButtonDownCoords();
#else
			GetButtonDownCoords(event_);
#endif
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
					setF(false, 2);
					pressbutton = 0;
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
#ifdef _WINDOWS_2
	if(VK_RBUTTON==key)
#else
    if(event_.type == SDL_MOUSEBUTTONDOWN)
#endif
    {
		return true;
	}
	return false;
}

#ifndef _WINDOWS_2
    POINT keyboard::GetButtonDownCoords(SDL_Event event_)
#else
    POINT keyboard::GetButtonDownCoords()
#endif
{
#ifdef _WINDOWS_2
	point.x=keyboard__->x;
	point.y=keyboard__->y;
#else
	point.x=event_.button.x;
	point.y=event_.button.y;
	//std::cout << "Coordinats x:" << event_.button.x << "y:"<< event_.button.y << std::endl;
#endif
	return point;
}
#ifdef _WINDOWS_2
    bool keyboard::IsKeyDown(byte key, bool bonus)
#else
    bool keyboard::IsKeyDown(byte key, bool bonus,SDL_Event event_)
#endif // _WINDOWS_2
{
#ifndef _WINDOWS_2
    SDL_PollEvent(&event_);
#endif
#ifdef _WINDOWS_2
	if (keyboard__->msg_->message == WM_KEYDOWN && !bonus)
#else
    if(event_.type == SDL_KEYDOWN && !bonus && event_.key.repeat == 0)
#endif
	{
#ifdef _WINDOWS_2
		switch (key)
        {
#else
        switch(event_.key.keysym.sym)
        {
#endif // _WINDOWS_2
#ifdef _WINDOWS_2
            case VK_F1:
#else
            case SDLK_F1:
#endif
            {
                setF(true, 0);
                //setF(false, 0);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F2:
#else
            case SDLK_F2:
#endif
            {
                setF(true, 1);
                //setF(false, 1);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F3:
#else
            case SDLK_F3:
#endif
            {
                setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
                //setF(false, 2);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F4:
#else
            case SDLK_F4:
#endif
            {
                //SetBet_(GetBet_()+1);
                setF(true, 3);
                //setF(false, 3);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F5:
#else
            case SDLK_F5:
#endif
            {
                setF(true, 4);
                //setF(false, 4);
                break;
            }
		}
	}
	else
#ifdef _WINDOWS_2
		if (keyboard__->msg_->message == WM_KEYDOWN && bonus && !GetAny())
#else
        if(event_.type == SDL_KEYDOWN && bonus && !GetAny() && event_.key.repeat == 0)
#endif
		{
#ifdef _WINDOWS_2
            switch (key)
            {
#else
            switch(event_.key.keysym.sym)
            {
#endif // _WINDOWS_2
#ifdef _WINDOWS_2
                case VK_F1:
#else
                case SDLK_F1:
#endif
                {
                    setF(true, 1);
                    break;
                }
#ifdef _WINDOWS_2
                case VK_F2:
#else
                case SDLK_F2:
#endif
                {
                    setF(true, 0);
                    break;
                }
#ifdef _WINDOWS_2
                case VK_F3:
#else
                case SDLK_F3:
#endif
                {
                    setF(true, 2);
					pressbutton += 1;
					std::cout << "press button:" << pressbutton << std::endl;
                    break;
                }
#ifdef _WINDOWS_2
                case VK_F4:
#else
                case SDLK_F4:
#endif
                {
                    setF(true, 3);
                    break;
                }
#ifdef _WINDOWS_2
                case VK_F5:
#else
                case SDLK_F5:
#endif
                {
                    setF(true, 4);
                    break;
                }
			}
		}
	return(true);
}
#ifndef _WINDOWS_2
    bool keyboard::IsKeyUp(byte key, bool bonus,Logic *Logic_, SDL_Event event_)
#else
    bool__ keyboard::IsKeyUp(byte key, bool bonus,Logic *Logic_)
#endif
{
#ifndef _WINDOWS_2
    SDL_PollEvent(&event_);
#endif
#ifdef _WINDOWS_2
	if (keyboard__->msg_->message == WM_KEYUP && !bonus)
#else
    if(event_.type == SDL_KEYUP && !bonus)
#endif
	{
#ifdef _WINDOWS_2
		switch (key)
		{
#else
        switch(event_.key.keysym.sym)
        {
#endif // _WINDOWS_2
#ifdef _WINDOWS_2
            case VK_F1:
#else
            case SDLK_F1:
#endif
            {
                setF(false, 0);
                //setF(true, 0);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F2:
#else
            case SDLK_F2:
#endif
            {
                setF(false, 1);
                //setF(true, 1);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F3:
#else
            case SDLK_F3:
#endif
            {
                setF(false, 2);
				pressbutton = 0;
				std::cout << "press button:" << pressbutton << std::endl;
                //setF(true, 2);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F4:
#else
            case SDLK_F4:
#endif
            {
                if (getF(3))
                    SetBet_(GetBet_() + 1);
                setF(false, 3);
                //setF(true, 3);
                break;
            }
#ifdef _WINDOWS_2
            case VK_F5:
#else
            case SDLK_F5:
#endif
            {
                setF(false, 4);
                //setF(true, 4);
                setdone(true);
                break;
            }
		}
	}else
#ifdef _WINDOWS_2
	if (keyboard__->msg_->message == WM_KEYUP && bonus && GetAny())
#else
    if(event_.type == SDL_KEYUP && bonus && GetAny())
#endif
	{
#ifdef _WINDOWS_2
		switch (key)
		{
#else
        switch(event_.key.keysym.sym)
        {
#endif // _WINDOWS_2
#ifdef _WINDOWS_2
			case VK_F1:
#else
            case SDLK_F1:
#endif
			{
				setF(false, 1);
				break;
			}
#ifdef _WINDOWS_2
			case VK_F2:
#else
            case SDLK_F2:
#endif
			{
				setF(false, 0);
				break;
			}
#ifdef _WINDOWS_2
			case VK_F3:
#else
            case SDLK_F3:
#endif
			{
				setF(false, 2);
				pressbutton = 0;
				std::cout << "press button:" << pressbutton << std::endl;
				//Logic_->SetRandom();
				Logic_->SetDrum();
				break;
			}
#ifdef _WINDOWS_2
			case VK_F4:
#else
            case SDLK_F4:
#endif
			{
				setF(false, 3);
				break;
			}
#ifdef _WINDOWS_2
			case VK_F5:
#else
            case SDLK_F5:
#endif
			{
				setF(false, 4);
				break;
			}
		}
	}
	return(true);
}

#ifdef _WINDOWS_2
    byte keyboard::GetPressedKey()
#else
    byte keyboard::GetPressedKey(SDL_Event event_)
#endif
{
#ifdef _WINDOWS_2
	return keyboard__->wparam_;
#else
    return event_.key.keysym.sym;
#endif // _WINDOWS_2
}

#ifdef _WINDOWS_2
    bool keyboard::IsExit()
#else
    bool keyboard::IsExit(SDL_Event event_)
#endif
{
#ifdef _WINDOWS_2
	return(keyboard__->msg_->message==WM_CLOSE);
#else
    return (event_.type == SDL_QUIT);
#endif
}
bool keyboard::getdone()
{
	return done;
}
void keyboard::setdone(bool state)
{
	done=state;
}
int keyboard::GetBet_()
{
	return bet;
}
void keyboard::SetBet_(int bet_)
{
	if(bet_>8)
		bet=0;
	else
		bet=bet_;
}
int keyboard::GetCountF()
{
	return CountButtons;
}
keyboard::~keyboard()
{
	delete F;
#ifdef _WINDOWS_2
	delete keyboard__;
#endif
}
