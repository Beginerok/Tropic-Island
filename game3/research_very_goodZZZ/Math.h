#ifndef MATH_H
#define MATH_H
#include "Drum.h"
#include <time.h>
#if netsupport==1
    #include "c.h"
#endif
#if audiosupport==1
    #include "Snd.h"
#endif
#if keyboardsupport==1
    #include "keyboard_.h"
    class keyboard;
#endif
#include "Logic.h"
class Math
{
public:
    Math();
    bool__ Init();
    void__ SetRotate();
    void__ RotateIn();
    void__ StartAcceleration(int__ num);
    void__ SetAcceleration(int__ num);
    float__ GetAcceleration(int__ num);
    int__ GetCredits();
    int__ GetWin_();
    int__ GetTotalBet();
    int__ GetBet();
    const char__*GetLines_();
    bool__*GetLines();
    void__ SetBet();
    int__**GetMS();
    bool__ GetF(int__ n);
    void__ SetDrums();
#ifndef _WINDOWS_
    void__ Update(bool__*isExecuted,bool__ bonus, Logic *Logic_,SDL_Event event_);
#else
    void__ Update(bool__*isExecuted,bool__ bonus, Logic *Logic_);
#endif
    bool__ GetDone();
    int__ GetCountDrums();
    float__*GetRotate();
    int__ GetCountTextureOnDrums();
    int__**GetDrums();
    void__ Destroy();
    void__ SetF(int__ num,bool__ state);
	POINT GetResolution();
#if keyboardsupport==1
    keyboard*keyboard_;
#endif
    virtual ~Math();
protected:
    Drum*Drum_;
#if netsupport==1
    Con*Con_;
#endif
#if audiosupport==1
    Snd*Snd_;
#endif
    clock_t*time_;
    float__*acceleration;
    clock_t*time_acc;
    float__*time_mxspd;
    bool__*check;
    bool__*uncheck;
    bool__*stop;
    int__ fps;
    int__ min_acceleration;
};
#endif
