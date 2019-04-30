#pragma once
//#define _WINDOWS_2
#ifdef _WINDOWS_2
#include <Windows.h>
#else
#include <Windows.h> 
#define SDL_MAIN_HANDLED

#include "SDL/SDL.h"
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"Glu32.lib")
#pragma comment(lib,"ILU.lib")
#pragma comment(lib,"DevIl.lib")
#pragma comment(lib,"SDL2.lib")
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef _WINDOWS_2
#include <IL\il.h>
#include <IL\ilu.h>
#pragma comment(lib,"ILU.lib")
#pragma comment(lib,"DevIl.lib")
#else
#include "IL/il.h"
#include "IL/ilu.h"
#include <string.h>
#endif // _WINDOWS_2
#include<string>
//#include "Vector3.h"
//#include "FileReader.h"
#include <vector>
#include <time.h>
#include <random>
//#include <chrono>
struct Image
{
	float**TextureCoordinats;
	float**VertexCoordinats;
	unsigned int*IndexTexture;
	std::string *Name;
	int *number;
};

/*ref*/ class Scene1
{
public:
	Scene1(void);
	void LoadImage(const ILstring path);
	void ShowWelcome(bool show);
	void LoadWelcome();
	void EnableTexture(float*texcoor, float*vercoor);
	int FindTexture(std::string name);
	int LoadDrum(int iter);
	void ShowDrum(int countdrums,/* float*rotate_,*/ int counttextureondrums/*, int**drum, int credits, int win, int totalbet, const char*line, int bet, bool*lines, int**ms, bool*buttons*/);
	void EnableTexture(int n, int m);
	void EnablePolygonFrontUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontDown(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackDown(float leftup, float leftdown, float rightdown, float rightup);
	void Rotate(/*bool__*buttons*/);
	void StartRotate();
	int GetRandom();
	int *GetRandomMassive();


	int GetMassive(int number);//02.03.2019
	void SetMassive(int number, int value);

	~Scene1();
	int err;
#ifdef _WINDOWS_2
	 char*strError;
	//or  wchar_t*strError;
#else
	//or const char*strError;
	wchar_t*strError;
#endif
	// Ширина изображения
	int width;
	// Высота изображения
	int height;
	// Тип хранения данных
	unsigned int type;
	unsigned char*copyData;
	static const int CountTexture = 30;
	Image *image;
	int CountIndexTexture;
	int AnimateBar;
	std::string NameAnimateBar;

//	std::vector<Vector3>listv;
	//std::vector<Vector3>listt;
	float xl, xr, yd, yu, z;
	float*rotate;
	bool*startrotate;
	static const int CountDrum = 5;
	std::vector<std::string>vectordrum;

	/*	volatile */int random, *randommassive;
	int max_, min_;
	bool start;
	bool b;
};

