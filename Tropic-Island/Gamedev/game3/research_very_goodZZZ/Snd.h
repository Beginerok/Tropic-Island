#ifndef SND_H
#define SND_H
#include <AL/al.h>
#include <AL/alc.h>
#include "FileReader.h"
struct lhead
{
    uint__ i1;
    ushort__ ul1;
    ushort__ us5;
    uint__ ul2;
};
class Snd
{
public:
    Snd();
    int__ Init();
    int__ Play(int__ src);
    int__ Stop(int__ src,bool__ force);
    int__ StopAll();
    void__ SetPlay(int__ num);
    virtual ~Snd();
private:
protected:
    ALCdevice*dev;
    ALCcontext*ctx;
    uint__*buffer,*source;
    int__ state;
    int__ song_;
    uchar__*buf;
    uint__ size_,freq;
    int__ format;
    lhead*lhead_;
};
#endif
