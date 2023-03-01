#ifndef keyboard_H
#define keyboard_H
#ifndef __unix__
	#include <Windows.h>
#endif
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "Logic.h"
#ifdef __unix__
    typedef unsigned char byte ;
    #ifndef _POINT_
    #define _POINT_
    typedef struct POINT
    {
        float x;
        float y;
    };
    #endif
#else
#pragma comment(lib,"SDL2.lib")
#endif
class WindowsSDLApi
{
public:
	WindowsSDLApi();
    int getAny();
    void Update(bool bonus, Logic *Logic_, SDL_Event event_);
    bool IsMouseButtonDown(byte key, bool bonus, SDL_Event event_);
    bool IsMouseButtonUp(byte key, bool bonus, Logic *Logic_, SDL_Event event_);
    bool IsKeyDown(byte key, bool bonus, SDL_Event event_);
    bool IsKeyUp(byte key, bool bonus, Logic *Logic_, SDL_Event event_);
    POINT GetButtonDownCoords(SDL_Event event_);
    bool IsExit(SDL_Event event_);
    byte GetPressedKey(SDL_Event event_);

    bool getdone();
    void setdone(bool state);
    bool getF(int n);
    void setF(bool status,int n);
    int GetBet_();
    void SetBet_(int bet_);
    int GetCountF();

	bool*GetF();
	bool GetAny();

	int pressbutton,upbutton;
    virtual ~WindowsSDLApi();
protected:
    bool done;
    bool *F;
    int CountButtons;
    int bet;
    POINT point;
public:
    int width, height;
};
#endif
