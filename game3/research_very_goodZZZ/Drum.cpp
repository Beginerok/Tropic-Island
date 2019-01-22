#include "Drum.h"
Drum::Drum()
{
    CountDrum=5;
    CountTextureOnDrum=6;
    line=21;
    bufsize=1024;
    vectressize=CountTextureOnDrum/2;
    Drum_=new int__*[CountDrum];
	for(int__ i=0;i<CountDrum;i++)
    	Drum_[i]=new int__[CountTextureOnDrum];
	Roll=new bool__[CountDrum];
	RotateDrum=new int__[CountDrum];
    Lim=new float__[CountDrum+2];
    Countin=new int__[CountDrum];
    t=new float__[CountDrum];
    VectorResult=new int__*[vectressize];
    for(int__ i=0;i<vectressize;i++)
        VectorResult[i]=new int__[CountDrum];
    lines=new bool__[line];
	win_=new float__[line];
    ms=new int*[line];
    for(int__ i=0;i<line;i++)
        ms[i]=new int__[CountDrum];
    buffer=new char__[bufsize];
    cells = new bool__[CountDrum-1];
}
float__ *Drum::GetRotateAll()
{
    return t;
}
int__ **Drum::GetDrumAll()
{
    return Drum_;
}
void__ Drum::SetBet_(int__ bet_)
{
    switch(bet_)
    {
        case 0:
        {
            bet=3;
            break;
        }
        case 1:
        {
            bet=5;
            break;
        }
        case 2:
        {
            bet=7;
            break;
        }
        case 3:
        {
            bet=9;
            break;
        }
        case 4:
        {
            bet=11;
            break;
        }
        case 5:
        {
            bet=13;
            break;
        }
        case 6:
        {
            bet=15;
            break;
        }
        case 7:
        {
            bet=17;
            break;
        }
        case 8:
        {
            bet=21;
            break;
        }
        default:
        {
            bet=3;
            break;
        }
    }
    SetTotalBet(coefbet*bet);
}
int__ Drum::GetBet()
{
    return bet;
}
float__ Drum::GetAcceleration()
{
    return ACCELERATION;
}
float__ Drum::GetSpeed()
{
    return SPEED;
}
float__ Drum::GetTimeStop()
{
    return TIME_STOP_FIRST_DRUM;
}
float__ Drum::GetTimeStopBetween()
{
    return TIME_STOP_BETWEEN_DRUMS;
}
void__ Drum::SetBuffer(char__ *str)
{
    for(int__ i=0;i<bufsize;i++)
        buffer[i]=str[i];
}
void__ Drum::ReInitilize()
{
    lines_.clear();
    int__ count_= 0;
    for(int__ i=0;i<CountDrum;i++)
    {
        for(int__ j=0;j<CountTextureOnDrum;j++)
        {
#if netsupport==1
            std::string str="";
            while(buffer[count_]!='|')
            {
                str+=buffer[count_];
                count_++;
            }
            count_++;
            Drum_[i][j]=atoi(str.c_str());
            str.clear();
#else
            int__ coin=0;
            if(rand()>rand())
                coin=1;
            Drum_[i][j]=((int__)((float__)rand()/RAND_MAX*(max_-((1-coin)*(max_-min_)/2)-(min_+coin*(max_-min_)/2))+(min_+coin*(max_-min_)/2)));
#endif
        }
    }

}
bool__ Drum::SetDrums()
{
    SPEED=10;
    TIME_STOP_FIRST_DRUM=0.23f;
    TIME_STOP_BETWEEN_DRUMS=0.23f;
    ACCELERATION=1;
    FULLSCREEN=0;
	RESOLUTION_W=1024;
	RESOLUTION_H=768;
    CREDITS=30000;
    WIN=0;
    coefbet=25;
    ildw=8;
    win5=5050;
    win4=4040;
    win3=1010;
    min_=4;
    max_=18;
    ildwenable=false;
    SetBet_(line);
	SetWin_(-1,-1);
    ms[0][0]=1;ms[0][1]=1;ms[0][2]=1;ms[0][3]=1;ms[0][4]=1;
    ms[1][0]=2;ms[1][1]=2;ms[1][2]=2;ms[1][3]=2;ms[1][4]=2;
    ms[2][0]=3;ms[2][1]=3;ms[2][2]=3;ms[2][3]=3;ms[2][4]=3;
    ms[3][0]=1;ms[3][1]=2;ms[3][2]=3;ms[3][3]=2;ms[3][4]=1;
    ms[4][0]=3;ms[4][1]=2;ms[4][2]=1;ms[4][3]=2;ms[4][4]=3;
    ms[5][0]=1;ms[5][1]=2;ms[5][2]=2;ms[5][3]=2;ms[5][4]=1;
    ms[6][0]=3;ms[6][1]=2;ms[6][2]=2;ms[6][3]=2;ms[6][4]=3;
    ms[7][0]=2;ms[7][1]=1;ms[7][2]=1;ms[7][3]=1;ms[7][4]=2;
    ms[8][0]=2;ms[8][1]=3;ms[8][2]=3;ms[8][3]=3;ms[8][4]=2;
    ms[9][0]=1;ms[9][1]=1;ms[9][2]=2;ms[9][3]=1;ms[9][4]=1;
    ms[10][0]=3;ms[10][1]=3;ms[10][2]=2;ms[10][3]=3;ms[10][4]=3;
    ms[11][0]=2;ms[11][1]=2;ms[11][2]=1;ms[11][3]=2;ms[11][4]=2;
    ms[12][0]=2;ms[12][1]=2;ms[12][2]=3;ms[12][3]=2;ms[12][4]=2;
    ms[13][0]=1;ms[13][1]=2;ms[13][2]=1;ms[13][3]=2;ms[13][4]=1;
    ms[14][0]=3;ms[14][1]=2;ms[14][2]=3;ms[14][3]=2;ms[14][4]=3;
    ms[15][0]=2;ms[15][1]=1;ms[15][2]=2;ms[15][3]=1;ms[15][4]=2;
    ms[16][0]=2;ms[16][1]=3;ms[16][2]=2;ms[16][3]=3;ms[16][4]=2;
    ms[17][0]=1;ms[17][1]=2;ms[17][2]=3;ms[17][3]=3;ms[17][4]=3;
    ms[18][0]=3;ms[18][1]=3;ms[18][2]=3;ms[18][3]=2;ms[18][4]=1;
    ms[19][0]=3;ms[19][1]=2;ms[19][2]=1;ms[19][3]=1;ms[19][4]=1;
    ms[20][0]=1;ms[20][1]=1;ms[20][2]=1;ms[20][3]=2;ms[20][4]=3;
    FileReader *filereader=new FileReader();
    filereader->FileReader__("config.conf","r");
    RESOLUTION_W=atoi(filereader->GetNumber().c_str());
    RESOLUTION_H=atoi(filereader->GetNumber().c_str());
    FULLSCREEN=atof(filereader->GetNumber().c_str());
    SPEED=atof(filereader->GetNumber().c_str());
    TIME_STOP_FIRST_DRUM=atof(filereader->GetNumber().c_str());
    TIME_STOP_BETWEEN_DRUMS=atof(filereader->GetNumber().c_str());
    CREDITS=atof(filereader->GetNumber().c_str());
    ACCELERATION=atof(filereader->GetNumber().c_str());
    min_=atof(filereader->GetNumber().c_str());
    max_=atof(filereader->GetNumber().c_str());
    win3=atof(filereader->GetNumber().c_str());
    win4=atof(filereader->GetNumber().c_str());
    win5=atof(filereader->GetNumber().c_str());
    coefbet=atof(filereader->GetNumber().c_str());
    ildw=atof(filereader->GetNumber().c_str());
    ildwenable=atof(filereader->GetNumber().c_str());
    //filereader->~FileReader();
	delete filereader;
    srand(time(0));
    for(int__ i=0;i<CountDrum;i++)
    {
        Set(0,i);
        SetRoll(false,i);
        SetRotate(0.0f,i);
        SetCountin(0,i);
        for(int__ j=0;j<CountTextureOnDrum;j++)
            Drum_[i][j]=((int__)((float__)rand()/RAND_MAX*(max_-min_)+min_));
    }
    for(int__ i=0;i<vectressize;i++)
        for(int__ j=0;j<CountDrum;j++)
            VectorResult[i][j]=Drum_[j][i+1];
	for(int__ i=0;i<line;i++)
		lines[i]=false;
    SetLim(0,0);
    SetLim(-62,1);
    SetLim(-118,2);
    SetLim(-183,3);
    SetLim(-241,4);
    SetLim(-300,5);
    SetLim(-360,6);
	return FULLSCREEN;
}
int__ Drum::GetDrum(int__ NumOfDrum,int__ NumOfTexture)
{
    return Drum_[NumOfDrum][NumOfTexture];
}
void__ Drum::SetLim(float__ lim,int__ n)
{
    Lim[n]=lim;
}
float__ Drum::GetLim(int__ n)
{
    return Lim[n];
}
void__ Drum::SetCountin(int__ countin,int__ n)
{
    Countin[n]=countin;
}
int__ Drum::GetCountin(int__ n)
{
    return Countin[n];
}
void__ Drum::SetRotate(float__ r,int__ n)
{
    t[n]=r;
}
float__ Drum::GetRotate(int__ n)
{
    return t[n];
}
void__ Drum::Set(int__ angle,int__ NumOfDrum)
{
    RotateDrum[NumOfDrum]=angle;
}
int__ Drum::Get(int__ NumOfDrum)
{
    return RotateDrum[NumOfDrum];
}
void__ Drum::SetRoll(bool__ roll,int__ n)
{
    Roll[n]=roll;
}
bool__ Drum::GetRoll(int__ n)
{
    return Roll[n];
}
bool__ Drum::GetAllRoll()
{
    bool__ b=false;
    for(int__ i=0;i<CountDrum;i++)
    {
        if(GetRoll(i))
        {
            b=true;
            break;
        }
    }
    return b;
}
void__ Drum::SetVectorResult(int__ result,int__ n,int__ m)
{
    VectorResult[n][m]=result;
}
int__ Drum::GetVectorResult(int__ NumOfPosition,int__ NumOfDrum)
{
    return VectorResult[NumOfPosition][NumOfDrum];
}
bool__ *Drum::GetLines()
{
    return lines;
}
const char__ *Drum::GetLines_()
{
    return lines_.c_str();
}
int__ **Drum::GetMS()
{
    return ms;
}
int__ Drum::GetMS(int__ n,int__ m)
{
    return ms[n][m]-1;
}
void__ Drum::SetCredits(float__ credits)
{
    CREDITS=credits+GetCredits();
}
float__ Drum::GetCredits()
{
    return CREDITS;
}
void__ Drum::SetWin_(int__ i,float__ win)
{
    if(i!=-1)
        win_[i]=win;
    else
        for(int__ j=0;j<line;j++)
            SetWin_(j,0.0);
}
float__ Drum::GetWin_(int__ i)
{
    if(i==21)
        return win_[i-1]+GetWin_(i-2);
	if(i>0)
		return win_[i]+GetWin_(i-1);
    else
        return win_[0];
}
void__ Drum::SetTotalBet(float__ totalbet)
{
    TOTAL_BET=totalbet;
}
float__ Drum::GetTotalBet()
{
    return TOTAL_BET;
}
void__ Drum::SetLines(int__ n,bool__ state)
{
    if(state)
    {
        switch(n)
        {
            case 0:
            {
                if(lines_.find('1')==-1)
                    lines_.insert(0,"1");
                break;
            }
            case 1:
            {
                if(lines_.find('1')==-1)
                    lines_.insert(0,"1");
                break;
            }
            case 2:
            {
                if(lines_.find('1')==-1)
                    lines_.insert(0,"1");
                break;
            }
            case 3:
            {
                if(lines_.find('2')==-1)
                    lines_.insert(0,"2");
                break;
            }
            case 4:
            {
                if(lines_.find('2')==-1)
                    lines_.insert(0,"2");
                break;
            }
            case 5:
            {
                if(lines_.find('3')==-1)
                    lines_.insert(0,"3");
                break;
            }
            case 6:
            {
                if(lines_.find('3')==-1)
                    lines_.insert(0,"3");
                break;
            }
            case 7:
            {
                if(lines_.find('4')==-1)
                    lines_.insert(0,"4");
                break;
            }
            case 8:
            {
                if(lines_.find('4')==-1)
                    lines_.insert(0,"4");
                break;
            }
            case 9:
            {
                if(lines_.find('5')==-1)
                    lines_.insert(0,"5");
                break;
            }
            case 10:
            {
                if(lines_.find('5')==-1)
                    lines_.insert(0,"5");
                break;
            }
            case 11:
            {
                if(lines_.find('6')==-1)
                    lines_.insert(0,"6");
                break;
            }
            case 12:
            {
                if(lines_.find('6')==-1)
                    lines_.insert(0,"6");
                break;
            }
            case 13:
            {
                if(lines_.find('7')==-1)
                    lines_.insert(0,"7");
                break;
            }
            case 14:
            {
                if(lines_.find('7')==-1)
                    lines_.insert(0,"7");
                break;
            }
            case 15:
            {
                if(lines_.find('8')==-1)
                    lines_.insert(0,"8");
                break;
            }
            case 16:
            {
                if(lines_.find('8')==-1)
                    lines_.insert(0,"8");
                break;
            }
            case 17:
            {
                if(lines_.find('9')==-1)
                    lines_.insert(0,"9");
                break;
            }
            case 18:
            {
                if(lines_.find('9')==-1)
                    lines_.insert(0,"9");
                break;
            }
            case 19:
            {
                if(lines_.find('9')==-1)
                    lines_.insert(0,"9");
                break;
            }
            case 20:
            {
                if(lines_.find('9')==-1)
                    lines_.insert(0,"9");
                break;
            }
        }
    }
    lines[n]=state;
}
bool__ Drum::GetLines(int__ n)
{
    return lines[n];
}
int__ Drum::GetCountDrum()
{
    return CountDrum;
}
int__ Drum::GetCountTextureOnDrum()
{
    return CountTextureOnDrum;
}
bool__ Drum::Lucky()
{
    bool__ ret=false;
    for(int__ i=0;i<GetBet();i++)
    {
        for(int__ j=0;j<GetCountDrum()-1;j++)
            cells[j]=false;
        if(GetVectorResult(GetMS(i,0),0)==GetVectorResult(GetMS(i,1),1))
            cells[0]=true;
        if(GetVectorResult(GetMS(i,1),1)==GetVectorResult(GetMS(i,2),2))
            cells[1]=true;
        if(GetVectorResult(GetMS(i,2),2)==GetVectorResult(GetMS(i,3),3))
            cells[2]=true;
        if(GetVectorResult(GetMS(i,3),3)==GetVectorResult(GetMS(i,4),4))
            cells[3]=true;
        if(ildwenable)
            Ildw(i);
        if(cells[0]&&cells[1]&&cells[2]&&cells[3])
        {
            SetLines(i,true);
            SetWin_(i,win5);
            ret=true;
            continue;
        }
        if(cells[1]&&cells[2]&&cells[3])
        {
            SetLines(i,true);
            SetWin_(i,win4);
            ret=true;
            continue;
        }
        if(cells[2]&&cells[3])
        {
            SetLines(i,true);
            SetWin_(i,win3);
            ret=true;
            continue;
        }
        if(cells[0]&&cells[1]&&cells[2])
        {
            SetLines(i,true);
            SetWin_(i,win4);
            ret=true;
            continue;
        }
        if(cells[0]&&cells[1])
        {
            SetLines(i,true);
            SetWin_(i,win3);
            ret=true;
            continue;
        }
        if(cells[1]&&cells[2])
        {
            SetLines(i,true);
            SetWin_(i,win3);
            ret=true;
            continue;
        }
    }
    return ret;
}
void__ Drum::Ildw(int__ num)
{
    if(GetVectorResult(GetMS(num,0),0)==ildw)
        cells[0]=true;
    if(GetVectorResult(GetMS(num,1),1)==ildw)
    {
        cells[1]=true;
        if(GetVectorResult(GetMS(num,2),2)==ildw||GetVectorResult(GetMS(num,0),0)==GetVectorResult(GetMS(num,2),2))
            cells[0]=true;
    }
    if(GetVectorResult(GetMS(num,2),2)==ildw)
    {
        if(GetVectorResult(GetMS(num,3),3)==ildw)
            cells[1]=true;
        if(GetVectorResult(GetMS(num,1),1)==GetVectorResult(GetMS(num,3),3))
        {
            cells[1]=true;
            cells[2]=true;
        }
        if(GetVectorResult(GetMS(num,0),0)==ildw)
            cells[1]=true;
    }
    if(GetVectorResult(GetMS(num,3),3)==ildw)
    {
        cells[2]=true;
        if(GetVectorResult(GetMS(num,2),2)==ildw||GetVectorResult(GetMS(num,2),2)==GetVectorResult(GetMS(num,4),4))
            cells[3]=true;
    }
    if(GetVectorResult(GetMS(num,4),4)==ildw)
        cells[3]=true;
}
POINT Drum::GetResolution()
{
	POINT p;
	p.x=RESOLUTION_W;
	p.y=RESOLUTION_H;
	return p;
}
void__ Drum::Take()
{
	SetCredits(GetWin_(GetBet()));
	SetWin_(-1,-1);
}
void__ Drum::Start()
{
	SetCredits(-GetTotalBet());
	for(int__ i=0;i<GetBet();i++)
		SetLines(i,false);
}
Drum::~Drum()
{
    for(int__ i=0;i<CountDrum;i++)
        delete[] Drum_[i];
    delete[] Drum_;
    delete[] Roll;
    delete[] RotateDrum;
    delete[] Lim;
    delete[] t;
    delete[] Countin;
    for(int__ i=0;i<vectressize;i++)
        delete[] VectorResult[i];
    delete[] VectorResult;
    delete[] lines;
    lines_.clear();
    delete[] win_;
    for(int__ i=0;i<line;i++)
        delete[] ms[i];
    delete[] ms;
    delete[] buffer;
    delete[] cells;
}
