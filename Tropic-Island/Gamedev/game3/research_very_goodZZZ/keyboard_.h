#ifndef keyboard_H
#define keyboard_H
#include "typedefs.h"
#ifdef _WINDOWS_2
    #include "keyboard.h"
#else
    #include<SDL2/SDL.h>
#endif
#include "Logic.h"
#ifndef _WINDOWS_2
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
    int__ getAny();
#ifdef _WINDOWS_2
    void__ Update(bool__ bonus, Logic *Logic_);
    bool__ IsMouseButtonDown(byte key, bool__ bonus);
    bool__ IsMouseButtonUp(byte key, bool__ bonus, Logic *Logic_);
    bool__ IsKeyDown(byte key, bool__ bonus);
    bool__ IsKeyUp(byte key, bool__ bonus, Logic *Logic_);
    POINT GetButtonDownCoords();
    bool__ IsExit();
    byte GetPressedKey();
#else
    void__ Update(bool__ bonus, Logic *Logic_, SDL_Event event_);
    bool__ IsMouseButtonDown(byte key, bool__ bonus, SDL_Event event_);
    bool__ IsMouseButtonUp(byte key, bool__ bonus, Logic *Logic_, SDL_Event event_);
    bool__ IsKeyDown(byte key, bool__ bonus, SDL_Event event_);
    bool__ IsKeyUp(byte key, bool__ bonus, Logic *Logic_, SDL_Event event_);
    POINT GetButtonDownCoords(SDL_Event event_);
    bool__ IsExit(SDL_Event event_);
    byte GetPressedKey(SDL_Event event_);
#endif
    bool__ getdone();
    void__ setdone(bool__ state);
    bool__ getF(int__ n);
    void__ setF(bool__ status,int__ n);
    int__ GetBet_();
    void__ SetBet_(int__ bet_);
    int__ GetCountF();
#ifdef _WINDOWS_2
	Keyboard *keyboard__;
#endif
	bool__*GetF();
	bool__ GetAny();
    virtual ~keyboard();
protected:
    bool__ done;
    bool__ *F;
    int__ countF;
    int__ bet;
    POINT point;
};
#endif
