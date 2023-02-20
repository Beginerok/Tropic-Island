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
#if WINAPI_==1 || SDLAPI_==1
void Game::setup_opengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
void Game::draw_screen()
{
	glEnable(GL_DEPTH_TEST);
	while (run)
	{
#if WINAPI_==1
		if (!WindowsWinApi_->keyboard__->offline && !online)
			Sound_->Play(2);
		online = !WindowsWinApi_->keyboard__->offline;
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		int countdrums = 5;
		int counttextureondrums = 6;
		if (!loading)
		{
#if WINAPI_==1
			if (!WindowsWinApi_->GetF()[2] && WindowsWinApi_->pressbutton == 1 && WindowsWinApi_->upbutton == 0 && !bonus)
#elif SDLAPI_==1
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
#if WINAPI_==1
			if (WindowsWinApi_->GetF()[1] && !bonus)
#elif SDLAPI_==1
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
#if WINAPI_==1
			if (Logic_->GetWin() > 0 && !bonus && WindowsWinApi_->GetF()[3])
#elif SDLAPI_==1
			if (Logic_->GetWin() > 0 && !bonus && WindowsSDLApi_->GetF()[3])
#endif
			{
				bonus = true;
				Logic_->SetRandom();
			}
			if (bonus || wait)
			{
#if WINAPI_==1
				if ((Logic_->GetWin() > 0 && WindowsWinApi_->GetF()[5]))
#elif SDLAPI_==1
				if ((Logic_->GetWin() > 0 && WindowsSDLApi_->GetF()[5]))
#endif
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
#if WINAPI_==1
					if (WindowsWinApi_->GetF()[i] && !wait)
#elif SDLAPI_==1
					if (WindowsSDLApi_->GetF()[i] && !wait)
#endif
					{
						wait = true;
						tmpcounter = 0;
						number = i;
					}
				}
				glDisable(GL_DEPTH_TEST);
#if WINAPI_==1
				Scene2_->ShowBackGround(WindowsWinApi_->GetF(), Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
#elif SDLAPI_==1
				Scene2_->ShowBackGround(WindowsSDLApi_->GetF(), Logic_->GetRandom(), Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
#endif
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
				Sound_->Play(7);
				if (wait)
				{
					if (tmpcounter > 30)
					{
						wait = false;
						for (int i = number; i < number + 1; i++)
						{
							{
								if (((Logic_->GetRandom()[0] - 3) % 13) < ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									Logic_->SetWin(Logic_->GetWin() * 2);
									Sound_->Play(3);
									Logic_->SetRandom();
								}
								else if (((Logic_->GetRandom()[0] - 3) % 13) > ((Logic_->GetRandom()[i - 5] - 3) % 13))
								{
									Logic_->SetWin(0);
									Sound_->Play(8);
									bonus = false;
									Logic_->firstline = false;
									Logic_->secondline = false;
									Logic_->thirdline = false;
								}
								else
								{
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
#if SDLAPI_==1
					WindowsSDLApi_->GetF(),
					WindowsSDLApi_->pressbutton,
					&WindowsSDLApi_->upbutton

#elif WINAPI_==1
					WindowsWinApi_->GetF(),
					WindowsWinApi_->pressbutton,
					&WindowsWinApi_->upbutton
#endif
				))
				{
					Sound_->Play(6);
					showline = true;
				}
				else
				{
					for (int i = 0; i < Scene1_->CountDrum; i++)
						if (Scene1_->changedrum[i])
							Logic_->SetDrum(i);
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
#if WINAPI_==1
			if (WindowsWinApi_->GetF()[0] && !bonus)
#elif SDLAPI_==1
			if (WindowsSDLApi_->GetF()[0] && !bonus)
#endif
			{
				glDisable(GL_DEPTH_TEST);
				Scene1_->ShowHelp();
				glEnable(GL_DEPTH_TEST);
				Sound_->Pause(0);
#if WINAPI_==1
				if(WindowsWinApi_->keyboard__->enablesound)
#endif
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
#if WINAPI_==1
		WindowsWinApi_->keyboard__->Show();
		WindowsWinApi_->Update(bonus, Logic_);
		run = !WindowsWinApi_->getdone();
#elif SDLAPI_==1
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
#if WINAPI_==1
		if (WindowsWinApi_->keyboard__->enablesound)
		{
			Sound_->Play(0);
			Sound_->Pause(7);
		}
		else
			Sound_->StopAll();
#elif SDLAPI_==1
        Sound_->Play(0);
#endif
		glFlush();
	}
	Exit();
}
#endif
int Game::Execute(int argc, char*argv[])
{
	bool fullscreen = false;
#if WINAPI_==1
	WindowsWinApi_ = new WindowsWinApi();
	if (!WindowsWinApi_->keyboard__->CreateWindow_(L"Cars",700,500, 32, fullscreen))
		return 0;
	setup_opengl(700, 500);
#elif SDLAPI_==1
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Cars", 10, 10,700 ,500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	setup_opengl(700, 500);
#elif QTAPI_==1
	//QCoreApplication::addLibraryPath(".");
	QApplication a(argc, argv);
	QWidget qw;
	MyWidget mw(&qw);
#endif
#if QTAPI_==0
	ilInit();
	iluInit();
	Scene1_ = new Scene1();
	Scene2_ = new Scene2();
#endif
#if WINAPI_==1 || SDLAPI_==1
	Scene1_->LoadWelcome();
	Scene2_->SetData();
#endif
	
#if SDLAPI_==1
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
	Logic_->SetMinMax(0,6);
	Logic_->SetWin(5, 10, 15, 20, 25);
	Sound_ = new Sound();
	Sound_->Init(argc, argv);
	//std::cout << glGetString(GL_VERSION)<<std::endl;
#if SDLAPI_==1 || WINAPI_==1
	draw_screen();
#endif
#if WINAPI_==1
	WindowsWinApi_->keyboard__->KillWindow();
#elif SDLAPI_==1
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
#elif QTAPI_==1
	mw.SetElements(Scene1_, Scene2_, Logic_, Sound_);
	mw.show();
	a.exec();
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
