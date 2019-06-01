
#ifndef Scene2_H
#define Scene2_H
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
class Scene2
{
public:
    Scene2();
    void__ SetData();
	void__ ShowBackGround(bool__ *GetFA,int__ *random_,int__ GetCredits,int__ GetWin,int__ GetTotalBet);
	void__ EnableTexture(float__*texcoor, float__*vercoor);
	void__ EnableTexture(float__*texcoor, float__*vercoor,int__ dx);
	void__ LoadImage(const ILstring path);
	void__ Destroy();
	void__ DrawNumeric(int__ num,int__ position);
protected:
	float__**NewTextureCoordinats,**NewVertexCoordinats;
	// ��������� ���� ������
	int__ err;
	// ��������� ������ � �������
#ifdef _WINDOWS_2
	wchar_t*strError;
#else
    const char__*strError;
#endif
    // ������ �����������
	int__ width;
	// ������ �����������
	int__ height;
	// ��� �������� ������
	uint__ type;
	// ������ ��������
	uchar__*copyData;
	uint__ *IndexTexture;
	int__ CountIndexTexture;
	int__ CountTexture;
	char__*num_;
	bool__ loading;
};
#endif
