#ifndef GAME_H
#define GAME_H
#include "Scene.h"
#include "Scene2.h"
#include "Math.h"
#include "Logic.h"
#ifndef _WINDOWS_
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
	void__ draw_screen();
    void__ setup_opengl(int__ width,int__ height);
	bool__ bonus;
	Logic *Logic_;
#ifndef _WINDOWS_
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
