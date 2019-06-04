#ifndef keyboard_H
#define keyboard_H
#ifdef __unix__
    //#include "keyboard.h"
	#include <SDL2/SDL.h>
#else
	#include <Windows.h>
    #include <SDL2/SDL.h>
#endif
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
#endif
class keyboard
{
public:
    keyboard();
    int getAny();
#ifdef _WINDOWS_2
    void Update(bool__ bonus, Logic *Logic_);
    bool IsMouseButtonDown(byte key, bool__ bonus);
    bool IsMouseButtonUp(byte key, bool__ bonus, Logic *Logic_);
    bool IsKeyDown(byte key, bool__ bonus);
    bool IsKeyUp(byte key, bool__ bonus, Logic *Logic_);
    POINT GetButtonDownCoords();
    bool IsExit();
    byte GetPressedKey();
#else
    void Update(bool bonus, Logic *Logic_, SDL_Event event_);
    bool IsMouseButtonDown(byte key, bool bonus, SDL_Event event_);
    bool IsMouseButtonUp(byte key, bool bonus, Logic *Logic_, SDL_Event event_);
    bool IsKeyDown(byte key, bool bonus, SDL_Event event_);
    bool IsKeyUp(byte key, bool bonus, Logic *Logic_, SDL_Event event_);
    POINT GetButtonDownCoords(SDL_Event event_);
    bool IsExit(SDL_Event event_);
    byte GetPressedKey(SDL_Event event_);
#endif
    bool getdone();
    void setdone(bool state);
    bool getF(int n);
    void setF(bool status,int n);
    int GetBet_();
    void SetBet_(int bet_);
    int GetCountF();
#ifdef _WINDOWS_2
	Keyboard *keyboard__;
#endif
	bool*GetF();
	bool GetAny();
    virtual ~keyboard();
protected:
    bool done;
    bool *F;
    int CountButtons;
    int bet;
    POINT point;
};
#endif
