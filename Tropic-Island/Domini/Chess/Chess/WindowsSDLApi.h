#ifndef keyboard_H
#define keyboard_H
#ifndef __unix__
	#include <Windows.h>
#endif
#define SDL_MAIN_HANDLED
#include <gl\GLU.h>
#include "SDL2/SDL.h"
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
#endif
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"SDL2.lib")
class WindowsSDLApi
{
public:
	WindowsSDLApi();
    void Update(SDL_Event event_);
    bool IsMouseButtonDown(byte key, SDL_Event event_);
    bool IsMouseButtonUp(byte key, SDL_Event event_);
    bool IsKeyDown(byte key,SDL_Event event_);
    bool IsKeyUp(byte key, SDL_Event event_);
    POINT GetButtonDownCoords(SDL_Event event_);
    bool IsExit(SDL_Event event_);
    byte GetPressedKey(SDL_Event event_);

    bool getdone();
    void setdone(bool state);
	int pressbutton;
    POINT point;
    virtual ~WindowsSDLApi();
protected:
    bool done;
};
#endif
