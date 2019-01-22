
#ifndef Scene2_H
#define Scene2_H
#include "typedefs.h"
#ifdef _WINDOWS_
#include <IL\il.h>
#include <IL\ilu.h>
    #pragma comment(lib,"ILU.lib")
    #pragma comment(lib,"DevIl.lib")
#else
    #include <il.h>
    #include <ilu.h>
    #include <string.h>
#endif // _WINDOWS_
#include<string>
class Scene2
{
public:
    Scene2();
    void__ SetData();
	void__ ShowBackGround(bool__ *GetFA,int__ *random_,int__ GetCredits,int__ GetWin,int__ GetTotalBet);
	void__ EnableTexture(float__*texcoor, float__*vercoor);
	void__ EnableTexture(float__*texcoor, float__*vercoor,int__ dx);
	void__ LoadImage(const ILstring path);
	void__ ShowWelcome();
	void__ LoadWelcome();
	void__ Destroy();
	void__ DrawNumeric(int__ num,int__ position);
protected:
	float__**NewTextureCoordinats,**NewVertexCoordinats;
	// Получение кода ошибки
	int__ err;
	// Получение строки с ошибкой
#ifdef _WINDOWS_
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
	// Индекс текстуры
	uchar__*copyData;
	uint__ *IndexTexture;
	int__ CountIndexTexture;
	int__ CountTexture;
};
#endif
