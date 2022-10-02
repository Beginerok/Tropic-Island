//#pragma once
#ifndef OGL
	#define OGL
#ifdef _WIN32
    #include <Window.h>
#endif // _WIN32
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#ifdef __unix__
    #include <cstring>
#endif
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"Glu32.lib")
#pragma comment(lib,"ILU.lib")
#pragma comment(lib,"DevIl.lib")
#pragma comment(lib,"SDL2.lib")
struct SimpleImage
{
	float** TextureCoordinats;
	float** VertexCoordinats;
	unsigned int* IndexTexture;
	std::string* Name;
	int* number;
};
class Loader
{
public:
	Loader(void);
	SimpleImage* LoadImage(const ILstring path,std::string path_);
	int FindTexture(std::string name);
	void LoadCoordFromFile();
	~Loader();
	int err;
#ifndef _WIN32
	char* strError;
#else
	wchar_t* strError;
#endif
	int width;
	int height;
	unsigned int type;
	unsigned char* copyData;
	static const int CountTexture = 57;
	SimpleImage* image;
	int CountIndexTexture;
	std::ofstream flogout;
};
#else
#endif
