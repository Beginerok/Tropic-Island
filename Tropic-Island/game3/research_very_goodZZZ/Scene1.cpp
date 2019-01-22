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
	image->IndexTexture = new uint__[1];
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
		if(strcmp(image->Name[i].c_str(),name.c_str())==0)
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
		randommassive[i] = GetRandom(max_);
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
			glBindTexture(GL_TEXTURE_2D,image->IndexTexture[FindTexture(vectordrum[randommassive[i*j+j]])]);
			EnableTexture(i,j);
        }
        glPopMatrix();
    }
    //glPopMatrix();
	//glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
}
int__ Scene1::GetRandom(int max)
{
	return ((int__)((float__)rand() / RAND_MAX*(max_ - min_) + min_));
	/*
	static default_random_engine gen;
    static uniform_int_distribution<int> dist;
    return dist(gen) % max;
	*/
}
int__*Scene1::GetRandomMassive(int max)
{
	for(int__ i=0;i<30;i++)
	{
		randommassive[i] = GetRandom(max);
		//std::cout<<randommassive[i]<<"|";
	}
	//std::cout<<std::endl;
	return randommassive;
}
void__ Scene1::SetVerteces()
{
    FileReader*filereader=new FileReader();
    filereader->FileReader__("tre.xml","r");
    Vector3*vec=new Vector3();
    filereader->GetStroke();
    int__ count_=0;
    while(filereader->Opened())
    {
        vec->a[0]=filereader->BConvert(2);
        vec->a[1]=filereader->BConvert(1);
        vec->a[2]=filereader->BConvert(0);
        count_++;
        listv.push_back((*vec));
        filereader->GetStroke();
    }
    filereader->~FileReader();
	float__**texturecoordinats = new float__*[1];
	texturecoordinats[0] = new float__[4];
    texturecoordinats[0][0]=1.0f;
    texturecoordinats[0][1]=0.0f;
    texturecoordinats[0][2]=1.0f;
    texturecoordinats[0][3]=0.0f;
    vec->a[0]=texturecoordinats[0][0];
    vec->a[1]=texturecoordinats[0][1];
    int__ n=3;
    for(int__ i=0;i<n;i++)
    {
        vec->a[2]=texturecoordinats[0][3]+(texturecoordinats[0][2]-texturecoordinats[0][3])*i/(n-1);
        listt.push_back((*vec));
    }
    n=9;
    for(int__ i=0;i<n;i++)
    {
        vec->a[2]=texturecoordinats[0][3]+(texturecoordinats[0][2]-texturecoordinats[0][3])*i/(n-1);
        listt.push_back((*vec));
    }
	delete vec;
	delete texturecoordinats[0];
	delete texturecoordinats;
	/*
    vertexcoordinats[0][0]=1.f;
    vertexcoordinats[0][1]=-1.0f;
    vertexcoordinats[0][2]=1.f;
    vertexcoordinats[0][3]=-1.f;
    texturecoordinats[10][0]=1.03f;
    texturecoordinats[10][1]=0.04f;
    texturecoordinats[10][2]=1.f;
    texturecoordinats[10][3]=0.0f;
    for(int__ i=0;i<10;i++)
    {
        texturecoordinats[i][0]=.6f;
        texturecoordinats[i][1]=-0.3f;
        texturecoordinats[i][2]=1.0f;
        texturecoordinats[i][3]=0.01f;
    }
    texturecoordinats[1][0]=1.f;
    texturecoordinats[1][1]=.0f;
    texturecoordinats[1][2]=.95f;
    texturecoordinats[1][3]=0.01f;
    vertexcoordinats[1][0]=-.52f;
    vertexcoordinats[1][1]=-.32f;
    vertexcoordinats[1][2]=-.6f;
    vertexcoordinats[1][3]=-.8f;
    vertexcoordinats[2][0]=-.31f;
    vertexcoordinats[2][1]=-.11f;
    vertexcoordinats[2][2]=-.6f;
    vertexcoordinats[2][3]=-.8f;
    vertexcoordinats[3][0]=-.1f;
    vertexcoordinats[3][1]=.1f;
    vertexcoordinats[3][2]=-.6f;
    vertexcoordinats[3][3]=-.8f;
    vertexcoordinats[4][0]=.11f;
    vertexcoordinats[4][1]=.31f;
    vertexcoordinats[4][2]=-.6f;
    vertexcoordinats[4][3]=-.8f;
    vertexcoordinats[5][0]=.32f;
    vertexcoordinats[5][1]=.52f;
    vertexcoordinats[5][2]=-.6f;
    vertexcoordinats[5][3]=-.8f;
    texturecoordinats[11][0]=.35f;
    texturecoordinats[11][1]=1.35f;
    texturecoordinats[11][2]=1.f;
    texturecoordinats[11][3]=.0f;
    texturecoordinats[12][0]=.38f;
    texturecoordinats[12][1]=1.35f;
    texturecoordinats[12][2]=1.0f;
    texturecoordinats[12][3]=0.0f;
    texturecoordinats[13][0]=.35f;
    texturecoordinats[13][1]=1.35f;
    texturecoordinats[13][2]=1.0f;
    texturecoordinats[13][3]=0.0f;
    texturecoordinats[14][0]=.38f;
    texturecoordinats[14][1]=1.35f;
    texturecoordinats[14][2]=1.0f;
    texturecoordinats[14][3]=0.0f;
    texturecoordinats[15][0]=.38f;
    texturecoordinats[15][1]=1.38f;
    texturecoordinats[15][2]=1.0f;
    texturecoordinats[15][3]=0.0f;
    texturecoordinats[16][0]=.5f;
    texturecoordinats[16][1]=-0.6f;
    texturecoordinats[16][2]=1.0f;
    texturecoordinats[16][3]=0.01f;
    texturecoordinats[17][0]=.6f;
    texturecoordinats[17][1]=-0.3f;
    texturecoordinats[17][2]=1.0f;
    texturecoordinats[17][3]=0.01f;
    texturecoordinats[18][0]=.5f;
    texturecoordinats[18][1]=-0.49f;
    texturecoordinats[18][2]=0.991f;
    texturecoordinats[18][3]=0.01f;
    texturecoordinats[19][0]=.5f;
    texturecoordinats[19][1]=-0.45f;
    texturecoordinats[19][2]=1.0f;
    texturecoordinats[19][3]=0.01f;
    texturecoordinats[20][0]=.6f;
    texturecoordinats[20][1]=-0.3f;
    texturecoordinats[20][2]=1.0f;
    texturecoordinats[20][3]=0.01f;
    texturecoordinats[21][0]=.89f;
    texturecoordinats[21][1]=.25f;
    texturecoordinats[21][2]=.9f;
    texturecoordinats[21][3]=.1f;
    texturecoordinats[22][0]=.6f;
    texturecoordinats[22][1]=-0.3f;
    texturecoordinats[22][2]=1.0f;
    texturecoordinats[22][3]=0.01f;
    texturecoordinats[23][0]=.6f;
    texturecoordinats[23][1]=-0.5f;
    texturecoordinats[23][2]=1.0f;
    texturecoordinats[23][3]=0.01f;
    texturecoordinats[24][0]=.5f;
    texturecoordinats[24][1]=-0.5f;
    texturecoordinats[24][2]=1.0f;
    texturecoordinats[24][3]=0.01f;
    texturecoordinats[25][0]=.6f;
    texturecoordinats[25][1]=-0.3f;
    texturecoordinats[25][2]=1.0f;
    texturecoordinats[25][3]=0.01f;
    texturecoordinats[26][0]=.5f;
    texturecoordinats[26][1]=-0.45f;
    texturecoordinats[26][2]=0.98f;
    texturecoordinats[26][3]=0.01f;
    texturecoordinats[27][0]=.6f;
    texturecoordinats[27][1]=-0.3f;
    texturecoordinats[27][2]=1.0f;
    texturecoordinats[27][3]=0.01f;
    texturecoordinats[28][0]=.5f;
    texturecoordinats[28][1]=-0.4f;
    texturecoordinats[28][2]=1.0f;
    texturecoordinats[28][3]=0.01f;
    texturecoordinats[29][0]=.5f;
    texturecoordinats[29][1]=-0.4f;
    texturecoordinats[29][2]=1.0f;
    texturecoordinats[29][3]=0.01f;
    texturecoordinats[30][0]=.3f;
    texturecoordinats[30][1]=-0.6f;
    texturecoordinats[30][2]=1.0f;
    texturecoordinats[30][3]=0.01f;
    texturecoordinats[31][0]=.6f;
    texturecoordinats[31][1]=-0.3f;
    texturecoordinats[31][2]=1.0f;
    texturecoordinats[31][3]=0.01f;
    texturecoordinats[32][0]=.6f;
    texturecoordinats[32][1]=-0.3f;
    texturecoordinats[32][2]=0.9f;
    texturecoordinats[32][3]=0.8f;
    texturecoordinats[33][0]=.44f;
    texturecoordinats[33][1]=0.06f;
    texturecoordinats[33][2]=1.0f;
    texturecoordinats[33][3]=0.05f;
    texturecoordinats[34][0]=0.95f;
    texturecoordinats[34][1]=0.4f;
    texturecoordinats[34][2]=0.8f;
    texturecoordinats[34][3]=0.05f;
    float__ dc=0.0;
    for(int__ c=0;c<21;c++)
        for(int__ a=0;a<3;a++)
            for(int__ b=0;b<6;b++)
            {
                locatelinecoordinats[c][a][b][0]=-1.5f+(b+3)*0.3f;
                locatelinecoordinats[c][a][b][1]=-1.5f+(b+2)*0.3f;
                if(c==3||c==7)
                    dc=-0.05;
                if(c==5)
                    dc=-0.1;
                if(c==9)
                    dc=0.05;
                if(c==11)
                    dc=0.1;
                if(c==13)
                    dc=0.05;
                if(c==17)
                    dc=0.0;
                locatelinecoordinats[c][a][b][2]=1.f-.4f*(a+1)-0.17+dc;
                locatelinecoordinats[c][a][b][3]=1.f-.4f*(a+1)-0.21+dc;
                locatelinecoordinats[c][a][b][4]=1.f-.4f*(a+2)-0.17+dc;
                locatelinecoordinats[c][a][b][5]=1.f-.4f*(a+2)-0.21+dc;
                locatelinecoordinats[c][a][b][6]=1.f-.4f*a-0.17f+dc;
                locatelinecoordinats[c][a][b][7]=1.f-.4f*a-0.21f+dc;
            }
			*/
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
		//if(!start){
			srand(time(0));
			GetRandomMassive(max_);
			//start = true;
		//}
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