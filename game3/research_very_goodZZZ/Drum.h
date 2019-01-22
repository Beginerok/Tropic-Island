#ifndef DRUM_H
#define DRUM_H
#include "FileReader.h"
#include <time.h>
#define netsupport 0
#define audiosupport 1
#define keyboardsupport 1
#ifndef _WINDOWS_
    #ifndef _POINT_
    #define _POINT_
    typedef struct POINT
    {
        float x;
        float y;
    };
    #endif
#endif
class Drum
{
public:
    Drum();
    int__ GetCountDrum();
    bool__ SetDrums();
    const char__ *GetLines_();
    bool__ *GetLines();
    int__ GetBet();
    float__ GetTotalBet();
    float__ GetWin_(int__ i);
    float__ GetCredits();
    void__ SetBet_(int__ bet_);
    int__ **GetMS();
    float__ *GetRotateAll();
    int__ GetCountTextureOnDrum();
    int__** GetDrumAll();
    float__ GetAcceleration();
    float__ GetSpeed();
    float__ GetTimeStop();
    float__ GetTimeStopBetween();
    void__ ReInitilize();
    void__ SetRoll(bool__ roll,int__ n);
    int__ GetCountin(int__ n);
    int__ GetDrum(int__ NumOfDrum,int__ NumOfTexture);
    void__ SetVectorResult(int__ result,int__ n,int__ m);
    bool__ GetAllRoll();
    void__ SetLines(int__ n,bool__ state);
    void__ SetCredits(float__ credits);
    void__ SetWin_(int__ i,float__ win);
    int__ Get(int__ NumOfDrum);
    void__ Set(int__ angle,int__ NumOfDrum);
    int__ GetMS(int__ n,int__ m);
    int__ GetVectorResult(int__ NumOfPosition,int__ NumOfDrum);
    bool__ GetRoll(int__ n);
    float__ GetRotate(int__ n);
    float__ GetLim(int__ n);
    void__ SetRotate(float__ r,int__ n);
    void__ SetCountin(int__ countin,int__ n);
    bool__ Lucky();
    void__ SetBuffer(char__ *str);
	POINT GetResolution();
	void__ Take();
	void__ Start();
    virtual ~Drum();
protected:
    bool__ GetLines(int__ n);
    void__ SetLim(float__ lim,int__ n);
    void__ SetTotalBet(float__ totalbet);
    void__ Ildw(int__ num);
    float__ FULLSCREEN,SPEED,TIME_STOP_FIRST_DRUM,TIME_STOP_BETWEEN_DRUMS,ACCELERATION,RESOLUTION_W,RESOLUTION_H;
    int__ CountDrum,CountTextureOnDrum,line,bufsize,vectressize;
    float__ CREDITS,WIN,*win_,TOTAL_BET,coefbet;
    float__ min_,max_;
    float__ *Lim;
    int__ *Countin;
    bool__ *Roll;
    float__ *t;
    int__ *RotateDrum;
    int__ **Drum_;
    int__ bet;
    int__ **VectorResult;
    bool__ *lines;
    std::string lines_;
    int__ lengthl;
    int__ **ms;
    char__ *buffer;
    bool__ *cells;
    int__ ildw;
    int__ win5;
    int__ win4;
    int__ win3;
    bool__ ildwenable;
};
#endif
