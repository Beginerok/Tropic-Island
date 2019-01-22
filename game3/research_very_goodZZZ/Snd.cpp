#include "Snd.h"
#ifdef _WINDOWS_
    #pragma comment(lib,"OpenAL32.lib")
#endif
Snd::Snd()
{
    song_=3;
    buffer=new uint__[song_];
    source=new uint__[song_];
    lhead_=new lhead[song_];
    buf=new uchar__[190884];
}
int__ Snd::Init()
{
    dev=alcOpenDevice(0);
    ctx=alcCreateContext(dev,0);
    alcMakeContextCurrent(ctx);
    alGenBuffers(song_,buffer);
    alGenSources(song_,source);
    int__ j=0;
    lhead_[0].i1=190884;
    lhead_[0].ul1=1;
    lhead_[0].us5=16;
    lhead_[0].ul2=22050;
    lhead_[1].i1=47532;
    lhead_[1].ul1=1;
    lhead_[1].us5=16;
    lhead_[1].ul2=22050;
    lhead_[2].i1=46376;
    lhead_[2].ul1=1;
    lhead_[2].us5=16;
    lhead_[2].ul2=22050;
    FileReader*filereader=new FileReader();
    filereader->FileReader__("resource.dat","r");
    for(int__ i=0;i<song_;i++)
    {
        if(lhead_[j].ul1==1)
        {
            if(lhead_[j].us5==16)
                format=AL_FORMAT_MONO16;
            else
                format=AL_FORMAT_MONO8;
        }
        else
        {
            if(lhead_[j].us5==16)
                format=AL_FORMAT_STEREO16;
            else
                format=AL_FORMAT_STEREO8;
        }
        freq=lhead_[j].ul2;
        size_=lhead_[j].i1;
        filereader->ReadFile(size_,buf);
        alBufferData(buffer[j],format,buf,size_,freq);
        alSourcei(source[j],AL_BUFFER,buffer[j]);
        j++;
    }
    filereader->~FileReader();
    return 0;
}
int__ Snd::Play(int__ src)
{
    alGetSourcei(source[src],AL_SOURCE_STATE,&state);
    if(state==AL_PLAYING)
        return 0;
    alSourcePlay(source[src]);
    return 0;
}
int__ Snd::Stop(int__ src,bool__ force)
{
    alGetSourcei(source[src],AL_SOURCE_STATE,&state);
    if(state==AL_PLAYING || force)
        alSourceStop(source[src]);
    return 0;
}
int__ Snd::StopAll()
{
    for(int__ i=0;i<song_;i++)
        Stop(i,false);
    return 0;
}
Snd::~Snd()
{
    alDeleteSources(song_,source);
    alDeleteBuffers(song_,buffer);
    delete source;
    delete buffer;
    delete lhead_;
    delete buf;
    alcMakeContextCurrent(0);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
}
