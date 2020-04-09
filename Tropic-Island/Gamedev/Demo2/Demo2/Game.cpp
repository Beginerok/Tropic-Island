#include "Game.h"

Game::Game()
{
	run = true;
	loading = true;
	iter = -1;
	bonus = false;
	firsttime = false;
}
void Game::setup_opengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluPerspective(189, 0.5, 0.6, 0.6);
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
		if (!firsttime && Logic_->dbconn->userid != -1)
		{
			firsttime = true;
			Logic_->SetCredits();
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask (GL_TRUE);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_COLOR_MATERIAL*/);
		glEnable(GL_TEXTURE_2D);
		
		int countdrums = 5;
		int counttextureondrums = 6;
		if (!loading) 
		{
			if (!WindowsWinApi_->GetF()[2] && WindowsWinApi_->pressbutton == 1 && WindowsWinApi_->upbutton == 0)
			{
				Logic_->SetCredits(Logic_->GetCredits() - Logic_->GetTotalBet());
			}
			if (WindowsWinApi_->GetF()[1])
			{
				Logic_->firstline = false;
				Logic_->secondline = false;
				Logic_->thirdline = false;
				Logic_->SetCredits(Logic_->GetCredits()+Logic_->GetWin());
				Logic_->SetWin(0.0f);
			}
			Scene1_->ShowDrum(countdrums, counttextureondrums, Logic_->GetDrum(),
#if WINAPI_==0
				WindowsSDLApi_->GetF(),
				WindowsSDLApi_->pressbutton
#else
				WindowsWinApi_->GetF(),
				WindowsWinApi_->pressbutton,
				&WindowsWinApi_->upbutton
#endif
			);
			
			Scene1_->ShowButtons();
			Scene1_->ShowNumbersAndWords(Logic_->GetCredits(), Logic_->GetWin(),Logic_->GetTotalBet());

			Scene1_->ShowBorder();
			Scene1_->ShowLine(Logic_->firstline,Logic_->secondline,Logic_->thirdline);
			Logic_->CheckWin();
			if (WindowsWinApi_->GetF()[0])
			{
				Scene1_->ShowHelp();
			}
		}
		else
			Scene1_->ShowWelcome(loading);
		glDisable(GL_TEXTURE_2D);
#if WINAPI_== 1
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
		if (iter > 17)
			iter = 17;
		Sound_->Play(0);
	}
	Exit();
}
int Game::Execute()
{
	bool fullscreen = false;
#if WINAPI_==1
	WindowsWinApi_ = new WindowsWinApi();
	if (!WindowsWinApi_->keyboard__->CreateWindow_(L"Cars",700,500, 32, fullscreen))
		return 0;
#else
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Tropic Island", 10, 10,700 ,500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
#endif
	setup_opengl(700,500);

	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene1_->LoadButtons();
	//
	Scene1_->LoadNumbersAndWords();
	//
#if WINAPI_ == 0
	WindowsSDLApi_ = new WindowsSDLApi();
#endif
	Logic_ = new Logic();
	Logic_->dbconn = WindowsWinApi_->keyboard__->db;
	Logic_->dbconn->Connect();
	Logic_->dbconn->Query();
	Logic_->SetTotalBet(1);
	Logic_->SetWin(0);
	Sound_ = new Sound();
	Sound_->Init();
	Scene1_->LoadBorder();
	draw_screen();
#if WINAPI_==1
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
