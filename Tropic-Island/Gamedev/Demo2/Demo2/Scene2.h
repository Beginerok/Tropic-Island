
#ifndef Scene2_H
#define Scene2_H
#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL\il.h>
#include <IL\ilu.h>
    #pragma comment(lib,"ILU.lib")
    #pragma comment(lib,"DevIl.lib")
#else
    #include <il.h>
    #include <ilu.h>
    #include <string.h>
#endif
#include <string>
#include <iostream>
class Scene2
{
public:
    Scene2();
    void SetData();
	void ShowBackGround(bool *GetFA,int *random_,int GetCredits,int GetWin,int GetTotalBet);
	void EnableTexture(float*texcoor, float*vercoor);
	void EnableTexture(float*texcoor, float*vercoor,int dx);
	void LoadImage(const ILstring path);
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
	unsigned int *IndexTexture;
	int CountIndexTexture;
	int CountTexture;
	char*num_;
	bool loading;
};
#endif
