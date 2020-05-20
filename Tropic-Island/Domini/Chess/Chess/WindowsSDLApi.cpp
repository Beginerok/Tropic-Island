#include "WindowsSDLApi.h"
#include <iostream>
WindowsSDLApi::WindowsSDLApi()
{
	done = false;
	pressbutton = 0;
}
void WindowsSDLApi::Update(SDL_Event event_)
{
	IsMouseButtonDown(GetPressedKey(event_),event_);
	IsMouseButtonUp(GetPressedKey(event_),event_);
	IsKeyDown(GetPressedKey(event_),event_);
	IsKeyUp(GetPressedKey(event_),event_);
}
bool WindowsSDLApi::IsMouseButtonDown(byte key,SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_MOUSEBUTTONDOWN)
	{
		GetButtonDownCoords(event_);
		if(point.y >478 && point.y<496)
		{
		}
		return true;
	}
    if(event_.type == SDL_MOUSEBUTTONDOWN)
	{
		GetButtonDownCoords(event_);
		return true;
	}
	return false;
}
bool WindowsSDLApi::IsMouseButtonUp(byte key, SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_MOUSEBUTTONUP)
	{
		GetButtonDownCoords(event_);
		if (point.y >478 && point.y<496)
		{
			
		}
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
bool WindowsSDLApi::IsKeyDown(byte key, SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_KEYDOWN && event_.key.repeat == 0)
	{
        switch(event_.key.keysym.sym)
        {
            case SDLK_F1:
            {
                break;
            }
            case SDLK_F2:
            {
                break;
            }
            case SDLK_F3:
            {
				pressbutton += 1;
				std::cout << "press button:" << pressbutton << std::endl;
                break;
            }
            case SDLK_F4:
            {
                break;
            }
            case SDLK_F5:
            {
                break;
            }
		}
	}
	return(true);
}
bool WindowsSDLApi::IsKeyUp(byte key, SDL_Event event_)
{
    SDL_PollEvent(&event_);
    if(event_.type == SDL_KEYUP)
	{
        switch(event_.key.keysym.sym)
        {
            case SDLK_F1:
            {
                break;
            }
            case SDLK_F2:
            {
                break;
            }
            case SDLK_F3:
            {
				pressbutton = 0;
				std::cout << "press button:" << pressbutton << std::endl;
                break;
            }
            case SDLK_F4:
            {
                break;
            }
            case SDLK_F5:
            {
                setdone(true);
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
WindowsSDLApi::~WindowsSDLApi()
{
}