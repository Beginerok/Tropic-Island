#include "BasicGame.h"

BasicGame::BasicGame()
{
	run = true;
	loading = true;
	iter = -1;
	scene_ = new Scene();
}
void BasicGame::setup_opengl(int width, int height)
{
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluPerspective(189, 0.5, 0.6, 0.6);
	//ilInit(); // Инициализация основной библиотеки
	//iluInit(); // Инициализация библиотеки утилит
	//ilEnable(IL_CONV_PAL);
	//ilEnable(IL_ORIGIN_SET);
	//ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}


void BasicGame::draw_screen()
{
	while (run)
	{
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_COLOR_MATERIAL*/);
		glEnable(GL_TEXTURE_2D);
		
		{
			scene_->Show();
			scene_->ShowFigure();
			
		}

		glDisable(GL_TEXTURE_2D);
		SDL_GL_SwapWindow(window);
		SDL_PollEvent(&event_);
		SDL_PumpEvents();
		keyboard_->Update(event_);
		run = !keyboard_->getdone();
	}
	Exit();
}
int BasicGame::Execute()
{
	bool fullscreen = false;;
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Simple Chess", 10, 10, 700, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	setup_opengl(700, 500);
	keyboard_ = new Keyboard();
	glColor3d(1.0, 0.0, 0.0);
	//Logic_ = new Logic();
	//Logic_->SetRandom();

	scene_->Initialize();
//
	draw_screen();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
void BasicGame::Exit()
{
	run = false;
}
BasicGame::~BasicGame()
{
}