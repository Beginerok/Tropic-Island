#ifndef GAME_H
#define GAME_H
#include "Scene.h"
#include "Scene2.h"
#include "Scene1.h"
#include "Math.h"
#include "Logic.h"
#ifndef _WINDOWS_2
    #include <SDL.h>
#endif
class Math;
class Game
{
private:
protected:
    bool__ run;
    Math *Math_;
	Scene *Scene_;
	Scene2 *Scene2_;
	Scene1 *Scene1_;
	void__ draw_screen();
    void__ setup_opengl(int__ width,int__ height);
	bool__ bonus;
	Logic *Logic_;
	bool__ loading;
#ifndef _WINDOWS_2
    SDL_Window*window;
    SDL_Event event_;
#endif
public:
    Game();
    int__ Execute();
    void__ Exit();

	~Game();
};
#endif
