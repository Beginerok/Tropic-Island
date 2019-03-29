#include "Game.h"

Game::Game()
{
	run = true;
	loading = true;
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_MATERIAL);
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
		bool*buttons;
		*/
		//Scene1_->ShowWelcome(loading);
		Scene1_->ShowDrum(countdrums,/*rotate_,*/counttextureondrums/*,drum,credits,win,totalbet,line,bet,lines,ms,buttons*/
			/*Math_->GetCountDrums(), Math_->GetRotate(), Math_->GetCountTextureOnDrums(), Math_->GetDrums(),
				Math_->GetCredits(), Math_->GetWin_(), Math_->GetTotalBet(), Math_->GetLines_(), Math_->GetBet(),
				Math_->GetLines(), Math_->GetMS(), Math_->keyboard_->GetF()*/);
		glDisable(GL_TEXTURE_2D);
#ifdef _WINDOWS_2
		//Math_->keyboard_->keyboard__->Show();
		Window_->Show();
#else
		SDL_GL_SwapWindow(window);
#endif
#ifndef _WINDOWS_2
		Math_->Update(&run, bonus, Logic_, event_);
#else
		Window_->Update();
		//Math_->Update(&run, bonus, Logic_);
#endif
		loading = false;
	}
	Exit();
}
int Game::Execute()
{
	//Math_ = new Math();
	Window_ = new Window();
	bool fullscreen = false;/* Math_->Init()*/;
#ifdef _WINDOWS_2
	if (!/*Math_->keyboard_->keyboard__*/Window_->CreateWindow_(L"Tropic Island",1024/* Math_->GetResolution().x*/,768/* Math_->GetResolution().y*/, 32, fullscreen))
		return 0;
#else
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Tropic Island", 0, 0, 1024/*Math_->GetResolution().x*/,768/* Math_->GetResolution().y*/, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
#endif
	setup_opengl(1024/*Math_->GetResolution().x*/,768/*Math_->GetResolution().y*/);

	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene1_->LoadDrum();

	draw_screen();
#ifdef _WINDOWS_2
	/*Math_->keyboard_->keyboard__*/Window_->KillWindow();
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