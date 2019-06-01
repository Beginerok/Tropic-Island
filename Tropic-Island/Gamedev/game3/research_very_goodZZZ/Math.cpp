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
    //int__ cli=1;
    //Con_=new Con(cli);
    //Con_->Init(0);
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
#ifndef _WINDOWS_2
    void__ Math::Update(bool__*isExecuted,bool__ bonus, Logic *Logic_,SDL_Event event_)
#else
    void__ Math::Update(bool__*isExecuted,bool__ bonus, Logic *Logic_)
#endif
{
#if keyboardsupport==1
    if(!Drum_->GetAllRoll())
#ifdef _WINDOWS_2
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
	if (keyboard_->getdone())
		//Con_->End(0);
		;

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
size_t write_data(char *ptr, size_t size, size_t nmemb, FILE* data)
{
	return fwrite(ptr, size, nmemb, data);
}
void__ Math::SetRotate()
{
	if(!Drum_->GetAllRoll()&&GetCredits()>=GetTotalBet()&&GetWin_()==0)
    {
#if netsupport==1
        /*
		Con_->SetBuf("Give Me Next Datagramm",0);
        Con_->Snd(0);
		Con_->ClearBuf(0);
        Con_->Recv(0);
        Drum_->SetBuffer(Con_->GetBuf(0));
        Con_->ClearBuf(0);
		*/
		const std::string header_filename = "head.txt";
		const std::string body_filename = "body.html";
#ifdef _WINDOWS_2
		FILE *header_file;
		fopen_s(&header_file, header_filename.c_str(), "w");
#else
		FILE *header_file = fopen(header_filename.c_str(), "w");
#endif
		//if (header_file == NULL)
		//	return -1;
#ifdef _WINDOWS_2
		FILE *body_file;
		fopen_s(&body_file, body_filename.c_str(), "w");
#else
		FILE *body_file = fopen(body_filename.c_str(), "w");
#endif
		//if (body_file == NULL)
		//	return -1;
		CURL *curl;
		CURLcode res;
		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://getlucky.ucoz.net");
			// example.com is redirected, so we tell libcurl to follow redirection 
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0");
			curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1); 
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, body_file);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			// сохраняем заголовок
			curl_easy_setopt(curl, CURLOPT_WRITEHEADER, header_file);
			//USING CURLOPT NOBODY
			//curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
			// Perform the request, res will get the return code 
			res = curl_easy_perform(curl);
			// Check for errors 
			//if (res != CURLE_OK)
			//	std::cout << "curl_easy_perform() failed: %s\n" << curl_easy_strerror(res) << std::endl;
			// always cleanup 
			curl_easy_cleanup(curl);
		}
		fclose(body_file);
		fclose(header_file);
#ifdef _WINDOWS_2
		fopen_s(&body_file, body_filename.c_str(), "r");
#else
		body_file = fopen(body_filename.c_str(), "r");
#endif
		//if (body_file == NULL)
		//	return -1;
		char *str = new char[64];
		std::string stroke = "";
		while (!feof(body_file))
		{
			fgets(str, 64, body_file);
			if (strstr(str, "random1="))
				stroke += str;
		}
		fclose(body_file);
		delete[] str;
		int j = 0;
		while (stroke[j++] != '=')
			;
		std::string *strmas = new std::string[14];
		for (int i = 0; i < 14; i++)
		{
			while (stroke[j] != '|')
				strmas[i] += stroke[j++];
			strmas[i] += stroke[j++];
			//std::cout << strmas[i] << std::endl;
		}
		std::string totalstr = "";
		srand(time(0));
		int max_ = 14, min_ = 0;
		for (int i = 0; i<30; i++)
			totalstr += strmas[((int__)((float__)rand() / RAND_MAX*(max_ - min_) + min_))];
		//std::cout << totalstr << std::endl;
		Drum_->SetBuffer((char__*)totalstr.c_str()/*"4|5|6|7|8|9|10|11|12|13|14|15|16|17|4|5|6|7|8|9|10|11|12|13|14|15|16|17|4|5"*/);
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
    //delete Con_;
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
