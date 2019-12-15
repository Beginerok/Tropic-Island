#include "Game.h"

Game::Game()
{
	run = true;
	loading = true;
	iter = -1;
	bonus = false;
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
	ilInit(); // ������������� �������� ����������
	iluInit(); // ������������� ���������� ������
	ilEnable(IL_CONV_PAL);
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}
void Game::draw_screen()
{
	while (run)
	{
        glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask (GL_TRUE);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_COLOR_MATERIAL*/);
		glEnable(GL_TEXTURE_2D);
		
		int countdrums = 5;
		/*
		float*rotate_;
		*/
		int counttextureondrums = 6;
		/*
		int**drum;
		int credits;
		int win; 
		int totalbet;
		const char*line;
		int bet;
		bool*lines;
		int**ms;
		*/
		//bool*buttons;
		if (!loading) 
		{
		
			Scene1_->ShowDrum(countdrums,/*rotate_,*/counttextureondrums, Logic_->GetDrum(),/*Logic_->GetRandom(),credits,win,totalbet,line,bet,lines,ms,buttons*/
			/*Math_->GetCountDrums(), Math_->GetRotate(), Math_->GetCountTextureOnDrums(), Math_->GetDrums(),
				Math_->GetCredits(), Math_->GetWin_(), Math_->GetTotalBet(), Math_->GetLines_(), Math_->GetBet(),
				Math_->GetLines(), Math_->GetMS()*/
#if WINAPI_==0
				WindowsSDLApi_->GetF(),
				WindowsSDLApi_->pressbutton
#else
				WindowsWinApi_->GetF(),
				WindowsWinApi_->pressbutton
#endif
			);
			
			Scene1_->ShowButtons();
			Scene1_->ShowNumbersAndWords();
			Scene1_->ShowBoomer();
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
	}
	Exit();
}
int Game::Execute()
{
	bool fullscreen = false;
#if WINAPI_==1
	WindowsWinApi_ = new WindowsWinApi();
	if (!WindowsWinApi_->keyboard__->CreateWindow_(L"Tropic Island",700,500, 32, fullscreen))
		return 0;
#else
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Tropic Island", 10, 10,700,500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
#endif
	setup_opengl(700,500);

	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene1_->LoadButtons();
	//
	Scene1_->LoadNumbersAndWords();
	Scene1_->LoadBoomer();
	//
#if WINAPI_ == 0
	WindowsSDLApi_ = new WindowsSDLApi();
#endif
	Logic_ = new Logic();
	Logic_->SetRandom();
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
