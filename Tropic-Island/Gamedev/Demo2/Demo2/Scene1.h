#pragma once
#define QTAPI_ 1
#define SDLAPI_ 0
#define WINAPI_ 0
#ifdef __unix__
#else
	#include <Windows.h>
#endif
#if SDLAPI_==1
	#define SDL_MAIN_HANDLED
	#include "SDL2/SDL.h"
#endif
#ifndef OGL
#define OGL
#endif
#include <fstream>
//#include <GL/gl.h>
#include <GL/glu.h>
#if SDLAPI_==1 || WINAPI_==1
#include <IL/il.h>
#include <IL/ilu.h>
#endif
#ifdef __unix__
#include <cstring>
#endif
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#if QTAPI_==1
	#include <QtWidgets/QtWidgets>
#endif
#ifdef Q_OS_LINUX
	#include <QtGui/qopengltexture.h>
#endif
#ifdef Q_OS_WIN
	#include <QtOpenGL/qopengltexture.h>
#endif
#ifdef _WIN32
	#pragma comment(lib,"OpenGL32.lib")
	#pragma comment(lib,"Glu32.lib")
	#pragma comment(lib,"ILU.lib")
	#pragma comment(lib,"DevIl.lib")
	#pragma comment(lib,"SDL2.lib")
#endif
#include <vector>
#include <set>
struct Image
{
	float**VertexCoordinats;
#if SDLAPI_==1 || WINAPI_==1
	unsigned int*IndexTexture;
#elif QTAPI_==1
	QOpenGLTexture* IndexTexture;
#endif
	std::string Name;
	int *number;
};
struct Image_s
{
	float Xleft;
	float Xright;
	float Yup;
	float Ydown;
	float Z;
#if SDLAPI_==1 || WINAPI_==1
	unsigned int IndexTexture;
#elif QTAPI_==1
	QOpenGLTexture *IndexTexture;
#endif
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
#if QTAPI_==1
	QOpenGLTexture* QTLoadImage(QString path);
	QImage qtimage;
	QOpenGLTexture *tmp;
#elif SDLAPI_==1 || WINAPI_==1
	unsigned int LoadImage(const ILstring path);
#endif
	void ShowWelcome(bool show);
	void LoadWelcome();//numbers
	void EnableTexture(Image_s im, bool third,bool alpha);
	int FindTexture(std::string name);
	int FindTexture(std::string name, std::vector<Image> v);
	int FindTexture(std::string name, std::vector<Image_s> vec);
	int LoadDrum(int iter);//numbers
	bool ShowDrum(int countdrums, int counttextureondrums, std::vector<std::string> drum,
		bool* buttons, int pressbutton,int *upbutton);
	void EnableTexture(int n, int m);//numbers
	void EnablePolygonFrontUp(float leftup, float leftdown);
	void EnablePolygonFrontMiddle(float leftup, float leftdown);
	void EnablePolygonFrontDown(float leftup, float leftdown);
	void EnablePolygonBackUp(float leftup, float leftdown);
	void EnablePolygonBackMiddle(float leftup, float leftdown);
	void EnablePolygonBackDown(float leftup, float leftdown);
	bool Rotate();
	void StartRotate(int *upbutoon);
	int LoadButtons(int iter);//numbers
	void ShowButtons();
	void EnableTextureButtons(int i);//numbers
	int LoadWords(int iter);//numbers
	void ShowNumbersAndWords(int credits,int win,int totalbet);
	void EnableTextureNumbersAndWords(int i,int win);//numbers
	void DrawNumbers(int number,int pos);//malloc free numbers
	void EnableTextureNumbers(int position, int numberword);
	int LoadBorder(int iter);//numbers
	void ShowBorder();
	void ShowHelp();//numbers
	void ShowLine(bool firstline,bool secondline, bool thirdline);//numbers
	int LoadNumbers(int iter);
	~Scene1();
	void LoadDrum(QOpenGLExtraFunctions* f);
	void ShowDrum(QOpenGLExtraFunctions* f, GLuint shaderProgram);
	void LoadBorder(QOpenGLExtraFunctions* f);
	void ShowBorder(QOpenGLExtraFunctions* f, GLuint shaderProgram);
	int err;
#ifndef _WIN32
	const char* strError;
#else
	wchar_t* strError;
#endif
	int width;
	int height;
	unsigned int type;
	unsigned char* copyData;
	static const int CountTexture = 58;
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
	std::vector<std::string>vectornumbersandwords;
	std::ofstream flogout;
	Coor* coor;
	std::vector<std::string>vectorram;
	std::vector<Image_s> welcomev;
	std::vector<Image_s>buttonsv;
	std::vector<Image_s>wordsv;
	std::vector<Image_s>borderhelpv;
	std::vector<Image> drumv;
	std::vector<Image> numbersv;
	int nnn;
	bool *changedrum;

	GLuint vao, id, id2;
	GLuint* indices;
	GLfloat rotate__;
	QOpenGLTexture* texture, * texture2,*texture3;
	QImage image1,image2;
	GLuint vao2, id3;
	GLuint buffer2, buffer;
	GLuint* indices_2;
	bool b;
};
