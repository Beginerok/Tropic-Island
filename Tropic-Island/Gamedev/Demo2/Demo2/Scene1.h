#pragma once
//#define _WINDOWS_2
#ifdef __unix__
#else
	#include <Windows.h>
#endif
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Animation.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
struct Image
{
	//float**TextureCoordinats;
	float**VertexCoordinats;
	unsigned int*IndexTexture;
	std::string *Name;
	int *number;
};
struct Image_s
{
	float Xleft;
	float Xright;
	float Yup;
	float Ydown;
	float Z;
	unsigned int IndexTexture;
	std::string Name;
	int number;
	bool alpha;
};

struct Coor
{
	std::vector<float> x;
	float y;
	float width;
	float height;
};
struct Image_d
{
	Coor coor;
	unsigned int IndexTexture;
	std::string Name;
	int number;
};
class Scene1
{
public:
	Scene1(void);
	unsigned int LoadImage(const ILstring path);
	void ShowWelcome(bool show);
	void LoadWelcome();//numbers
	void EnableTexture(Image_s im, bool third,bool alpha);
	int FindTexture(std::string name);
	int FindTexture(std::string name, std::vector<Image_s> vec);
	int LoadDrum(int iter);//numbers
	void ShowDrum(int countdrums, int counttextureondrums, std::vector<std::string> drum,
		bool* buttons, int pressbutton,int *upbutton);
	void EnableTexture(int n, int m);//numbers
	void EnablePolygonFrontUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonFrontDown(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackUp(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackMiddle(float leftup, float leftdown, float rightdown, float rightup);
	void EnablePolygonBackDown(float leftup, float leftdown, float rightdown, float rightup);
	void Rotate();
	void StartRotate(int *upbutoon);

	void LoadButtons();//numbers
	void ShowButtons();
	void EnableTextureButtons(int i);//numbers

	void LoadWords();//numbers
	void ShowNumbersAndWords(int credits,int win,int totalbet);
	void EnableTextureNumbersAndWords(int i,int win);//numbers
	void LoadAnimatedAuto();

	void DrawNumbers(int number,int pos);//malloc free numbers
	void EnableTextureNumbers(int position, int numberword);
	void LoadBorder();//numbers
	void ShowBorder();
	void ShowHelp();//numbers
	void ShowLine(bool firstline,bool secondline, bool thirdline);//numbers
	void LoadNumbers();
	~Scene1();
	int err;
#ifndef _WIN32
	const char* strError;
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
	static const int CountTexture = 58;// 57;//40//53
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
	bool start;
	std::vector<std::string>vectornumbersandwords;
	std::ofstream flogout;
	std::vector<std::string>vectorboomer;
	int animateboomer, slowlychangesprite;
	Animation *animation,*animation2,*animation3;
	int **drumanimation;
	int *speedchangeanimation;
	Coor* coor;
	std::vector<std::string>vectorram;
	float scale;
	bool scaling;


	std::vector<Image_s> welcomev;

	std::vector<Image_s>buttonsv;

	std::vector<Image_s>wordsv;

	std::vector<Image_s>borderhelpv;
};
