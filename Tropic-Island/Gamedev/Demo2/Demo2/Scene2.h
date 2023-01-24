
#ifndef Scene2_H
#define Scene2_H
#define QTAPI_ 1
#define SDLAPI_ 0
#define WINAPI_ 0
#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#if SDLAPI_==1 || WINAPI_==1
	#include <IL\il.h>
	#include <IL\ilu.h>
    #pragma comment(lib,"ILU.lib")
    #pragma comment(lib,"DevIl.lib")
#endif
#endif
#if __unix__ && SDLAPI_==1
    #include <il.h>
    #include <ilu.h>
    #include <string.h>
#elif QTAPI_==1
	#include <QtWidgets/QtWidgets>
	#ifdef Q_OS_LINUX
		#include <QtGui/qopengltexture.h>
	#endif
	#ifdef Q_OS_WIN
		#include <QtOpenGL/qopengltexture.h>
	#endif
#endif

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>
struct Image2
{
	float** VertexCoordinats;
#if SDLAPI_==1 || WINAPI_==1
	unsigned int* IndexTexture;
#elif QTAPI_==1
	QOpenGLTexture* IndexTexture;
#endif
	std::string Name;
	int* number;
};
class Scene2
{
public:
    Scene2();
    void SetData();
	void ShowBackGround(bool *GetFA,int *random_,int GetCredits,int GetWin,int GetTotalBet);
	void EnableTexture(float*texcoor, float*vercoor);
	void EnableTexture(float*texcoor, float*vercoor,int dx);
#if QTAPI_==1
	QOpenGLTexture* QTLoadImage(QString path);
	QImage qtimage;
	QOpenGLTexture* tmp;
	void LoadQT();
#elif SDLAPI_==1 || WINAPI_==1
	void LoadImage(const ILstring path);
#endif
	void Destroy();
	void DrawNumeric(int num,int position);
protected:
	float**NewTextureCoordinats,**NewVertexCoordinats;
	// Получение кода ошибки
	int err;
	// Получение строки с ошибкой
#ifdef _WIN32
	wchar_t*strError;
#else
    const char*strError;
#endif
    // Ширина изображения
	int width;
	// Высота изображения
	int height;
	// Тип хранения данных
	unsigned int type;
	// Индекс текстуры
	unsigned char*copyData;

#if SDLAPI_==1 || WINAPI_==1
	unsigned int *IndexTexture;
#elif QTAPI_==1
	QOpenGLTexture *IndexTexture;
#endif
	int CountIndexTexture;
	int CountTexture;
	char*num_;
	bool loading;	
	Image2* image;
};
#endif
