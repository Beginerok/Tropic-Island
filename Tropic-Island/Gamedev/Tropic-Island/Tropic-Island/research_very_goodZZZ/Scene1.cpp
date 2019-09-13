#include "Scene1.h"

Scene1::Scene1(void)
{
	image = new Image[CountTexture];
	image->TextureCoordinats = new float__*[CountTexture];
	image->VertexCoordinats = new float__*[CountTexture];
	image->Name = new std::string[CountTexture];
	for(int__ i=0;i<CountTexture;i++)
	{
		image->TextureCoordinats[i]=new float__[4];
		image->VertexCoordinats[i]=new float__[4];
		image->Name[i] = "";
	}
	image->IndexTexture = new uint__[CountTexture/*1*/];//02.03.2019
	image->number = new int__[CountTexture];
	CountIndexTexture = 0;
	AnimateBar = 0;
	rotate = new float__[CountDrum];
	startrotate = new bool__[CountDrum];
	for(int__ i=0;i<CountDrum;i++){
		rotate[i] = 0.0f;
		startrotate[i] = false;
	}
	randommassive = new int__[30];
	
}
#include <iostream>
void__ Scene1::LoadImage(const ILstring path)
{
	ILenum ext;
	if(strstr(reinterpret_cast<const char*>(path),"png"))
		ext=IL_PNG;
	if(strstr(reinterpret_cast<const char*>(path),"jpg") || strstr(reinterpret_cast<const char*>(path),"jpeg"))
		ext=IL_JPG;
	if(strstr(reinterpret_cast<const char*>(path),"bmp"))
		ext=IL_BMP;
	ilLoad( ext, reinterpret_cast<const ILstring>(path));
	// Получение кода ошибки
	err = ilGetError();
	// Если код не равен нулю ошибка была
	if (err != IL_NO_ERROR) {
	// Получение строки с ошибкой
    strError = iluErrorString(err);
        // Выдаем сообщение об ошибке
    #ifdef _WINDOWS_2

	std::cout << "\nNot find file: ";
	std::wcout << path << std::endl;
        MessageBox(NULL, NULL, L"Ошибка при загрузке il!", MB_OK);
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
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	
	CountIndexTexture++;
};
void__ Scene1::LoadWelcome()
{
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//welcome.jpg"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\welcome.jpg"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "welcome";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;



#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//logo.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\logo.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .8f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.8f;
	image->VertexCoordinats[CountIndexTexture-1][2] = .8f;
	image->VertexCoordinats[CountIndexTexture-1][3] = .4f;
	
	image->Name[CountIndexTexture-1] = "logo";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

	
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar0.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar0.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar0";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar1.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar1.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar1";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar2.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar2.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar2";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar3.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar3.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar3";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

	
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar4.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar4.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar4";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar5.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar5.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar5";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar6.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar6.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar6";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar7.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar7.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar7";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar8.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar8.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar8";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar9.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar9.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar9";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

		
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//progress//bar10.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\progress\\bar10.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = .4f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][2] = -.4f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -.8f;
	
	image->Name[CountIndexTexture-1] = "bar10";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;

}
#include <sstream>
void__ Scene1::ShowWelcome(bool__ show)
{
	if(!show)
		return;
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.0f); 
	int__ numb = FindTexture("welcome");
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
	EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);
	

	numb = FindTexture("logo");
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
	EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);
	
	if(AnimateBar>10)
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
void__ Scene1::EnableTexture(float__*texcoor, float__*vercoor)
{
    glBegin(GL_QUADS);
    glTexCoord2f(texcoor[0],texcoor[2]);
    glVertex2f(vercoor[0],vercoor[2]);
    glTexCoord2f(texcoor[1],texcoor[2]);
    glVertex2f(vercoor[1],vercoor[2]);
    glTexCoord2f(texcoor[1],texcoor[3]);
    glVertex2f(vercoor[1],vercoor[3]);
    glTexCoord2f(texcoor[0],texcoor[3]);
    glVertex2f(vercoor[0],vercoor[3]);
    glEnd();
}
int__ Scene1::FindTexture(std::string name)
{
	int__ result = -1;
	for(int__ i=0;i<CountTexture;i++)
	{
		if (strcmp(image->Name[i].c_str(), name.c_str()) == 0)
		{
			/*
		int__ bb=0;
		for(int__ j=0;j<name.length() && j<image->Name[i].length();j++)
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
void__ Scene1::LoadDrum()
{
	vectordrum.push_back("auto1");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto1.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto1.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto1";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto2");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto2.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto2.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto2";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto3");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto3.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto3.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto3";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto4");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto4.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto4.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto4";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto5");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto5.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto5.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto5";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto6");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto6.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto6.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto6";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto7");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto7.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto7.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto7";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto8");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto8.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto8.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto8";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto9");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto9.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto9.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto9";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto10");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto10.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto10.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto10";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto11");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto11.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto11.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto11";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto12");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto12.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto12.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto12";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto13");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto13.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto13.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto13";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto14");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto14.jpg"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto14.jpg"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto14";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("auto15");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//auto15.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\auto15.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "auto15";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("moto");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//moto.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\moto.png"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "moto";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	vectordrum.push_back("wild");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//drum//wild.jpg"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\drum\\wild.jpg"));
#endif
	image->TextureCoordinats[CountIndexTexture-1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture-1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture-1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture-1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture-1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture-1][3] = -1.f;
	
	image->Name[CountIndexTexture-1] = "wild";
	image->number[CountIndexTexture-1] = CountIndexTexture-1;
	
	max_ = vectordrum.size()-1, min_ = 0;
	for(int__ i=0;i<30;i++)
	{
		randommassive[i] = GetRandom();
	}
}
void__ Scene1::ShowDrum(int__ countdrums,float__*rotate_,int__ counttextureondrums,int__**drum,
	int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet,bool__*lines,int__**ms,bool__*buttons)
{
	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.0f); 
	/*
	int__ numb = FindTexture("wild");
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numb]);
	EnableTexture(image->TextureCoordinats[numb], image->VertexCoordinats[numb]);
	*/
	//glPushMatrix();
    //glRotatef(180,0,0,1);
	if(buttons[2]){
		//start = false;
		StartRotate();
	}
	Rotate(/*startrotate*/);
	/*
	std::default_random_engine generator;
	 std::uniform_int_distribution<int>distribution(0, INT_MAX);
	*/
	for(int__ i=0;i<countdrums;i++)
    {
        glPushMatrix();
        glRotatef(rotate[i],1,0,0);
		for(int__ j=0;j<counttextureondrums;j++)
        {
			//random = GetRandom(max_);
			glBindTexture(GL_TEXTURE_2D,image->IndexTexture[FindTexture(vectordrum[GetMassive(i*j+j)/*randommassive[i*j+j]*/])]);
			EnableTexture(i,j);
        }
        glPopMatrix();
    }
    //glPopMatrix();
	//glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
}

int__ Scene1::GetMassive(int__ number)
{
	return randommassive[number];
}
void__ Scene1::SetMassive(int__ number, int__ value)
{
	randommassive[number] = value;
}

int__ Scene1::GetRandom()
{
	return ((int__)((float__)rand() / RAND_MAX*(max_ - min_) + min_));
	/*
	static default_random_engine gen;
    static uniform_int_distribution<int> dist;
    return dist(gen) % max;
	*/
}
//#include <iostream>
int__*Scene1::GetRandomMassive()
{
	for(int__ i=0;i<30;i++)
	{
		//randommassive[i] = GetRandom();
		//std::cout<<randommassive[i]<<"|";
	}
	
	SetMassive(0,min_+1);//GetRandom(max);
	SetMassive(1,max_);//GetRandom(max);
	SetMassive(2,max_);//GetRandom(max);
	SetMassive(3,max_);//GetRandom(max);
	SetMassive(4,max_);//GetRandom(max);
	SetMassive(5,min_);//GetRandom(max);
	SetMassive(6, max_);//GetRandom(max);
	SetMassive(7, max_);//GetRandom(max);
	SetMassive(8,max_);//GetRandom(max);
	SetMassive(9,max_);//GetRandom(max);
	SetMassive(10,max_);//GetRandom(max);
	SetMassive(11,max_);//GetRandom(max);
	SetMassive(12,max_);//GetRandom(max);
	SetMassive(13,max_);//GetRandom(max);
	SetMassive(14,max_);//GetRandom(max);
	SetMassive(15,min_);//GetRandom(max);
	SetMassive(16,max_);//GetRandom(max);
	SetMassive(17,max_);//GetRandom(max);
	SetMassive(18,max_);//GetRandom(max);
	SetMassive(19,max_);//GetRandom(max);
	SetMassive(20,min_);//GetRandom(max);
	SetMassive(21,max_);//GetRandom(max);
	SetMassive(22,max_);//GetRandom(max);
	SetMassive(23,max_);//GetRandom(max);
	SetMassive(24,max_);//GetRandom(max);
	SetMassive(25,min_);//GetRandom(max);
	SetMassive(26,max_);//GetRandom(max);
	SetMassive(27,max_);//GetRandom(max);
	SetMassive(28,max_);//GetRandom(max);
	SetMassive(29,max_);//GetRandom(max);
	
							//std::cout<<std::endl;
	return randommassive;
}
void__ Scene1::EnablePolygonFrontUp(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,yup,0.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,ydown,1.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,ydown,1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,yup,0.0f);

	glEnd();
	
}
void__ Scene1::EnablePolygonFrontMiddle(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,yup,1.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,ydown,1.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,ydown,1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,yup,1.0f);

	glEnd();
}
void__ Scene1::EnablePolygonFrontDown(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,yup,1.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,ydown,0.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,ydown,0.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,yup,1.0f);

	glEnd();
}
void__ Scene1::EnablePolygonBackUp(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,ydown,-1.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,yup,0.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,yup,0.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,ydown,-1.0f);

	glEnd();
}
void__ Scene1::EnablePolygonBackMiddle(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,ydown,-1.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,yup,-1.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,yup,-1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,ydown,-1.0f);

	glEnd();
}
void__ Scene1::EnablePolygonBackDown(float__ xleft,float__ xright,float__ ydown,float__ yup)
{
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f(xleft,ydown,0.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f(xleft,yup,-1.0f);
	
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(xright,yup,-1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(xright,ydown,0.0f);

	glEnd();
}
void__ Scene1::EnableTexture(int__ n,int__ m)
{
	
	//front up
	xl = -0.8f;
	xr = -0.48f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonFrontUp(xl,xr,yd,yu);

	xl = -0.48f;
	xr = -0.16f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonFrontUp(xl,xr,yd,yu);

	xl = -0.16f;
	xr = 0.16f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonFrontUp(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonFrontUp(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonFrontUp(xl,xr,yd,yu);
	//front up

	//front middle
	xl = -0.8f;
	xr = -0.48f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonFrontMiddle(xl,xr,yd,yu);
	
	xl = -0.48f;
	xr = -0.16f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonFrontMiddle(xl,xr,yd,yu);
	
	xl = -0.16f;
	xr = 0.16f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonFrontMiddle(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonFrontMiddle(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonFrontMiddle(xl,xr,yd,yu);
	
	//front middle

	//front down
	xl = -0.8f;
	xr = -0.48f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonFrontDown(xl,xr,yd,yu);
	
	xl = -0.48f;
	xr = -0.16f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonFrontDown(xl,xr,yd,yu);
	
	xl = -0.16f;
	xr = 0.16f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonFrontDown(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonFrontDown(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonFrontDown(xl,xr,yd,yu);

	//front down
	
	//back up
	xl = -0.8f;
	xr = -0.48f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonBackUp(xl,xr,yd,yu);

	xl = -0.48f;
	xr = -0.16f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonBackUp(xl,xr,yd,yu);

	xl = -0.16f;
	xr = 0.16f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonBackUp(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonBackUp(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = 0.3f;
	yu = 0.9;
	EnablePolygonBackUp(xl,xr,yd,yu);
	//back up

	
	//back middle
	xl = -0.8f;
	xr = -0.48f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonBackMiddle(xl,xr,yd,yu);
	
	xl = -0.48f;
	xr = -0.16f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonBackMiddle(xl,xr,yd,yu);
	
	xl = -0.16f;
	xr = 0.16f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonBackMiddle(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonBackMiddle(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = -0.3f;
	yu = 0.3;
	EnablePolygonBackMiddle(xl,xr,yd,yu);
	
	//back middle
	
	//back down
	xl = -0.8f;
	xr = -0.48f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonBackDown(xl,xr,yd,yu);
	
	xl = -0.48f;
	xr = -0.16f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonBackDown(xl,xr,yd,yu);
	
	xl = -0.16f;
	xr = 0.16f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonBackDown(xl,xr,yd,yu);
	
	xl = 0.16f;
	xr = 0.48f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonBackDown(xl,xr,yd,yu);
	
	xl = 0.48f;
	xr = 0.8f;
	yd = -0.9f;
	yu = -0.3;
	EnablePolygonBackDown(xl,xr,yd,yu);

	//back down
	/*
    float__ _width_=0.188f;
    int__ k=5-n*2;
    switch (m)
    {
        case 0:
        {
            glBegin(GL_POLYGON);
            for(int__ i=1,j=3;i<10;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=9,j=11;i>0;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 1:
        {
            glBegin(GL_POLYGON);
            for(int__ i=9,j=3;i<18;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=17,j=11;i>8;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 2:
        {
            glBegin(GL_POLYGON);
            for(int__ i=17,j=0;i<20;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=19,j=2;i>16;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 3:
        {
            glBegin(GL_POLYGON);
            for(int__ i=19,j=3;i<28;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=27,j=11;i>18;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 4:
        {
            glBegin(GL_POLYGON);
            for(int__ i=27,j=3;i<36;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=35,j=11;i>26;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 5:
        {
            glBegin(GL_POLYGON);
            for(int__ i=35,j=0;i<(int__)listv.size();i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=(int__)listv.size()-1,j=2;i>34;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
    }
	*/
}
void__ Scene1::Rotate(/*bool__*buttons*/)
{
	for(int__ i=0;i<CountDrum;i++)
	{
		if(/*buttons[2]*/startrotate[i])
		{
			if(rotate[i]<360.0f)
				rotate[i]+=5.0f;
			else
				startrotate[i] = false;
		}
	}
}
void__ Scene1::StartRotate()
{	
	for(int__ i=0;i<CountDrum;i++)
	{
		if(startrotate[i])
			continue;
		startrotate[i] = true;
		rotate[i] = 0.0f;
		srand(time(0));
		GetRandomMassive();
	}
}
Scene1::~Scene1()
{
	for(int__ i=0;i<CountTexture;i++)
        delete[] image->TextureCoordinats[i];
    delete[] image->TextureCoordinats;
    for(int__ i=0;i<CountTexture;i++)
        delete[] image->VertexCoordinats[i];
    for(int__ i=0;i<CountTexture;i++)
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