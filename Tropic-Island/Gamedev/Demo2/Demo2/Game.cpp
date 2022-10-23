#include "Game.h"

Game::Game()
{
	run = true;
	loading = true;
	iter = -1;
	bonus = false;
	firsttime = false;
	online = false;
}
void Game::setup_opengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	//glShadeModel(GL_SMOOTH);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluPerspective(189, 0.5, 0.6, 0.6);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	ilInit(); // Инициализация основной библиотеки
	iluInit(); // Инициализация библиотеки утилит
	ilEnable(IL_CONV_PAL);
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}
void Game::draw_screen()
{
	while (run)
	{
#ifdef _WIN32
		if (!WindowsWinApi_->keyboard__->offline && !online)
			Sound_->Play(2);
		online = !WindowsWinApi_->keyboard__->offline;
#else

#endif
		if (!firsttime
#if DBAPI_ == 1
			&& Logic_->dbconn->userid != -1
#endif
			)
		{
			firsttime = true;
			Logic_->SetCredits();//
		}
		//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        //glDepthMask(GL_TRUE);
        //glClearColor(0.0f,0.0f,0.0f,1.0f);
        //glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		int countdrums = 5;
		int counttextureondrums = 6;
		if (!loading)
		{
#ifdef _WIN32
			if (!WindowsWinApi_->GetF()[2] && WindowsWinApi_->pressbutton == 1 && WindowsWinApi_->upbutton == 0)
#else
			if (!WindowsSDLApi_->GetF()[2] && WindowsSDLApi_->pressbutton == 1 && WindowsSDLApi_->upbutton == 0)
#endif
			{
				Sound_->Play(5);
				if (Logic_->firstline || Logic_->secondline || Logic_->thirdline)
				{
					Logic_->firstline = false;
					Logic_->secondline = false;
					Logic_->thirdline = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);//
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
				}
				Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet(),online);//
				Logic_->checkwin = false;
			}
#ifdef _WIN32
			if (WindowsWinApi_->GetF()[1] && !bonus)
#else
			if (WindowsSDLApi_->GetF()[1])
#endif
			{
				Logic_->firstline = false;
				Logic_->secondline = false;
				Logic_->thirdline = false;
				Logic_->SetCredits(Logic_->GetCredits()+Logic_->GetWin(),online);//
				Logic_->SetWin(0.0f);
				Sound_->Play(4);
			}
			if (Logic_->GetWin() > 0 && !bonus && WindowsWinApi_->GetF()[3])
			{
				bonus = true;
				WindowsWinApi_->setF(false, 3);
				WindowsWinApi_->setF(false, 0);
				WindowsWinApi_->setF(false, 1);
				WindowsWinApi_->setF(false, 2);
				WindowsWinApi_->setF(false, 4);
				Logic_->SetRandom();
			}
			if ((Logic_->GetWin() > 0 && bonus && WindowsWinApi_->GetF()[1]) || (bonus && Logic_->GetWin() == 0))
			{
				bonus = false;
				WindowsWinApi_->setF(false, 1);
				WindowsWinApi_->setF(false, 0);
				WindowsWinApi_->setF(false, 2);
				WindowsWinApi_->setF(false, 3);
				WindowsWinApi_->setF(false, 4);
			}
			if(bonus)
				Scene2_->ShowBackGround(WindowsWinApi_->GetF(), Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
			else
			{
				if (Scene1_->ShowDrum(countdrums, counttextureondrums,
					Logic_->GetDrum(),
#ifndef _WIN32
					WindowsSDLApi_->GetF(),
					WindowsSDLApi_->pressbutton,
					&WindowsSDLApi_->upbutton

#else
					WindowsWinApi_->GetF(),
					WindowsWinApi_->pressbutton,
					&WindowsWinApi_->upbutton
#endif
				))
					Sound_->Play(6);

				Scene1_->ShowButtons();
				Scene1_->ShowNumbersAndWords(Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				Scene1_->ShowBorder();
				Scene1_->ShowLine(Logic_->firstline, Logic_->secondline, Logic_->thirdline);
			}
			if (Logic_->CheckWin())
				Sound_->Play(3);
#ifdef _WIN32
			if (WindowsWinApi_->GetF()[0] && !bonus)
#else
			if (WindowsSDLApi_->GetF()[0] && !bonus)
#endif
			{
				Scene1_->ShowHelp();
				Sound_->Pause(0);
				if(WindowsWinApi_->keyboard__->enablesound)
					Sound_->Play(1);
			}
			else
				Sound_->Pause(1);
		}
		else
			Scene1_->ShowWelcome(loading);
		glDisable(GL_TEXTURE_2D);
#if _WIN32
		WindowsWinApi_->keyboard__->Show();
		WindowsWinApi_->Update(bonus, Logic_);
		run = !WindowsWinApi_->getdone();
#else
		SDL_GL_SwapWindow(window);
		SDL_PollEvent(&event_);
		SDL_PumpEvents();
		WindowsSDLApi_->Update(bonus,Logic_,event_);
		run = !WindowsSDLApi_->getdone();
#endif
		loading = Scene1_->LoadDrum(++iter);
		if (iter > 15)
			loading = Scene1_->LoadButtons(++iter);
		if (iter > 16)
			loading = Scene1_->LoadWords(++iter);
		if (iter > 17)
			loading = Scene1_->LoadNumbers(++iter);
		if (iter > 18)
			loading = Scene1_->LoadBorder(++iter);
		if (iter > 19)
			iter = 20;
#if _WIN32
		if (WindowsWinApi_->keyboard__->enablesound)
			Sound_->Play(0);
		else
			Sound_->StopAll();
#else
        Sound_->Play(0);
#endif
	}
	Exit();
}
int Game::Execute(int argc, char*argv[])
{
	bool fullscreen = false;
#ifdef _WIN32
	WindowsWinApi_ = new WindowsWinApi();
	if (!WindowsWinApi_->keyboard__->CreateWindow_(L"Cars",700,500, 32, fullscreen))
		return 0;
#else
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Cars", 10, 10,700 ,500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
#endif
	setup_opengl(700,500);
	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene2_ = new Scene2();
	Scene2_->SetData();
#ifndef _WIN32
	WindowsSDLApi_ = new WindowsSDLApi();
#endif
	Logic_ = new Logic();
#if DBAPI_ == 1
	Logic_->dbconn = WindowsWinApi_->keyboard__->db;
	Logic_->dbconn->Connect();
	Logic_->dbconn->Query();
#endif
	Logic_->SetTotalBet(1);
	Logic_->SetWin(0);
	Logic_->SetCredits(1000,online);
	Sound_ = new Sound();
	Sound_->Init(argc, argv);
	draw_screen();
#if _WIN32
	WindowsWinApi_->keyboard__->KillWindow();
#else
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
#endif
	return 0;
}
void Game::Exit()
{
	run = false;
}
Game::~Game()
{
}
