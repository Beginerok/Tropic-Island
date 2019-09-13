#include "Game.h"
Game::Game()
{
    run=true;
	bonus = false;
	Logic_ = new Logic();
	loading = true;
}
void__ Game::draw_screen()
{
    while(run)
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		if (Math_->GetWin_() > 0 && !bonus && Math_->keyboard_->getF(3) == true)
		{
			bonus = true;
			Math_->keyboard_->setF(false, 3);
			Math_->keyboard_->setF(false, 0);
			Math_->keyboard_->setF(false, 1);
			Math_->keyboard_->setF(false, 2);
			Math_->keyboard_->setF(false, 4);
			Logic_->SetRandom();
		}
		if ((Math_->GetWin_() > 0 && bonus && Math_->keyboard_->getF(1) == true) || (bonus && Math_->GetWin_() == 0))
		{
			bonus = false;
			Math_->keyboard_->setF(false, 1);
			Math_->keyboard_->setF(false, 0);
			Math_->keyboard_->setF(false, 2);
			Math_->keyboard_->setF(false, 3);
			Math_->keyboard_->setF(false, 4);
		}
		if (!bonus){
			/*
			Scene1_->ShowDrum(Math_->GetCountDrums(), Math_->GetRotate(), Math_->GetCountTextureOnDrums(), Math_->GetDrums(),
				Math_->GetCredits(), Math_->GetWin_(), Math_->GetTotalBet(), Math_->GetLines_(), Math_->GetBet(),
				Math_->GetLines(), Math_->GetMS(), Math_->keyboard_->GetF());
			*/
			//Scene1_->ShowWelcome(loading);
			Scene_->Show(Math_->GetCountDrums(), Math_->GetRotate(), Math_->GetCountTextureOnDrums(), Math_->GetDrums(),
				Math_->GetCredits(), Math_->GetWin_(), Math_->GetTotalBet(), Math_->GetLines_(), Math_->GetBet(),
				Math_->GetLines(), Math_->GetMS(), Math_->keyboard_->GetF());
		}
		else
		{
			Logic_->SetCredits(Math_->GetCredits());
			Logic_->SetWin(Math_->GetWin_());
			Logic_->SetTotalBet(Math_->GetTotalBet());
			Scene2_->ShowBackGround(Math_->keyboard_->GetF(), Logic_->GetRandom(),
				Logic_->GetCredits(), Logic_->GetWin(), Logic_->GetTotalBet());
		}
		glDisable(GL_TEXTURE_2D);
#ifdef _WINDOWS_2
			Math_->keyboard_->keyboard__->Show();
#else
        SDL_GL_SwapWindow(window);
#endif
#ifndef _WINDOWS_2
        Math_->Update(&run,bonus,Logic_,event_);
#else
        Math_->Update(&run,bonus,Logic_);
#endif
		loading = false;
    }
    Exit();
}
void__ Game::setup_opengl(int__ width,int__ height)
{
    glClearColor(0,0,0,0);
    glViewport(0,0,width,height);
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
    gluPerspective(189,0.5,0.6,0.6);
	ilInit(); // Инициализация основной библиотеки
	iluInit(); // Инициализация библиотеки утилит
	ilEnable(IL_CONV_PAL);
    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}
int__ Game::Execute()
{
    Math_=new Math();
    bool fullscreen=Math_->Init();
#ifdef _WINDOWS_2
	if(!Math_->keyboard_->keyboard__->CreateWindow_(L"Tropic Island",Math_->GetResolution().x,Math_->GetResolution().y,32,fullscreen))
		return 0;
#else
    SDL_GLContext context;
    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("Tropic Island",0,0,Math_->GetResolution().x,Math_->GetResolution().y,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    context=SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
#endif
	setup_opengl(Math_->GetResolution().x,Math_->GetResolution().y);

	Scene_ = new Scene();
	Scene2_ = new Scene2();
	Scene2_->SetData();
//	Scene2_->LoadWelcome();
	
	Scene1_ = new Scene1();
	Scene1_->LoadWelcome();
	Scene1_->LoadDrum();
	
    draw_screen();
#ifdef _WINDOWS_2
	Math_->keyboard_->keyboard__->KillWindow();
#else
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
    return 0;
}
void Game::Exit()
{
    run=false;
}
Game::~Game()
{
	//delete run;
    delete Math_;
    delete Scene_;
    delete Scene2_;
	delete Logic_;
}
