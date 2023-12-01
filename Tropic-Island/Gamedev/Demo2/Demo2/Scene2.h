
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
#include <vector>
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
struct Image_s2
{
	float Xleft;
	float Xright;
	float Yup;
	float Ydown;
	float Z;
#if SDLAPI_==1 || WINAPI_==1
	unsigned int IndexTexture;
#elif QTAPI_==1
	QOpenGLTexture* IndexTexture;
#endif
	std::string Name;
	int number;
	bool alpha;
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
	// ��������� ���� ������
	int err;
	// ��������� ������ � �������
#ifdef _WIN32
	wchar_t*strError;
#else
    const char*strError;
#endif
    // ������ �����������
	int width;
	// ������ �����������
	int height;
	// ��� �������� ������
	unsigned int type;
	// ������ ��������
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
	std::vector<Image_s2> scene2v;
	int FindTexture(std::string name, std::vector<Image_s2> vec);
	void EnableTexture(Image_s2 im, bool third, bool alpha);
};
#endif
