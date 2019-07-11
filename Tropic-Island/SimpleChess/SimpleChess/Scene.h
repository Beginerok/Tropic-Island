#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"Glu32.lib")
struct Chest
{
	float x1, y1, x2, y2;
	float r, g, b;
};
Chest tmp;
class Scene
{
public:
	Scene();
	void Initialize();
	void Show();
	void Chest_(float x1,float y1,float x2,float y2);
	void ShowFigure();
	std::vector<Chest> *vec;
	~Scene();
};
#endif
