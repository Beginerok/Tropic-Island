#include "Scene1.h"

Scene1::Scene1(void)
{
	image = new Image[CountTexture];
	image->TextureCoordinats = new float* [CountTexture];
	image->VertexCoordinats = new float* [CountTexture];
	image->Name = new std::string[CountTexture];
	for (int i = 0; i < CountTexture; i++)
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
	for (int i = 0; i < CountDrum; i++) {
		rotate[i] = 360.0f;
		startrotate[i] = false;
	}
	//randommassive = new int[30];
	start = true;
	flogout.open("log.txt");
	animateboomer = 0;
	slowlychangesprite = 0;
	animation = new Animation();
	animation2 = new Animation();
	animation3 = new Animation();
	drumanimation = new int*[3];
	drumanimation[0] = new int[CountDrum * CountTextureOnDrum];
	drumanimation[1] = new int[CountDrum * CountTextureOnDrum];
	drumanimation[2] = new int[CountDrum * CountTextureOnDrum];
	speedchangeanimation = new int[CountDrum * CountTextureOnDrum];
	for (int i = 0; i < CountDrum * CountTextureOnDrum; i++)
	{
		drumanimation[0][i] = 0;
		drumanimation[1][i] = 0;
		drumanimation[2][i] = 0;
		speedchangeanimation[i] = 0;
	}
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
	if (strstr(reinterpret_cast<const char*>(path), "gif"))
		ext = IL_GIF;

	ilLoad(ext, reinterpret_cast<const ILstring>(path));
	// ��������� ���� ������
	err = ilGetError();
	// ���� ��� �� ����� ���� ������ ����
	if (err != IL_NO_ERROR) {
		// ��������� ������ � �������
		strError = (wchar_t *)iluErrorString(err);
		// ������ ��������� �� ������
#ifdef _WINDOWS_2
		MessageBox(NULL, NULL, "������ ��� �������� il!", MB_OK);
#endif
		// ����� �� ���������
		flogout << "Error loading image: " << reinterpret_cast<const char*>(path) << std::endl;
		flogout.close();
		exit(EXIT_FAILURE);
	}
	// ������ �����������
	width = ilGetInteger(IL_IMAGE_WIDTH);
	// ������ �����������
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	// ����� ���� �� �������
	//int bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	// ��� �������� ������
	type = ilGetInteger(IL_IMAGE_FORMAT);
	/*
	unsigned int type;
	// �������������� ��� ��� OpenGL
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
	// ������ ��������
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
		/*
		max_ = vectordrum.size() - 1, min_ = 0;
		srand(time(NULL));
		for (int i = 0; i < 30; i++)
		{
			SetMassive(i, GetRandom());
		}
		GetRandomMassive();
		*/
	}
	if (iter > 15)
		return 0;
	else
		return 1;
}
void Scene1::ShowDrum(int countdrums,/* float*rotate_,*/ int counttextureondrums,std::vector<std::string> drum,/* int*DrumPosition,
	int credits, int win, int totalbet, const char*line, int bet, bool*lines, int**ms*/ bool*buttons,int pressbutton)
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f); 
	//29.03.2019
	if (buttons[2] && pressbutton == 1) {
		StartRotate();
	}
	Rotate();
	int k = -1;
	for (int i = 0; i<countdrums; i++)
	{
		glPushMatrix();
		glRotatef(rotate[i], 1, 0, 0);
		for (int j = 0; j < counttextureondrums; j++)
		{
			//glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(vectordrum[DrumPosition[++k]/*GetMassive(++k)*/])]);
			++k;
			
			if (speedchangeanimation[k] % 23 == 0)
			{
				drumanimation[0][k]++;
				drumanimation[1][k]++;
				drumanimation[2][k]++;
			}
			if (drumanimation[0][k] == animation->path.size())
				drumanimation[0][k] = 0;
			if (drumanimation[1][k] == animation2->path.size())
				drumanimation[1][k] = 0;
			if (drumanimation[2][k] == animation3->path.size())
				drumanimation[2][k] = 0;
			speedchangeanimation[k]++;
			
			/*image->IndexTexture[FindTexture(drum[++k])]*/
			
			if (i == 0 || i == 1)
			{
				std::string str = "content//drum//animated auto//" + std::to_string(drumanimation[0][k]) + ".png";
				glBindTexture(GL_TEXTURE_2D, animation->loader->image->IndexTexture[animation->loader->FindTexture(str)]);
				EnableTexture(i, j);
			}
			if (i == 2)
			{
				std::string str = "content//drum//animated auto 2//" + std::to_string(drumanimation[1][k]) + ".png";
				glBindTexture(GL_TEXTURE_2D, animation2->loader->image->IndexTexture[animation2->loader->FindTexture(str)]);
				EnableTexture(i, j);
			}
			if (i == 3 || i == 4)
			{
				std::string str = "content//drum//animated auto 3//" + std::to_string(drumanimation[2][k]) + ".png";
				glBindTexture(GL_TEXTURE_2D, animation3->loader->image->IndexTexture[animation3->loader->FindTexture(str)]);
				EnableTexture(i, j);
			}
			
		}
		glPopMatrix();
	}
	//glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
/*
int Scene1::GetMassive(int number)
{
	return randommassive[number];
}
void Scene1::SetMassive(int number, int value)
{
	randommassive[number] = value;
}
*/
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
		glVertex3f(-.45f, -.9f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-.45f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.65f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.65f, -.9f, 0.0f);

		glEnd();//HELP
	}
	if (i == 1)
	{
		glBegin(GL_POLYGON);//TAKE

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.15f, -.9f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-.15f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.35f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.35f, -.9f, 0.0f);

		glEnd();//TAKE
	}
	if (i == 2)
	{
		glBegin(GL_POLYGON);//PLAY

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.15f, -.9f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.15f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.05f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.05f, -.9f, 0.0f);

		glEnd();//PLAY
	}
	if (i == 3)
	{
		glBegin(GL_POLYGON);//FLIP

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.45f, -.9f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.45f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.25f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.25f, -.9f, 0.0f);

		glEnd();//FLIP
	}
	if (i == 4)
	{
		glBegin(GL_POLYGON);//EXIT

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.75f, -.9f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.75f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.55f, -1.f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.55f, -.9f, 0.0f);

		glEnd();//EXIT
	}
}
/*
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
	//std::cout<<std::endl;
	return randommassive;
}
*/
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
		if (m == 1) {
			xl = -0.8f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
		if (m == 2) {
			xl = -0.8f;
			xr = -0.48f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = -0.8f;
			xr = -0.48f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
		if (m == 4) {
			xl = -0.8f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr, yd, yu);
		}
		if (m == 5) {
			xl = -0.8f;
			xr = -0.48f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//front up

	//front middle
    if(n == 1)
    {
		if (m == 0) {
			xl = -0.48f;
			xr = -0.16f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonFrontUp(xl, xr, yd, yu);
		}
        if(m == 1){
        xl = -0.48f;
        xr = -0.16f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonFrontMiddle(xl, xr, yd, yu);
        }
		if (m == 2) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = -0.48f;
			xr = -0.16f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
		if (m == 4) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr, yd, yu);
		}
		if (m == 5) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//front middle

	//front down
    if(n == 2)
    {
		if (m == 0) {
			xl = -0.16f;
			xr = 0.16f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonFrontUp(xl, xr, yd, yu);
		}
		if (m == 1) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
        if(m == 2){
        xl = -0.16f;
        xr = 0.16f;
        yd = -0.9f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
		if (m == 3) {
			xl = -0.16f;
			xr = 0.16f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
		if (m == 4) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr, yd, yu);
		}
		if (m == 5) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//front down

	//back up
    if(n == 3)
    {
		if (m == 0) {
			xl = 0.16f;
			xr = 0.48f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonFrontUp(xl, xr, yd, yu);
		}
		if (m == 1) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
		if (m == 2) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = 0.3f;
        yu = 0.9;
        EnablePolygonBackUp(xl, xr, yd, yu);
        }
		if (m == 4) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr, yd, yu);
		}
		if (m == 5) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//back up

	//back middle
    if(n == 4)
    {
		if (m == 0) {
			xl = 0.48f;
			xr = 0.8f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonFrontUp(xl, xr, yd, yu);
		}
		if (m == 1) {
			xl = 0.48f;
			xr = 0.8f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
		if (m == 2) {
			xl = 0.48f;
			xr = 0.8f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = 0.48f;
			xr = 0.8f;
			yd = 0.3f;
			yu = 0.9;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
        if(m == 4){
        xl = 0.48f;
        xr = 0.8f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
		if (m == 5) {
			xl = 0.48f;
			xr = 0.8f;
			yd = -0.9f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//back middle
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
			{
				startrotate[i] = false;
			}
		}
	}
}
void Scene1::StartRotate()
{
	for (int i = 0; i < CountDrum; i++)
	{
		if (startrotate[i] && rotate[i] != 0.0f)
			continue;
		if (rotate[i] >= 360.0f)
		{
			startrotate[i] = true;
			rotate[i] = 0.0f;
			//srand(time(0));
			//GetRandomMassive();
		}
	}
}

void Scene1::LoadNumbersAndWords()
{
	vectornumbersandwords.push_back("CREDITS");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//CREDITS.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\CREDITS.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "CREDITS";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("WIN");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//WIN.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\WIN.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "WIN";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("TOTAL BET");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//TOTAL BET.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\TOTAL BET.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "TOTAL BET";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("0");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//0.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\0.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "0";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("1");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//1.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\1.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "1";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("2");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//2.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\2.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "2";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("3");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//3.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\3.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "3";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("4");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//4.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\4.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "4";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("5");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//5.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\5.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "5";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("6");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//6.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\6.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "6";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("7");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//7.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\7.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "7";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("8");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//8.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\8.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "8";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectornumbersandwords.push_back("9");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//9.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\numbers_and_words\\9.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "9";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

}
void Scene1::ShowNumbersAndWords()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f);
	for (int i = 0; i < vectornumbersandwords.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(vectornumbersandwords[i])]);
		EnableTextureNumbersAndWords(i);
	}
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

void Scene1::EnableTextureNumbersAndWords(int i)
{
	if (i == 0)
	{
		glBegin(GL_POLYGON);//credits

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.8f, 1.f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-.8f, .9f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.f, .9f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.f, 1.f, 1.0f);

		glEnd();//HELP
	}
	if (i == 1)
	{
		glBegin(GL_POLYGON);//win

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.1f, 1.f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.1f, .9f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.1f, .9f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.1f, 1.f, 1.0f);

		glEnd();//win
	}
	if (i == 2)
	{
		glBegin(GL_POLYGON);//totalbet

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.9f, 1.f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(.9f, .9f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.7f, .9f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.7f, 1.f, 1.0f);

		glEnd();//total bet
	}
}
void Scene1::LoadBoomer()
{

	std::vector<std::string> anim;// = new std::vector<std::string>();
	anim.push_back("content//drum//animated auto//0.png");
	anim.push_back("content//drum//animated auto//1.png");
	anim.push_back("content//drum//animated auto//2.png");
	anim.push_back("content//drum//animated auto//3.png");
	anim.push_back("content//drum//animated auto//4.png");
	anim.push_back("content//drum//animated auto//5.png");
	anim.push_back("content//drum//animated auto//6.png");
	anim.push_back("content//drum//animated auto//7.png");
	anim.push_back("content//drum//animated auto//8.png");
	anim.push_back("content//drum//animated auto//9.png");
	anim.push_back("content//drum//animated auto//10.png");
	anim.push_back("content//drum//animated auto//11.png");
	animation = new Animation(anim);

	std::vector<std::string> anim2;// = new std::vector<std::string>();
	anim2.push_back("content//drum//animated auto 2//0.png");
	anim2.push_back("content//drum//animated auto 2//1.png");
	animation2 = new Animation(anim2);

	std::vector<std::string> anim3;// = new std::vector<std::string>();
	anim3.push_back("content//drum//animated auto 3//0.png");
	anim3.push_back("content//drum//animated auto 3//1.png");
	anim3.push_back("content//drum//animated auto 3//2.png");
	anim3.push_back("content//drum//animated auto 3//3.png");
	anim3.push_back("content//drum//animated auto 3//4.png");
	anim3.push_back("content//drum//animated auto 3//5.png");
	anim3.push_back("content//drum//animated auto 3//6.png");
	anim3.push_back("content//drum//animated auto 3//7.png");
	animation3 = new Animation(anim3);

	vectorboomer.push_back("0");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//boomer//0.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\boomer\\0.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = .6f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.2f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "0";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorboomer.push_back("1");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//boomer//1.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\boomer\\1.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = .6f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.2f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "1";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorboomer.push_back("2");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//boomer//2.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\boomer\\2.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = .6f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.2f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "2";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	vectorboomer.push_back("3");
#ifndef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content//boomer//3.png"));
#else
	LoadImage(reinterpret_cast<const ILstring>("content\\boomer\\3.png"));
#endif
	image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
	image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
	image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;

	image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
	image->VertexCoordinats[CountIndexTexture - 1][1] = .6f;
	image->VertexCoordinats[CountIndexTexture - 1][2] = -.2f;
	image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

	image->Name[CountIndexTexture - 1] = "3";
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	
}
void Scene1::ShowBoomer()
{
	//animation->ShowAnimation();
	
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f);
	if (slowlychangesprite > 100 && slowlychangesprite < 200 && animateboomer == 0)
		animateboomer++;
	if (slowlychangesprite > 200 && slowlychangesprite < 300 && animateboomer == 1)
		animateboomer++;
	if (slowlychangesprite > 300 && slowlychangesprite < 400 && animateboomer == 2)
		animateboomer++;
	if (slowlychangesprite > 400 && slowlychangesprite < 500 && animateboomer == 3)
		animateboomer++;
	if (animateboomer == vectorboomer.size())
	{
		animateboomer = 0;
		slowlychangesprite = 0;
	}
	int numTexture = FindTexture(vectorboomer[animateboomer]);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[numTexture]);
	EnableTextureBoomer(numTexture);
	//animateboomer++;
	slowlychangesprite++;
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	
}
void Scene1::EnableTextureBoomer(int animboom)
{
	
	glBegin(GL_QUADS);
	glTexCoord2f(image->TextureCoordinats[animboom][0], image->TextureCoordinats[animboom][2]);
	glVertex2f(image->VertexCoordinats[animboom][0], image->VertexCoordinats[animboom][2]);

	glTexCoord2f(image->TextureCoordinats[animboom][1], image->TextureCoordinats[animboom][2]);
	glVertex2f(image->VertexCoordinats[animboom][1], image->VertexCoordinats[animboom][2]);
	
	glTexCoord2f(image->TextureCoordinats[animboom][1], image->TextureCoordinats[animboom][3]);
	glVertex2f(image->VertexCoordinats[animboom][1], image->VertexCoordinats[animboom][3]);
	
	glTexCoord2f(image->TextureCoordinats[animboom][0], image->TextureCoordinats[animboom][3]);
	glVertex2f(image->VertexCoordinats[animboom][0], image->VertexCoordinats[animboom][3]);
	glEnd();
	
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
	flogout.close();
	//delete randommassive;
}
