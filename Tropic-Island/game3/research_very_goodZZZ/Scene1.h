#pragma once
#include "typedefs.h"
#ifdef _WINDOWS_2
#include <IL\il.h>
#include <IL\ilu.h>
    #pragma comment(lib,"ILU.lib")
    #pragma comment(lib,"DevIl.lib")
#else
    #include <il.h>
    #include <ilu.h>
    #include <string.h>
#endif // _WINDOWS_2
#include<string>
#include "Vector3.h"
#include "FileReader.h"
#include <vector>
#include <time.h>
#include <random>
//#include <chrono>
struct Image
{
	float__**TextureCoordinats;
	float__**VertexCoordinats;
	uint__*IndexTexture;
	std::string *Name;
	int__ *number;
};

/*ref*/ class Scene1
{
public:
	Scene1(void);
	void__ LoadImage(const ILstring path);
	void__ ShowWelcome(bool__ show);
	void__ LoadWelcome();
	void__ EnableTexture(float__*texcoor, float__*vercoor);
	int__ FindTexture(std::string name);
	void__ LoadDrum();
	void__ ShowDrum(int__ countdrums,float__*rotate_,int__ counttextureondrums,int__**drum,int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet,bool__*lines,int__**ms,bool__*buttons);
	void__ EnableTexture(int__ n,int__ m);
	void__ SetVerteces();
	void__ EnablePolygonFrontUp(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ EnablePolygonFrontMiddle(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ EnablePolygonFrontDown(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ EnablePolygonBackUp(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ EnablePolygonBackMiddle(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ EnablePolygonBackDown(float__ leftup,float__ leftdown,float__ rightdown,float__ rightup);
	void__ Rotate(/*bool__*buttons*/);
	void__ StartRotate();
	int__ GetRandom(int__ max);
	int__ *GetRandomMassive(int__ max);
	~Scene1();
	int__ err;
#ifdef _WINDOWS_2
	wchar_t*strError;
#else
    const char__*strError;
#endif
	 // Ширина изображения
	int__ width;
	// Высота изображения
	int__ height;
	// Тип хранения данных
	uint__ type;
	uchar__*copyData;
	static const int__ CountTexture = 30;
	Image *image;
	int__ CountIndexTexture;
	int__ AnimateBar;
	std::string NameAnimateBar;
	
    std::vector<Vector3>listv;
    std::vector<Vector3>listt;
	float__ xl,xr,yd,yu,z;
	float__*rotate;
	bool__*startrotate;
	static const int__ CountDrum = 5;
	std::vector<std::string>vectordrum;

/*	volatile */int__ random,*randommassive;
	int__ max_,min_;
	bool__ start;

};

