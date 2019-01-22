#include "Math.h"
Math::Math()
{
}
bool__ Math::Init()
{
    Drum_=new Drum();
    time_=new clock_t[Drum_->GetCountDrum()];
    acceleration=new float__[Drum_->GetCountDrum()];
    time_acc=new clock_t[Drum_->GetCountDrum()];
    time_mxspd=new float__[Drum_->GetCountDrum()];
    check=new bool__[Drum_->GetCountDrum()];
    uncheck=new bool__[Drum_->GetCountDrum()];
    stop=new bool__[Drum_->GetCountDrum()];
    min_acceleration=5;
#if netsupport==1
    int__ cli=1;
    Con_=new Con(cli);
    Con_->Init(0);
#endif
#if audiosupport==1
    Snd_=new Snd();
    Snd_->Init();
#endif
#if keyboardsupport==1
    keyboard_=new keyboard();
#endif
    return Drum_->SetDrums();
}
const char__*Math::GetLines_()
{
    return Drum_->GetLines_();
}
bool__*Math::GetLines()
{
    return Drum_->GetLines();
}
int__ Math::GetBet()
{
    return Drum_->GetBet();
}
int__ Math::GetTotalBet()
{
    return Drum_->GetTotalBet();
}
int__ Math::GetWin_()
{
    return Drum_->GetWin_(GetBet());
}
int__ Math::GetCredits()
{
    return Drum_->GetCredits();
}
void__ Math::SetBet()
{
#if keyboardsupport==1
	if(GetF(3))
		Drum_->SetBet_(keyboard_->GetBet_());
#endif
}
bool__ Math::GetF(int__ n)
{
#if audiosupport==1
	if(n!=2&&keyboard_->getF(n))
		Snd_->Play(2);
#endif
#if keyboardsupport==1
    return keyboard_->getF(n);
#endif
}

void__ Math::SetF(int__ n,bool__ state)
{
#if keyboardsupport==1
    return keyboard_->setF(state,n);
#endif
}
int__**Math::GetMS()
{
    return Drum_->GetMS();
}
#ifndef _WINDOWS_
    void__ Math::Update(bool__*isExecuted,bool__ bonus, Logic *Logic_,SDL_Event event_)
#else
    void__ Math::Update(bool__*isExecuted,bool__ bonus, Logic *Logic_)
#endif
{
#if keyboardsupport==1
    if(!Drum_->GetAllRoll())
#ifdef _WINDOWS_
		keyboard_->Update(bonus, Logic_);
#else
		keyboard_->Update(bonus,Logic_,event_);
#endif
#endif
    RotateIn();
    if(GetDone())
    {
*isExecuted=false;
        Destroy();
    }
}
bool__ Math::GetDone()
{
#if netsupport==1
    if(keyboard_->getdone())
        Con_->End(0);
#endif
#if keyboardsupport==1
    return keyboard_->getdone();
#endif
}
int__ Math::GetCountDrums()
{
    return Drum_->GetCountDrum();
}
float__*Math::GetRotate()
{
    return Drum_->GetRotateAll();
}
int__ Math::GetCountTextureOnDrums()
{
    return Drum_->GetCountTextureOnDrum();
}
int__**Math::GetDrums()
{
    return Drum_->GetDrumAll();
}
POINT Math::GetResolution()
{
	return Drum_->GetResolution();
}
void__ Math::StartAcceleration(int__ num)
{
#if audiosupport==1
    Snd_->StopAll();
    Snd_->Play(0);
#endif
    check[num]=false;
    acceleration[num]=Drum_->GetAcceleration();
    uncheck[num]=false;
    stop[num]=false;
}
void__ Math::SetAcceleration(int__ num)
{
    if(!check[num]&&acceleration[num]+Drum_->GetAcceleration()<Drum_->GetSpeed())
        acceleration[num]+=Drum_->GetAcceleration();
    else
    {
        if(!check[num])
        {
            time_mxspd[num]=Drum_->GetTimeStop()+num*(Drum_->GetTimeStopBetween())-2*(float__)(clock()-time_[num])/CLOCKS_PER_SEC;
            time_acc[num]=clock();
            Drum_->ReInitilize();
            check[num]=true;
        }
        else if(time_mxspd[num]<=(float__)(clock()-time_acc[num])/CLOCKS_PER_SEC)
            if(!uncheck[num]&&acceleration[num]-Drum_->GetAcceleration()>=0)
                acceleration[num]-=Drum_->GetAcceleration();
            else
            {
                if(!uncheck[num])
                    uncheck[num]=true;
                acceleration[num]=min_acceleration;
                if(stop[num])
                {
                    Drum_->SetRoll(false,num);
#if audiosupport==1
                    if(num>0)
                        Snd_->Stop(1,true);
                    Snd_->Play(1);
#endif
                    time_[num]=clock()-time_[num];
                    int__ dd=Drum_->GetCountin(num)%GetCountTextureOnDrums()+2;
                    dd%=GetCountTextureOnDrums();
                    int__ ddprev=dd-1,ddnext=dd+1;
                    if(!dd)
                        ddprev=GetCountTextureOnDrums()-1;
                    if(dd==GetCountTextureOnDrums()-1)
                        ddnext=0;
                    Drum_->SetVectorResult(Drum_->GetDrum(num,ddnext),0,num);
                    Drum_->SetVectorResult(Drum_->GetDrum(num,dd),1,num);
                    Drum_->SetVectorResult(Drum_->GetDrum(num,ddprev),2,num);
					//delete dd, ddprev, ddnext;
                    if(!Drum_->GetAllRoll())
                    {
                        if(Drum_->Lucky())
#if audiosupport==1
                        Snd_->Play(2);
#endif
                        ;
#if keyboardsupport==1
                        SetF(2,false);
#endif
                    }
                }
            }
    }
}
float__ Math::GetAcceleration(int__ num)
{
    return acceleration[num];
}
void__ Math::SetRotate()
{
	if(!Drum_->GetAllRoll()&&GetCredits()>=GetTotalBet()&&GetWin_()==0)
    {
#if netsupport==1
        Con_->SetBuf("Give Me Next Datagramm",0);
        Con_->Snd(0);
        Con_->ClearBuf(0);
        Con_->Recv(0);
        Drum_->SetBuffer(Con_->GetBuf(0));
        Con_->ClearBuf(0);
#endif
        Drum_->Start();
        for(int__ i=0;i<GetCountDrums();i++)
        {
            if(!i)
                fps = 0;
            time_[i]=clock();
            Drum_->Set(1+Drum_->Get(i),i);
            StartAcceleration(i);
            Drum_->SetRoll(true,i);
        }
    }
}
void__ Math::RotateIn()
{
	if(GetF(0))
		;
	if(GetF(1))
		Drum_->Take();
	SetBet();
#if keyboardsupport==1
    if(GetF(2))
#endif
        SetRotate();
	for(int__ i=0;i<Drum_->GetCountDrum();i++)
    {
        if(Drum_->GetRoll(i))
        {
            if(!i)
                fps++;
            if(Drum_->GetRotate(i)<=Drum_->GetLim(Drum_->Get(i)))
            {
                if(Drum_->Get(i)==GetCountTextureOnDrums())
                {
                    Drum_->Set(0,i);
                    Drum_->SetRotate(0.0f,i);
                }
                Drum_->SetCountin(Drum_->GetCountin(i)+1,i);
                if(!uncheck[i])
                    Drum_->Set(Drum_->Get(i)+1,i);
                else
                    stop[i]=true;
            }
            Drum_->SetRotate(Drum_->GetRotate(i)-GetAcceleration(i),i);
            SetAcceleration(i);
        }
    }
}
void__ Math::Destroy()
{
#if netsupport==1
    delete Con_;
#endif
#if audiosupport==1
    delete Snd_;
#endif
#if keyboardsupport==1
    delete keyboard_;
#endif
    delete Drum_;
    delete[] time_;
    delete[] acceleration;
    delete[] time_acc;
    delete[] time_mxspd;
    delete[] check;
    delete[] uncheck;
    delete[] stop;
	//delete fps;
	//delete min_acceleration;
}
Math::~Math()
{
}
