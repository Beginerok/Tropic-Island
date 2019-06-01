#include "Scene1.h"

Scene1::Scene1(void)
{
	image = new Image[CountTexture];
	image->TextureCoordinats = new float*[CountTexture];
	image->VertexCoordinats = new float*[CountTexture];
	image->Name = new std::string[CountTexture];
	for (int i = 0; i<CountTexture; i++)
	{
		image->TextureCoordinats[i] = new float[4];
		image->VertexCoordinats[i] = new float[4];
		image->Name[i] = "";
	}
	image->IndexTexture = new unsigned int[CountTexture];//02.03.2019
	image->number = new int[CountTexture];
	CountIndexTexture = 0;
	AnimateBar = 0;
	rotate = new float[CountDrum];
	startrotate = new bool[CountDrum];
	for (int i = 0; i<CountDrum; i++) {
		rotate[i] = 0.0f;
		startrotate[i] = false;
	}
	randommassive = new int[30];
}
void Scene1::LoadImage(const ILstring path)
{
	ILenum ext;
	if (strstr(reinterpret_cast<const char*>(path), "png"))
		ext = IL_PNG;
	if (strstr(reinterpret_cast<const char*>(path), "jpg") || strstr(reinterpret_cast<const char*>(path), "jpeg"))
		ext = IL_JPG;
	if (strstr(reinterpret_cast<const char*>(path), "bmp"))
		ext = IL_BMP;
	ilLoad(ext, reinterpret_cast<const ILstring>(path));
	// Получение кода ошибки
	err = ilGetError();
	// Если код не равен нулю ошибка была
	if (err != IL_NO_ERROR) {
		// Получение строки с ошибкой
		strError = (wchar_t *)iluErrorString(err);
		// Выдаем сообщение об ошибке
#ifdef _WINDOWS_2
		MessageBox(NULL, NULL, "Ошибка при загрузке il!", MB_OK);
#endif
		// выход из программы
		exit(EXIT_FAILURE);
	}
	// Ширина изображения
	width = ilGetInteger(IL_IMAGE_WIDTH);
	// Высота изображения
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	// Число байт на пиксель
	//int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	// Тип хранения данных
	type = ilGetInteger(IL_IMAGE_FORMAT);
	/*
	unsigned int type;
	// переопределить тип для OpenGL
	switch (bpp) {
	case 1:
	type  = GL_RGB8;
	break;
	case 3:
	type = GL_RGB;
	break;
	case 4:
	type = GL_RGBA;
	break;
	}
	*/
	// Индекс текстуры
	copyData = ilGetData();
	image->IndexTexture[CountIndexTexture] = 0;
	glGenTextures(1, &image->IndexTexture[CountIndexTexture]);
	iluFlipImage();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[CountIndexTexture]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);

	CountIndexTexture++;
};
void Scene1::LoadWelcome()
{
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//welcome.jpg"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\welcome.jpg"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "welcome";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;



#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//logo.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\logo.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .8f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.8f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = .8f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = .4f;

	image->Name[CountIndexTexture - 1] = "logo";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar0.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar0.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar0";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar1.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar1.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar1";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar2.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar2.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar2";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar3.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar3.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar3";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar4.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar4.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar4";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar5.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar5.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar5";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar6.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar6.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar6";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar7.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar7.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar7";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar8.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar8.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar8";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar9.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar9.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar9";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar10.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar10.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -.8f;

	image->Name[CountIndexTexture - 1] = "bar10";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

}
#include <sstream>
void Scene1::ShowWelcome(bool show)
{
	if (!show)
		return;
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.0f); 
	int numb = FindTexture("welcome");
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
	EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);


	numb = FindTexture("logo");
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
	EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);

	if (AnimateBar>10)
		AnimateBar = 0;
	NameAnimateBar = "bar";

	std::stringstream out;
	out << AnimateBar;
	NameAnimateBar += out.str();
	{
		numb = FindTexture(NameAnimateBar);
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
		EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);
	}
	NameAnimateBar.clear();
	AnimateBar++;
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void Scene1::EnableTexture(float*texcoor, float*vercoor)
{
	glBegin(GL_QUADS);
	glTexCoord2f(texcoor[0], texcoor[2]);
	glVertex2f(vercoor[0], vercoor[2]);
	glTexCoord2f(texcoor[1], texcoor[2]);
	glVertex2f(vercoor[1], vercoor[2]);
	glTexCoord2f(texcoor[1], texcoor[3]);
	glVertex2f(vercoor[1], vercoor[3]);
	glTexCoord2f(texcoor[0], texcoor[3]);
	glVertex2f(vercoor[0], vercoor[3]);
	glEnd();
}
int Scene1::FindTexture(std::string name)
{
	int result = -1;
	for (int i = 0; i<CountTexture; i++)
	{
		if (strcmp(image->Name[i].c_str(), name.c_str()) == 0)
		{
			/*
			int bb=0;
			for(int j=0;j<name.length() && j<image->Name[i].length();j++)
			{
			if(name[j] == image->Name[i][j])
			bb++;
			}
			if(name.length() == image->Name[i].length() && bb == name.length())
			*/
			result = image->number[i];
			//break;
		}
	}
	return result;
}
int Scene1::LoadDrum(int iter)
{
	if (iter == 0)
	{
		vectordrum.push_back("auto1");//1
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto1.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto1.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto1";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 1)
	{
		vectordrum.push_back("auto2");//2
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto2.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto2.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto2";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 2)
	{

		vectordrum.push_back("auto3");//3
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto3.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto3.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto3";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 3)
	{
		vectordrum.push_back("auto4");//4
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto4.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto4.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto4";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 4)
	{
		vectordrum.push_back("auto5");//5
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto5.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto5.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto5";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 5)
	{
		vectordrum.push_back("auto6");//6
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto6.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto6.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto6";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 6)
	{
		vectordrum.push_back("auto7");//7
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto7.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto7.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto7";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 7)
	{
		vectordrum.push_back("auto8");//8
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto8.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto8.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto8";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 8)
	{
		vectordrum.push_back("auto9");//9
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto9.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto9.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto9";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 9)
	{
		vectordrum.push_back("auto10");//10
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto10.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto10.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto10";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 10)
	{
		vectordrum.push_back("auto11");//11
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto11.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto11.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto11";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 11)
	{
		vectordrum.push_back("auto12");//12
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto12.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto12.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto12";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 12)
	{
		vectordrum.push_back("auto13");//13
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto13.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto13.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto13";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 13)
	{
		vectordrum.push_back("auto14");//14
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto14.jpg"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto14.jpg"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto14";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 14)
	{
		vectordrum.push_back("auto15");//15
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto15.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto15.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto15";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 15)
	{
		vectordrum.push_back("moto");//16
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//moto.png"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\moto.png"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "moto";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 16)
	{
		vectordrum.push_back("wild");//17
#ifndef _WINDOWS_2
		LoadImage(reinterpret_cast<const ILstring>("content//drum//wild.jpg"));
#else
		LoadImage(reinterpret_cast<const ILstring>("content\\drum\\wild.jpg"));
#endif
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "wild";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

		max_ = vectordrum.size() - 1, min_ = 0;
		srand(time(NULL));
		for (int i = 0; i < 30; i++)
		{
			SetMassive(i, GetRandom());
		}
		GetRandomMassive();
	}
	if (iter > 15)
		return 0;
	else
		return 1;
}
void Scene1::ShowDrum(int countdrums,/* float*rotate_,*/ int counttextureondrums/*, int**drum,
	int credits, int win, int totalbet, const char*line, int bet, bool*lines, int**ms*/, bool*buttons)
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f); 
	//29.03.2019
	if (buttons[2]) {
		start = false;
		StartRotate();
	}
	Rotate();
	int k = -1;
	for (int i = 0; i<countdrums; i++)
	{
		glPushMatrix();
		glRotatef(rotate[i], 1, 0, 0);
		for (int j = 0; j<counttextureondrums; j++)
		{
			glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(vectordrum[GetMassive(++k)])]);
			EnableTexture(i, j);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

int Scene1::GetMassive(int number)
{
	return randommassive[number];
}
void Scene1::SetMassive(int number, int value)
{
	randommassive[number] = value;
}

void Scene1::LoadButtons()
{
	vectorbuttons.push_back("HELP");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//HELP.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\HELP.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "HELP";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("TAKE");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\TAKE.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "TAKE";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("PLAY");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//PLAY.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\PLAY.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "PLAY";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("FLIP");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\FLIP.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "FLIP";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("EXIT");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//EXIT.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\EXIT.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "EXIT";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("HELP_PRESS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//HELP_PRESS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\HELP_PRESS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "HELP_PRESS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("TAKE_PRESS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE_PRESS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\TAKE_PRESS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "TAKE_PRESS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("PLAY_PRESS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//PLAY_PRESS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\PLAY_PRESS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "PLAY_PRESS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorbuttons.push_back("FLIP_PRESS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP_PRESS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\FLIP_PRESS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "FLIP_PRESS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;


	vectorbuttons.push_back("EXIT_PRESS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//EXIT_PRESS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\EXIT_PRESS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "EXIT_PRESS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

}
void Scene1::ShowButtons()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f); 
	for (int i = 0; i < vectorbuttons.size()/2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(vectorbuttons[i])]);
		EnableTextureButtons(i);
	}
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void Scene1::EnableTextureButtons(int i)
{
	if (i == 0)
	{
		glBegin(GL_POLYGON);//HELP

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.45f, -.6f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-.45f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.65f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.65f, -.6f, 0.0f);

		glEnd();//HELP
	}
	if (i == 1)
	{
		glBegin(GL_POLYGON);//TAKE

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.15f, -.6f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-.15f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.35f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.35f, -.6f, 0.0f);

		glEnd();//TAKE
	}
	if (i == 2)
	{
		glBegin(GL_POLYGON);//PLAY

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.15f, -.6f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.15f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.05f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.05f, -.6f, 0.0f);

		glEnd();//PLAY
	}
	if (i == 3)
	{
		glBegin(GL_POLYGON);//FLIP

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.45f, -.6f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.45f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.25f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.25f, -.6f, 0.0f);

		glEnd();//FLIP
	}
	if (i == 4)
	{
		glBegin(GL_POLYGON);//EXIT

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.75f, -.6f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.75f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.55f, -.8f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.55f, -.6f, 0.0f);

		glEnd();//EXIT
	}
}
int Scene1::GetRandom()
{
	return ((int)((float)rand() / RAND_MAX*(max_ - min_) + min_));
}
int*Scene1::GetRandomMassive()
{
	for (int i = 0; i<30; i++)
	{
		randommassive[i] = GetRandom();
		//std::cout<<randommassive[i]<<"|";
	}
	/*
	SetMassive(0, min_);//GetRandom(max);
	SetMassive(1, min_);//GetRandom(max);
	SetMassive(2, min_);//GetRandom(max);
	SetMassive(3, min_);//GetRandom(max);
	SetMassive(4, min_);//GetRandom(max);
	SetMassive(5, max_);//GetRandom(max);
	SetMassive(6, max_);//GetRandom(max);
	SetMassive(7, max_);//GetRandom(max);
	SetMassive(8, max_);//GetRandom(max);
	SetMassive(9, max_);//GetRandom(max);
	SetMassive(10, max_);//GetRandom(max);
	SetMassive(11, max_);//GetRandom(max);
	SetMassive(12, max_);//GetRandom(max);
	SetMassive(13, max_);//GetRandom(max);
	SetMassive(14, max_);//GetRandom(max);
	SetMassive(15, max_);//GetRandom(max);
	SetMassive(16, max_);//GetRandom(max);
	SetMassive(17, max_);//GetRandom(max);
	SetMassive(18, max_);//GetRandom(max);
	SetMassive(19, max_);//GetRandom(max);
	SetMassive(20, max_);//GetRandom(max);
	SetMassive(21, max_);//GetRandom(max);
	SetMassive(22, max_);//GetRandom(max);
	SetMassive(23, max_);//GetRandom(max);
	SetMassive(24, max_);//GetRandom(max);
	SetMassive(25, max_);//GetRandom(max);
	SetMassive(26, max_);//GetRandom(max);
	SetMassive(27, max_);//GetRandom(max);
	SetMassive(28, max_);//GetRandom(max);
	SetMassive(29, max_);//GetRandom(max);
	*/
	//std::cout<<std::endl;
	return randommassive;
}
void Scene1::EnablePolygonFrontUp(float xleft, float xright, float ydown, float yup)
{

	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, yup, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, ydown, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, ydown, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, yup, 0.0f);

	glEnd();

}
void Scene1::EnablePolygonFrontMiddle(float xleft, float xright, float ydown, float yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, yup, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, ydown, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, ydown, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, yup, 1.0f);

	glEnd();
}
void Scene1::EnablePolygonFrontDown(float xleft, float xright, float ydown, float yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, yup, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, ydown, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, ydown, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, yup, 1.0f);

	glEnd();
}
void Scene1::EnablePolygonBackUp(float xleft, float xright, float ydown, float yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, ydown, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, yup, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, yup, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, ydown, -1.0f);

	glEnd();
}
void Scene1::EnablePolygonBackMiddle(float xleft, float xright, float ydown, float yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, ydown, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, yup, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, yup, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, ydown, -1.0f);

	glEnd();
}
void Scene1::EnablePolygonBackDown(float xleft, float xright, float ydown, float yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xleft, ydown, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xleft, yup, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xright, yup, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xright, ydown, 0.0f);

	glEnd();
}
void Scene1::EnableTexture(int n, int m)
{
    if(n == 0)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
    }
	//front up

	//front middle
    if(n == 1)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
    }
	//front middle

	//front down
    if(n == 2)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
    }
	//front down

	//back up
    if(n == 3)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
    }
	//back up

	//back middle
    if(n == 4)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
    }
	//back middle

	//back down
    if(n == 5)
    {
        if(m == 0){
        xl = -0.8f;
        xr = -0.48f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonBackDown(xl, xr, yd, yu);
        }
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonBackDown(xl, xr, yd, yu);
        }
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonBackDown(xl, xr, yd, yu);
        }
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonBackDown(xl, xr, yd, yu);
        };
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonBackDown(xl, xr, yd, yu);
        }
    }
	//back down
}
void Scene1::Rotate()
{
	for (int i = 0; i<CountDrum; i++)
	{
		if (startrotate[i])
		{
			if (rotate[i]<360.0f)
				rotate[i] += 5.0f;
			else
				startrotate[i] = false;
		}
	}
}
void Scene1::StartRotate()
{
	for (int i = 0; i<CountDrum; i++)
	{
		if (startrotate[i])
			continue;
		startrotate[i] = true;
		rotate[i] = 0.0f;
		srand(time(0));
		GetRandomMassive();
	}
}
Scene1::~Scene1()
{
	for (int i = 0; i<CountTexture; i++)
		delete[] image->TextureCoordinats[i];
	delete[] image->TextureCoordinats;
	for (int i = 0; i<CountTexture; i++)
		delete[] image->VertexCoordinats[i];
	for (int i = 0; i<CountTexture; i++)
		image->Name[i].clear();
	delete[] image->VertexCoordinats;
	delete image->IndexTexture;
	delete image->Name;
	delete image->number;
	delete image;
	delete rotate;
	delete startrotate;
	delete randommassive;
}
