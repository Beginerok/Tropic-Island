#include "WindowsSDLApi.h"
#include <iostream>
WindowsSDLApi::WindowsSDLApi()
{
	CountButtons=10;
	F=new bool[CountButtons];
	for(int i=0;i<CountButtons;i++)
		setF(false,i);
	done = false;
	SetBet_(8);

	pressbutton = 0;
    upbutton = 1;
	width = 1920;
	height = 1080;
}
int WindowsSDLApi::getAny()
{
	int retval=10;
	for(int i=0;i<CountButtons;i++)
		if(getF(i))
			retval=i;
	return retval;
}
bool WindowsSDLApi::GetAny()
{
	bool retval = false;
	for (int i = 0; i<CountButtons; i++)
		if (getF(i))
			retval = true;
	return retval;
}
bool WindowsSDLApi::getF(int n)
{
	return F[n];
}
void WindowsSDLApi::setF(bool status,int n)
{
	F[n] = status;
}
bool*WindowsSDLApi::GetF()
{
	return F;
}
void WindowsSDLApi::Update(bool bonus, Logic *Logic_,SDL_Event event_)
{
	IsMouseButtonDown(GetPressedKey(event_),bonus,event_);
	IsMouseButtonUp(GetPressedKey(event_), bonus, Logic_,event_);
	IsKeyDown(GetPressedKey(event_), bonus,event_);
	IsKeyUp(GetPressedKey(event_), bonus,Logic_,event_);
}
bool WindowsSDLApi::IsMouseButtonDown(byte key,bool bonus,SDL_Event event_)
{
    SDL_PollEvent(&event_);
	switch (event_.type) 
	{

	case SDL_WINDOWEVENT:
		if (event_.window.event == /*SDL_WINDOWEVENT_RESIZED | */ SDL_WINDOWEVENT_SIZE_CHANGED) {
			std::cout << "MESSAGE:Resizing window" << std::endl;
			width = event_.window.data1;
			height = event_.window.data2;

			glViewport(0, 0, width, height);
		}
		break;
	}
	if (event_.type == SDL_QUIT) {
		done = true;
	}
    if(event_.type == SDL_MOUSEBUTTONDOWN && !bonus)
	{
		GetButtonDownCoords(event_);
		/*
		if(point.y >478 && point.y<496)
		{
			if(point.x >123 && point.x<190)
				setF(true, 0);
			if(point.x >228 && point.x<296)
				setF(true, 1);
			if (point.x > 330 && point.x < 401)
			{
                upbutton+=1;
				setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
			}
			if (point.x > 436 && point.x < 506)
				setF(true, 3);
			if(point.x >543 && point.x<608)
				setF(true, 4);
		}
		*/
		if (point.y >1040  && point.y < 1063)
		{
			if (point.x > 351 && point.x < 508)
				setF(true, 0);
			if (point.x > 630 && point.x < 800)
				setF(true, 1);
			if (point.x > 923 && point.x < 1091)
			{
				upbutton += 1;
				setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
			}
			if (point.x > 1215 && point.x < 1377)
				setF(true, 3);
			if (point.x > 1500 && point.x < 1663)
				setF(true, 4);
		}
		event_.type = 0;
		return true;
	}
	else
    if(event_.type == SDL_MOUSEBUTTONDOWN && bonus/* && !GetAny() */ )
		{
			GetButtonDownCoords(event_);
			std::cout << point.x << " " << point.y<<std::endl;
			/*
			if (point.y >253 && point.y<448)
			{
				if (point.x >37 && point.x<137)
					setF(true, 5);
				if (point.x >166 && point.x<270)
					setF(true, 6);
				if (point.x > 296 && point.x < 401)
				{
                    upbutton+=1;
					setF(true, 7);
					pressbutton += 1;
					std::cout << "press button:" << pressbutton << std::endl;
				}
				if (point.x > 430 && point.x < 532)
					setF(true, 8);
				if (point.x >560 && point.x<663)
					setF(true, 9);
			}
			*/
				if (point.y > 542 && point.y < 970)
				{
					if (point.x > 95 && point.x < 383)
						setF(true, 5);
					if (point.x > 453 && point.x < 742)
						setF(true, 6);
					if (point.x > 813 && point.x < 1103)
					{
						upbutton += 1;
						setF(true, 7);
						pressbutton += 1;
						std::cout << "press button:" << pressbutton << std::endl;
					}
					if (point.x > 1172 && point.x < 1465)
						setF(true, 8);
					if (point.x > 1534 && point.x < 1823)
						setF(true, 9);
				}
			event_.type = 0;
			return true;
		}

    if(event_.type == SDL_MOUSEBUTTONDOWN)
	{
		GetButtonDownCoords(event_);
		return true;
	}
	return false;
}
bool WindowsSDLApi::IsMouseButtonUp(byte key, bool bonus, Logic *Logic_,SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_MOUSEBUTTONUP && !bonus)
	{
		GetButtonDownCoords(event_);
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
			    upbutton=0;
                pressbutton = 1;
				std::cout << "press button:" << pressbutton << std::endl;
				Logic_->SetDrum();
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
		event_.type = 0;
		return true;
	}
	else
    if(event_.type == SDL_MOUSEBUTTONUP && bonus&&/*!GetAny()  &&*/ event_.key.repeat == 0)
		{
			GetButtonDownCoords(event_);
			//if (point.y >478 && point.y<496)
			{
				//if (point.x >123 && point.x<190)
				if (getF(5))
					setF(false, 5);
				//if (point.x >228 && point.x<296)
				if (getF(6))
					setF(false, 6);
				//if (point.x >330 && point.x<401)
				if (getF(7))
				{

					setF(false, 7);
                  //  upbutton=0;
					//pressbutton = 1;
					//std::cout << "press button:" << pressbutton << std::endl;
				}
				//if (point.x >436 && point.x<506)
				{
					if (getF(8))
					{
						//SetBet_(GetBet_() + 1);
						setF(false, 8);
					}
				}
				//if (point.x >543 && point.x<608)
				{
					if (getF(9))
					{
						setF(false, 9);
						//setdone(true);
					}
				}
			}
		event_.type = 0;
			return true;
		}
    if(event_.type == SDL_MOUSEBUTTONDOWN)
    {
		return true;
	}
	return false;
}
POINT WindowsSDLApi::GetButtonDownCoords(SDL_Event event_)
{
	point.x=event_.button.x;
	point.y=event_.button.y;
	//std::cout << "Coordinats x:" << event_.button.x << "y:"<< event_.button.y << std::endl;
	return point;
}
bool WindowsSDLApi::IsKeyDown(byte key, bool bonus,SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_KEYDOWN && !bonus && event_.key.repeat == 0)
	{
        switch(event_.key.keysym.sym)
        {
            case SDLK_F1:
            {
                setF(true, 0);
                //setF(true, 5);
                break;
            }
            case SDLK_F2:
            {
                setF(true, 1);
                //setF(true, 6);
                break;
            }
            case SDLK_F3:
            {
                setF(true, 2);
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
                //setF(true, 7);
                break;
            }
            case SDLK_F4:
            {
                //SetBet_(GetBet_()+1);
                setF(true, 3);
                //setF(true, 8);
                break;
            }
            case SDLK_F5:
            {
                setF(true, 4);
                //setF(true, 9);
                break;
            }
		}
	}
	else
        if(event_.type == SDL_KEYDOWN && bonus && !GetAny() && event_.key.repeat == 0)
		{
            switch(event_.key.keysym.sym)
            {
                case SDLK_F1:
                {
                    setF(true, 6);
                    break;
                }
                case SDLK_F2:
                {
                    setF(true, 5);
                    break;
                }
                case SDLK_F3:
                {
                    setF(true, 7);
					pressbutton += 1;
					std::cout << "press button:" << pressbutton << std::endl;
                    break;
                }
                case SDLK_F4:
                {
                    setF(true, 8);
                    break;
                }
                case SDLK_F5:
                {
                    setF(true, 9);
                    break;
                }
			}
		}
	return(true);
}
bool WindowsSDLApi::IsKeyUp(byte key, bool bonus,Logic *Logic_, SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_KEYUP && !bonus)
	{
        switch(event_.key.keysym.sym)
        {
            case SDLK_F1:
            {
                setF(false, 0);
                //setF(true, 0);
                break;
            }
            case SDLK_F2:
            {
                setF(false, 1);
                //setF(true, 1);
                break;
            }
            case SDLK_F3:
            {
                setF(false, 2);
				pressbutton = 0;
				upbutton = 1;
				std::cout << "press button:" << pressbutton << std::endl;
                //setF(true, 2);
                Logic_->SetDrum();
                break;
            }
            case SDLK_F4:
            {
                if (getF(3))
                    SetBet_(GetBet_() + 1);
                setF(false, 3);
                //setF(true, 3);
                break;
            }
            case SDLK_F5:
            {
                setF(false, 4);
                //setF(true, 4);
                setdone(true);
                break;
            }
		}
	}else
    if(event_.type == SDL_KEYUP && bonus && GetAny())
	{
        switch(event_.key.keysym.sym)
        {
            case SDLK_F1:
			{
				setF(false, 6);
				break;
			}
            case SDLK_F2:
			{
				setF(false, 5);
				break;
			}
            case SDLK_F3:
			{
				setF(false, 7);
				pressbutton = 0;
				upbutton = 1;
				std::cout << "press button:" << pressbutton << std::endl;
				//Logic_->SetRandom();

				break;
			}
            case SDLK_F4:
			{
				setF(false, 8);
				break;
			}
            case SDLK_F5:
			{
				setF(false, 9);
				break;
			}
		}
	}
	return(true);
}
byte WindowsSDLApi::GetPressedKey(SDL_Event event_)
{
    return event_.key.keysym.sym;
}
bool WindowsSDLApi::IsExit(SDL_Event event_)
{
    return (event_.type == SDL_QUIT);
}
bool WindowsSDLApi::getdone()
{
	return done;
}
void WindowsSDLApi::setdone(bool state)
{
	done=state;
}
int WindowsSDLApi::GetBet_()
{
	return bet;
}
void WindowsSDLApi::SetBet_(int bet_)
{
	if(bet_>8)
		bet=0;
	else
		bet=bet_;
}
int WindowsSDLApi::GetCountF()
{
	return CountButtons;
}
WindowsSDLApi::~WindowsSDLApi()
{
	delete F;
}
