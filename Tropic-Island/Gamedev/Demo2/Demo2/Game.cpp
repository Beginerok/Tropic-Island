#include "Game.h"

Game::Game()
{
	run = true;
	loading = true;
	iter = -1;
	bonus = false;
	firsttime = false;
	online = false;
	wait = false;
	tmpcounter = 0;
	number = -1;
}
void Game::setup_opengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	//glShadeModel(GL_SMOOTH);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluPerspective(189, 0.5, 0.6, 0.6);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	ilInit(); // Инициализация основной библиотеки
	iluInit(); // Инициализация библиотеки утилит
	ilEnable(IL_CONV_PAL);
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}
void Game::draw_screen()
{
	glEnable(GL_DEPTH_TEST);
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
			if (!WindowsWinApi_->GetF()[2] && WindowsWinApi_->pressbutton == 1 && WindowsWinApi_->upbutton == 0 && !bonus)
#else
			if (!WindowsSDLApi_->GetF()[2] && WindowsSDLApi_->pressbutton == 1 && WindowsSDLApi_->upbutton == 0 && !bonus)
#endif
			{
				Sound_->Play(5);
				if (Logic_->firstline || Logic_->secondline || Logic_->thirdline)
				{
					Logic_->firstline = false;
					Logic_->secondline = false;
					Logic_->thirdline = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
				}
				Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet(), online);
				Logic_->checkwin = false;
				showline = false;
			}
#ifdef _WIN32
			if (WindowsWinApi_->GetF()[1] && !bonus)
#else
			if (WindowsSDLApi_->GetF()[1] && !bonus)
#endif
			{
				Logic_->firstline = false;
				Logic_->secondline = false;
				Logic_->thirdline = false;
				Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
				Logic_->SetWin(0.0f);
				Sound_->Play(4);
			}
			if (Logic_->GetWin() > 0 && !bonus && WindowsWinApi_->GetF()[3])
			{
				bonus = true;
				Logic_->SetRandom();
			}
			if (bonus || wait)
			{
				if ((Logic_->GetWin() > 0 && WindowsWinApi_->GetF()[5]))
				{
					bonus = false;
					Logic_->firstline = false;
					Logic_->secondline = false;
					Logic_->thirdline = false;
					Logic_->SetCredits(Logic_->GetCredits() + Logic_->GetWin(), online);
					Logic_->SetWin(0.0f);
					Sound_->Play(4);
				}
				for (int i = 6; i < 10; i++)
				{
					if (WindowsWinApi_->GetF()[i] && !wait)
					{
						wait = true;
						tmpcounter = 0;
						//now = std::time(0);
						//ltm = localtime(&now);
						number = i;
					}
				}
				glDisable(GL_DEPTH_TEST);
				Scene2_->ShowBackGround(WindowsWinApi_->GetF(), Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
				Sound_->Play(7);
				if (wait)
				{
					//std::time_t tmpnow = std::time(0);
					//tm* tmpltm = localtime(&now);
					//if (abs(ltm->tm_sec - tmpltm->tm_sec) > 2)
					if (tmpcounter > 30)
					{
						/*
						for(int i=2;i<54;i++)
							std::cout <<(i - 2) % 13 << std::endl;*/
						wait = false;
						for (int i = number; i < number + 1; i++)
						{
							//if (WindowsWinApi_->GetF()[i])
							{
								if (((Logic_->GetRandom()[0] - 3) % 13) < ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									//WindowsWinApi_->setF(false, 1);
									Logic_->SetWin(Logic_->GetWin() * 2);
									Sound_->Play(3);
									//Sleep(1000);
									Logic_->SetRandom();
								}
								else if (((Logic_->GetRandom()[0] - 3) % 13) > ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									//WindowsWinApi_->setF(false, 1);
									Logic_->SetWin(0);
									Sound_->Play(8);
									//Sleep(1000);
									bonus = false;
									Logic_->firstline = false;
									Logic_->secondline = false;
									Logic_->thirdline = false;
								}
								else// if (((Logic_->GetRandom()[0] - 2) % 14) == ((Logic_->GetRandom()[i - 2] - 2) % 14))
								{
									//WindowsWinApi_->setF(false, 1);
									//Sleep(1000);
									Logic_->SetRandom();
								}
							}
						}
					}
				}
				tmpcounter++;
			}
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
				{
					Sound_->Play(6);
					showline = true;
				}
				Scene1_->ShowButtons();
				Scene1_->ShowNumbersAndWords(Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
				Scene1_->ShowBorder();
				if (showline)
				{
					if (Logic_->CheckWin())
						Sound_->Play(3);
					glDisable(GL_DEPTH_TEST);
					Scene1_->ShowLine(Logic_->firstline, Logic_->secondline, Logic_->thirdline);
					glEnable(GL_DEPTH_TEST);
				}
			}
#ifdef _WIN32
			if (WindowsWinApi_->GetF()[0] && !bonus)
#else
			if (WindowsSDLApi_->GetF()[0] && !bonus)
#endif
			{
				glDisable(GL_DEPTH_TEST);
				Scene1_->ShowHelp();
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
				if(WindowsWinApi_->keyboard__->enablesound)
					Sound_->Play(1);
			}
			else
				Sound_->Pause(1);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			Scene1_->ShowWelcome(loading);
			glEnable(GL_DEPTH_TEST);
		}
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
		{
			Sound_->Play(0);
			Sound_->Pause(7);
		}
		else
			Sound_->StopAll();
#else
        Sound_->Play(0);
#endif
		glFlush();
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
