#pragma once
//#define _WINDOWS_2
#ifdef __unix__
#else
	#include <Windows.h>
#endif

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include "Animation.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "IL/il.h"
//#include "IL/ilu.h"
#include <string.h>
//#include <string>
//#include <vector>
#include <iostream>
#include <fstream>
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
	void EnableTexture(float* texcoor, float* vercoor);
	int FindTexture(std::string name);
	int LoadDrum(int iter);
	void ShowDrum(int countdrums,/* float*rotate_,*/ int counttextureondrums, std::vector<std::string> drum,
		/*int*DrumPosition, int credits, int win, int totalbet, const char*line, int bet, bool*lines, int**ms,*/
		bool* buttons, int pressbutton);
	void EnableTexture(int n, int m);
	void EnablePolygonFrontUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontDown(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackDown(float leftup, float leftdown, float rightdown, float rightup);
	void Rotate(/*bool__*buttons*/);
	void StartRotate();
	//int GetRandom();
	//int *GetRandomMassive();


	//int GetMassive(int number);//02.03.2019
	//void SetMassive(int number, int value);

	void LoadButtons();
	void ShowButtons();
	void EnableTextureButtons(int i);

	void LoadNumbersAndWords();
	void ShowNumbersAndWords();
	void EnableTextureNumbersAndWords(int i);
	void LoadBoomer();
	void ShowBoomer();
	void EnableTextureBoomer(int i);
	~Scene1();
	int err;
#ifdef _WINDOWS_2
	char* strError;
	//or  wchar_t*strError;
#else
	//or const char*strError;
	wchar_t* strError;
#endif
	// Ширина изображения
	int width;
	// Высота изображения
	int height;
	// Тип хранения данных
	unsigned int type;
	unsigned char* copyData;
	static const int CountTexture = 57;//40//53
	Image* image;
	int CountIndexTexture;
	int AnimateBar;
	std::string NameAnimateBar;

	float xl, xr, yd, yu, z;
	float* rotate;
	bool* startrotate;
	static const int CountDrum = 5;
	static const int CountTextureOnDrum = 6;
	std::vector<std::string>vectordrum;

	std::vector<std::string>vectorbuttons;

	//volatile int random, *randommassive;
	//int max_, min_;
	bool start;

	std::vector<std::string>vectornumbersandwords;
	std::ofstream flogout;// ("log.txt");
	std::vector<std::string>vectorboomer;
	int animateboomer, slowlychangesprite;
	Animation *animation,*animation2,*animation3;
	int **drumanimation;
	int *speedchangeanimation;
};
