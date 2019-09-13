#include "keyboard_.h"
keyboard::keyboard()
{
	countF=5;
	F=new bool__[countF];
	for(int__ i=0;i<countF;i++)
		setF(false,i);
	done = false;
	SetBet_(8);

#ifdef _WINDOWS_2
	keyboard__=new Keyboard();
#endif
}
int__ keyboard::getAny()
{
	int__ retval=5;
	for(int__ i=0;i<countF;i++)
		if(getF(i))
			retval=i;
	return retval;
}
bool__ keyboard::GetAny()
{
	bool__ retval = false;
	for (int__ i = 0; i<countF; i++)
		if (getF(i))
			retval = true;
	return retval;
}
bool__ keyboard::getF(int__ n)
{
	return F[n];
}
void__ keyboard::setF(bool__ status,int__ n)
{
	F[n] = status;
}
bool__*keyboard::GetF()
{
	return F;
}
#ifndef _WINDOWS_2
    void__ keyboard::Update(bool__ bonus, Logic *Logic_,SDL_Event event_)
#else
    void__ keyboard::Update(bool__ bonus, Logic *Logic_)
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
    bool__ keyboard::IsMouseButtonDown(byte key,bool__ bonus)
#else
    bool__ keyboard::IsMouseButtonDown(byte key,bool__ bonus,SDL_Event event_)
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
		if(point.y >607 && point.y<683)
		{
			if(point.x >245 && point.x<345)
				setF(true, 0);
			if(point.x >352 && point.x<455)
				setF(true, 1);
			if(point.x >461 && point.x<561)
				setF(true, 2);
			if(point.x >569 && point.x<668)
				setF(true, 3);
			if(point.x >677 && point.x<777)
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
			if (point.y >437 && point.y<570)
			{
				if (point.x >65 && point.x<190)
					setF(true, 1);
				if (point.x >261 && point.x<381)
					setF(true, 0);
				if (point.x >436 && point.x<582)
					setF(true, 2);
				if (point.x >632 && point.x<774)
					setF(true, 3);
				if (point.x >820 && point.x<961)
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
    bool__ keyboard::IsMouseButtonUp(byte key, bool__ bonus, Logic *Logic_,SDL_Event event_)
#else
    bool__ keyboard::IsMouseButtonUp(byte key, bool__ bonus, Logic *Logic_)
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
		if(point.y >607 && point.y<683)
		{
			if(point.x >245 && point.x<345)
				setF(false, 0);
			if(point.x >352 && point.x<455)
				setF(false, 1);
			if(point.x >461 && point.x<561)
				setF(false, 2);
			if(point.x >569 && point.x<668)
			{
				if(getF(3))
					SetBet_(GetBet_() + 1);
				setF(false, 3);
			}
			if(point.x >677 && point.x<777)
			{
				setF(false, 4);
				setdone(true);
			}
		}
		return true;
	}
	else

#ifdef _WINDOWS_2
		if (keyboard__->msg_->message == WM_RBUTTONUP || keyboard__->msg_->message == WM_LBUTTONUP && bonus && GetAny())
#else
    if(event_.type == SDL_MOUSEBUTTONUP && bonus&&!GetAny())
#endif
		{
#ifdef _WINDOWS_2			
			GetButtonDownCoords();
#else
			GetButtonDownCoords(event_);
#endif
			if (point.y > 437 && point.y < 570)
			{
					if (point.x > 65 && point.x < 190)
						setF(false, 1);
					if (point.x > 261 && point.x < 381)
					{
						setF(false, 0);
						Logic_->SetRandom();
					}
					if (point.x > 436 && point.x < 582)
					{
						setF(false, 2);
						Logic_->SetRandom();
					}
					if (point.x > 632 && point.x < 774)
					{
						setF(false, 3);
						Logic_->SetRandom();
					}

					if (point.x > 820 && point.x < 961)
					{
						setF(false, 4);
						Logic_->SetRandom();
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
#endif
	return point;
}
#ifdef _WINDOWS_2
    bool__ keyboard::IsKeyDown(byte key, bool__ bonus)
#else
    bool__ keyboard::IsKeyDown(byte key, bool__ bonus,SDL_Event event_)
#endif // _WINDOWS_2
{
#ifndef _WINDOWS_2
    SDL_PollEvent(&event_);
#endif
#ifdef _WINDOWS_2
	if (keyboard__->msg_->message == WM_KEYDOWN && !bonus)
#else
    if(event_.type == SDL_KEYDOWN && !bonus)
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
        if(event_.type == SDL_KEYDOWN && bonus && !GetAny())
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
    bool__ keyboard::IsKeyUp(byte key, bool__ bonus,Logic *Logic_, SDL_Event event_)
#else
    bool__ keyboard::IsKeyUp(byte key, bool__ bonus,Logic *Logic_)
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
				Logic_->SetRandom();
				break;
			}
#ifdef _WINDOWS_2
			case VK_F3:
#else
            case SDLK_F3:
#endif
			{
				setF(false, 2);
				Logic_->SetRandom();
				break;
			}
#ifdef _WINDOWS_2
			case VK_F4:
#else
            case SDLK_F4:
#endif
			{
				setF(false, 3);
				Logic_->SetRandom();
				break;
			}
#ifdef _WINDOWS_2
			case VK_F5:
#else
            case SDLK_F5:
#endif
			{
				setF(false, 4);
				Logic_->SetRandom();
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
    bool__ keyboard::IsExit()
#else
    bool__ keyboard::IsExit(SDL_Event event_)
#endif
{
#ifdef _WINDOWS_2
	return(keyboard__->msg_->message==WM_CLOSE);
#else
    return (event_.type == SDL_QUIT);
#endif
}
bool__ keyboard::getdone()
{
	return done;
}
void__ keyboard::setdone(bool__ state)
{
	done=state;
}
int__ keyboard::GetBet_()
{
	return bet;
}
void__ keyboard::SetBet_(int__ bet_)
{
	if(bet_>8)
		bet=0;
	else
		bet=bet_;
}
int__ keyboard::GetCountF()
{
	return countF;
}
keyboard::~keyboard()
{
	delete F;
#ifdef _WINDOWS_2
	delete keyboard__;
#endif
}
