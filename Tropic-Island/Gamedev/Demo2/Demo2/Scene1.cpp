#include "Scene1.h"
#ifdef __unix__
#include <stdlib.h>
#include <unistd.h>
#endif
Scene1::Scene1(void)
{
	image = new Image[CountTexture];
	//image->TextureCoordinats = new float* [CountTexture];
	image->VertexCoordinats = new float* [CountTexture];
	image->Name = new std::string[CountTexture];
	for (int i = 0; i < CountTexture; i++)
	{
		//image->TextureCoordinats[i] = new float[4];
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
	drumanimation = new int* [3];
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
	coor = new Coor[3];
	scale = 1.0f;
	scaling = true;
	drums = gluNewQuadric();
	rt = new float[5];
	rt[0] = -0.75;
	rt[1] = -0.45;
	rt[2] = -0.15;
	rt[3] = 0.15;
	rt[4] = 0.45;
	b = true;
	nnn = 20;
	ccc = new bool[6];
	ccc[0] = true;
	ccc[1] = true;
	ccc[2] = true;
	ccc[3] = true;
	ccc[4] = true;
	ccc[5] = true;
	/*
	ccc[0] = false;
	ccc[1] = false;
	ccc[2] = false;
	ccc[3] = false;
	ccc[4] = false;
	ccc[5] = false;
	*/
}
unsigned int Scene1::LoadImage(const ILstring path)
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
	// Получение кода ошибки
	err = ilGetError();
	// Если код не равен нулю ошибка была
	if (err != IL_NO_ERROR) {
		// Получение строки с ошибкой
#ifdef _WIN32
		strError = (wchar_t *)iluErrorString(err);
		// Выдаем сообщение об ошибке
#else
		strError = iluErrorString(err);
#endif
#ifdef _WIN32
		MessageBox(NULL, NULL, L"Ошибка при загрузке il!", MB_OK);
#endif
		// выход из программы
		flogout << "Error loading image: " << reinterpret_cast<const char*>(path) << std::endl;
 		std::cout<< "Error loading image: " << reinterpret_cast<const char*>(path)<<std::endl;
#ifndef _WIN32
		long size;
        char*buf,*ptr;
        size=pathconf(".",_PC_PATH_MAX);
        buf = (char*)malloc((size_t)size);
        ptr=getcwd(buf,(size_t)size);
		std::cout<< ptr<<std::endl;
#endif
		flogout.close();
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
	//iluFlipImage();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[CountIndexTexture]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	
	return image->IndexTexture[CountIndexTexture++];
};
void Scene1::LoadWelcome()
{
	std::ifstream in("welcome coordinats.txt");
	Image_s im;
	if (in.is_open())
	{
		std::string path__;
		while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup) && (in >> im.Z) && (in >> im.alpha))
		{
			im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
			path__ = path__.substr(path__.find_last_of("/\\") + 1);
			size_t dot_i = path__.find_last_of('.');
			im.Name = path__.substr(0, dot_i);
			im.number = welcomev.size();
			welcomev.push_back(im);
		}
	}
	in.close();
	/*
	std::ofstream out;          // поток для записи
	out.open("coordinats.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		out <<"content//welcome.jpg" << std::endl;
		LoadImage(reinterpret_cast<const ILstring>("content//welcome.jpg"));
		
		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;
		out << image->VertexCoordinats[CountIndexTexture - 1][0] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][1] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][2] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][3] << std::endl;
		image->Name[CountIndexTexture - 1] = "welcome";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

		out.close();
	}
	*/
}
int Scene1::FindTexture(std::string name)
{
	int result = -1;
	for (int i = 0; i < CountTexture; i++)
		if (strcmp(image->Name[i].c_str(), name.c_str()) == 0)
			result = image->number[i];
	return result;
}
int Scene1::FindTexture(std::string name, std::vector<Image_s> vec)
{
	int result = -1,size = vec.size();
	for (int i = 0; i < size; i++)
		if (strcmp(vec[i].Name.c_str(), name.c_str()) == 0)
		{
			result = i;
			break;
		}
	return result;
}
void Scene1::ShowWelcome(bool show)
{
	if (!show)
		return;
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.0f);
	int numb = FindTexture("welcome",welcomev);
	EnableTexture(welcomev[numb],true,true);

	numb = FindTexture("logo", welcomev);
	EnableTexture(welcomev[numb],true,true);

	if (AnimateBar>10)
		AnimateBar = 0;
	NameAnimateBar = "bar";

	std::stringstream out;
	out << AnimateBar;
	NameAnimateBar += out.str();
	{
		numb = FindTexture(NameAnimateBar, welcomev);
		EnableTexture(welcomev[numb],true,true);
	}
	NameAnimateBar.clear();
	AnimateBar++;
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void Scene1::EnableTexture(Image_s im, bool third, bool alpha)
{
	glBindTexture(GL_TEXTURE_2D, im.IndexTexture);
	if (alpha)
	{
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	if (!third)
		glVertex2f(im.Xright, im.Yup);
	else
		glVertex3f(im.Xright, im.Yup, im.Z);
	glTexCoord2f(0.0f, 1.0f);
	if (!third)
		glVertex2f(im.Xleft, im.Yup);
	else
		glVertex3f(im.Xleft, im.Yup, im.Z);
	glTexCoord2f(0.0f, 0.0f);
	if (!third)
		glVertex2f(im.Xleft, im.Ydown);
	else
		glVertex3f(im.Xleft, im.Ydown, im.Z);
	glTexCoord2f(1.0f, 0.0f);
	if (!third)
		glVertex2f(im.Xright, im.Ydown);
	else
		glVertex3f(im.Xright, im.Ydown, im.Z);
	glEnd();
	if (alpha)
	{
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
}
int Scene1::LoadButtons(int iter)
{
	if (iter == 17)
	{
		std::ifstream in("buttons coordinats.txt");
		Image_s im;
		if (in.is_open())
		{
			std::string path__;
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup))
			{
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
				path__ = path__.substr(path__.find_last_of("/\\") + 1);
				size_t dot_i = path__.find_last_of('.');
				im.Name = path__.substr(0, dot_i);
				im.number = buttonsv.size();
				buttonsv.push_back(im);
			}
			in.close();
		}
	}
	if (iter > 16)
		return 0;
	else
		return 1;
}
void Scene1::ShowButtons()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.0f);
	for (int i = 0; i < buttonsv.size() / 2; i++)
		EnableTexture(buttonsv[i],false,false);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
int Scene1::LoadWords(int iter)
{
	if (iter == 18)
	{
		std::ifstream in("words coordinats.txt");
		Image_s im;
		if (in.is_open())
		{
			std::string path__;
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup))
			{
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
				path__ = path__.substr(path__.find_last_of("/\\") + 1);
				size_t dot_i = path__.find_last_of('.');
				im.Name = path__.substr(0, dot_i);
				im.number = wordsv.size();
				wordsv.push_back(im);
			}
			in.close();
		}
	}
	if (iter > 17)
		return 0;
	else
		return 1;
}
int Scene1::LoadNumbers(int iter)
{
	if (iter == 19)
	{
		std::ofstream out;          // поток для записи
		out.open("numbers coordinats.txt"); // окрываем файл для записи
		if (out.is_open())
		{
			out << "content//numbers_and_words//0.png" << std::endl;
			vectornumbersandwords.push_back("0");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//0.png"));

			image->Name[CountIndexTexture - 1] = "0";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//1.png" << std::endl;
			vectornumbersandwords.push_back("1");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//1.png"));

			image->Name[CountIndexTexture - 1] = "1";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//2.png" << std::endl;
			vectornumbersandwords.push_back("2");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//2.png"));

			image->Name[CountIndexTexture - 1] = "2";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//3.png" << std::endl;
			vectornumbersandwords.push_back("3");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//3.png"));

			image->Name[CountIndexTexture - 1] = "3";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("4");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//4.png"));

			out << "content//numbers_and_words//4.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "4";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("5");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//5.png"));

			out << "content//numbers_and_words//5.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "5";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("6");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//6.png"));

			out << "content//numbers_and_words//6.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "6";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("7");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//7.png"));

			out << "content//numbers_and_words//7.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "7";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("8");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//8.png"));

			out << "content//numbers_and_words//8.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "8";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("9");
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//9.png"));

			out << "content//numbers_and_words//9.png" << std::endl;
			image->Name[CountIndexTexture - 1] = "9";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//cross.png" << std::endl;
			vectornumbersandwords.push_back("cross");//1
			LoadImage(reinterpret_cast<const ILstring>("content//cross.png"));

			image->Name[CountIndexTexture - 1] = "cross";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out.close();
		}
	}
	if (iter > 18)
		return 0;
	else
		return 1;
}
void Scene1::ShowNumbersAndWords(int credits, int win, int totalbet)
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f);
	for (int i = 0; i < wordsv.size(); i++)
		EnableTexture(wordsv[i],false,false);
	DrawNumbers(credits, 0);
	DrawNumbers(win, 1);
	DrawNumbers(totalbet, 2);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
//numbers
void Scene1::DrawNumbers(int number,int pos)
{
	char*word = new char[25];
#ifndef _WIN32
	sprintf(word, "%d", number);
#else
	sprintf_s(word, 25, "%d", number);
#endif
	coor[0].x.clear();
	coor[1].x.clear();
	coor[2].x.clear();

	coor[0].x.push_back(-0.75f);//credits
	coor[0].y = 0.8;
	coor[0].width = 0.03f;
	coor[0].height = 0.1;
	
	coor[1].x.push_back(-0.05f);//win
	coor[1].y = 0.8;
	coor[1].width = 0.03f;
	coor[1].height = 0.1;

	coor[2].x.push_back(0.65f);//totalbet
	coor[2].y = 0.8;
	coor[2].width = 0.03f;
	coor[2].height = 0.1;

	for (int i = 0; i < strlen(word); i++)
		coor[pos].x.push_back(coor[pos].x[i] + coor[pos].width);
	for (int i = 0; i < strlen(word); i++) {
		std::string str = "";
		str+=word[i];
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(str)]);
		EnableTextureNumbers(i,pos);
		str.clear();
	}
	delete[] word;
}
void Scene1::EnableTextureNumbers(int position,int numberword)
{
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(coor[numberword].x[position], coor[numberword].y, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(coor[numberword].x[position], coor[numberword].y + coor[numberword].height, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y + coor[numberword].height,1.0f);
	glEnd();
}
int Scene1::LoadBorder(int iter)
{
	if (iter == 20)
	{
		std::ifstream in("help border coordinats.txt");
		Image_s im;
		if (in.is_open())
		{
			std::string path__;
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup) && (in >> im.Z) && (in >> im.alpha))
			{
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
				path__ = path__.substr(path__.find_last_of("/\\") + 1);
				size_t dot_i = path__.find_last_of('.');
				im.Name = path__.substr(0, dot_i);
				im.number = borderhelpv.size();
				borderhelpv.push_back(im);
			}
			in.close();
		}
	}
	if (iter > 19)
		return 0;
	else
		return 1;
}
void Scene1::ShowBorder()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_BLEND);
	/*
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f);
	*/
	int numb = FindTexture("border", borderhelpv);
	EnableTexture(borderhelpv[numb],true,false);

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
//numbers
void Scene1::ShowHelp()
{
	for (int i = 1; i < borderhelpv.size(); i++)
		EnableTexture(borderhelpv[i], true, borderhelpv[i].alpha);
	/*
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("auto11")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.55f, 0.45f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, 0.45f, 1.0f);
	glEnd();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("5")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05f, 0.45f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.05f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.15f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.15f, 0.45f, 1.0f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("auto22")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.55f, 0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.55f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, 0.225f, 1.0f);
	glEnd();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("1")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1f, 0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.1f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.15f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.15f, 0.225f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("0")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05f, 0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.05f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, 0.025f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1f, 0.225f, 1.0f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("auto33")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.55f, 0.0f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.55f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, 0.0f, 1.0f);
	glEnd();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("1")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1f, 0.0f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.15f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.15f, 0.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("5")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05f, 0.0f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.05f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1f, 0.0f, 1.0f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("auto44")]);
	glBegin(GL_POLYGON);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.55f, -0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.55f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3f, -0.225f, 1.0f);
	glEnd();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("2")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1f, -0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.1f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.15f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.15f, -0.225f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("0")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05f, -0.225f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(-0.05f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, -0.425f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1f, -0.225f, 1.0f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("auto55")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25f, 0.45f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(0.25f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.45f, 1.0f);
	glEnd();

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("2")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.45f, 0.45f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(0.45f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.4f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.4f, 0.45f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("5")]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.45f, 1.0f);

	glTexCoord2f(1.f, 0.0f);
	glVertex3f(0.5f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.45f, 0.25f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.45f, 0.45f, 1.0f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	*/
}
//numbers
void Scene1::ShowLine(bool firstline, bool secondline, bool thirdline)
{
	if (firstline)
	{
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]);
		glBegin(GL_POLYGON);//up both line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, 0.32f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, 0.3f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, 0.3f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, 0.32f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//up line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, 0.67f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, 0.67f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal left-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.78f, 0.49f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.78f, 0.51f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.85f, 0.51f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.85f, 0.49f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//first left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.76f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.76f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//second left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.47f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.47f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.49f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.49f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//third left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.18f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.18f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.20f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.20f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//four left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.13f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.13f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.15f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.15f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//five left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.44f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.44f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.46f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.46f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//six left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.76f, 0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.76f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.78f, 0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.78f, 0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal right-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, 0.49f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, 0.51f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.85f, 0.51f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.85f, 0.49f, 1.0f);
		glEnd();
	}
	if (secondline)
	{
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]);
		glBegin(GL_POLYGON);//up line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, 0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, 0.27f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, 0.27f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, 0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//up both line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, -0.27f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, -0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, -0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, -0.27f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal left-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.78f, -0.01f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.78f, 0.01f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.85f, 0.01f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.85f, -0.01f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//first left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.76f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.76f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//second left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.47f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.47f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.49f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.49f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//third left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.18f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.18f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.20f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.20f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//four left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.13f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.13f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.15f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.15f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//five left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.44f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.44f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.46f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.46f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//six left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.76f, -0.29f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.76f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.78f, 0.29f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.78f, -0.29f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal right-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, -0.01f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, 0.01f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.85f, 0.01f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.85f, -0.01f, 1.0f);
		glEnd();
	}
	if (thirdline)
	{
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]);
		glBegin(GL_POLYGON);//up both line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, -0.32f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, -0.3f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, -0.3f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, -0.32f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//up line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, -0.67f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, -0.67f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal left-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.78f, -0.49f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.78f, -0.51f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.85f, -0.51f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.85f, -0.49f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//first left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.76f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.76f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.78f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.78f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//second left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.47f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.47f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.49f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.49f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//third left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-.18f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(-.18f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-.20f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-.20f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//four left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.13f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.13f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.15f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.15f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//five left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.44f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.44f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.46f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.46f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//six left vertical line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.76f, -0.3f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.76f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.78f, -0.69f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.78f, -0.3f, 1.0f);
		glEnd();

		glBegin(GL_POLYGON);//gorizontal right-middle line
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(.78f, -0.49f, 1.0f);

		glTexCoord2f(1.f, 0.0f);
		glVertex3f(.78f, -0.51f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(.85f, -0.51f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(.85f, -0.49f, 1.0f);
		glEnd();
	}
}
//numbers
int Scene1::LoadDrum(int iter)
{
	if (iter == 0)
	{
		vectordrum.push_back("auto1");//1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto1.png"));
		/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;
		*/
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto2.png"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;
		*/
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto3.png"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;
		*/
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto4.png"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto5.png"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "auto5";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	/*
	if (iter == 5)
	{
		vectordrum.push_back("auto6");//6
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto6.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto7.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto8.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto9.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto10.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto11.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto12.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto13.png"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto14.jpg"));
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
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto15.png"));
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
	*/
	if (iter == 15)
	{
		vectordrum.push_back("bonus");//16
		LoadImage(reinterpret_cast<const ILstring>("content//drum//bonus.png"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "bonus";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 16)
	{
		vectordrum.push_back("wild");//17
		LoadImage(reinterpret_cast<const ILstring>("content//drum//wild.jpg"));/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image->Name[CountIndexTexture - 1] = "wild";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

	}
	if (iter > 15)
		return 0;
	else
		return 1;
}
bool Scene1::ShowDrum(int countdrums, int counttextureondrums,std::vector<std::string> drum,bool*buttons,int pressbutton,int *upbutton)
{
	if (!buttons[2] && pressbutton == 1 && *upbutton==0)
			StartRotate(upbutton);
	bool stop = Rotate();
	int k = -1;
	
	for (int i = 0; i < countdrums; i++)
	{
		glPushMatrix();
		/*
		glRotated(90, 0, 1, 0);
		glRotatef(rotate[i], 0, 0, 1);
		gluQuadricDrawStyle(drums, GLU_FILL);
		glTranslatef(0.0, 0.0, rt[i]);
		
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(drum[++k])]);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		glRotated(90, 0, 0, 1);
		gluCylinder(drums, 0.68f, 0.68f, 0.3f, 30, 30);
		gluQuadricTexture(drums, true);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		*/
		//glRotatef(180, 0, 1, 0);
		glRotatef(rotate[i], 1, 0, 0);
		for (int j = 0; j < counttextureondrums; j++)
		{
			glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(drum[++k])]);
			EnableTexture(i, j);
		}
		
		glPopMatrix();
	}
	return stop;
}
//numbers
void Scene1::EnablePolygonFrontUp(float xleft, float xright, float ydown, float yup)
{
	if (ccc[0])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, yup, 0.0f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2d(1.0f, (float)i / n);
			glVertex3d(xleft, (0.68f * sin((90.0 - 60.0 / n * i) *0.0175)), (-0==round(0.68f * cos((90.0 - 60.0 / n * i) * 0.0175)*100)/100)?0: round(0.68f * cos((90.0 - 60.0 / n * i) * 0.0175) * 100) / 100);
			if (b)
				std::cout << (float)i / n<<" "<< (0.68f * sin((90.0 - 60.0 / n * i) * 0.0175)) << " " << round(0.68f * cos((90.0 - 60.0 / n * i) * 0.0175) * 100) / 100<< std::endl;
		}
		if (b)
			std::cout << "------------" << std::endl;
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, ydown, .6f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, ydown, .6f);

		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2d(0.0f, 1.0f - (float)i / n);
			glVertex3d(xright, (0.68f * sin((30.0 + 60.0 / n * i)*0.0175)), (-0 == round(0.68f * cos((30.0 + 60.0 / n * i) * 0.0175) * 100) / 100) ? 0 : round(0.68f * cos((30.0 + 60.0 / n * i) * 0.0175) * 100) / 100);
			if (b)
				std::cout << 1.0f - (float)i / n<<" "<< (0.68f * sin((30.0 + 60.0 / n * i) * 0.0175)) << " " << round(0.68f * cos((30.0 + 60.0 / n * i) * 0.0175) * 100) / 100<< std::endl;
		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, yup, 0.0f);

		glEnd();

	}
}
void Scene1::EnablePolygonFrontMiddle(float xleft, float xright, float ydown, float yup)
{
	if (ccc[1])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, yup, .6f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(1.0f, (float)i / n);
			glVertex3f(xleft, 0.68f * sin((30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175));
		}
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, ydown, .6f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, ydown, .6f);

		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(0.0f, 1.0f -(float) i / n);
			glVertex3f(xright, 0.68f * sin((-30.0 + 60.0 / n * i) * 0.0175), 0.68f * cos((-30.0 + 60.0 / n * i) * 0.0175));
			if (b)
				std::cout << 0.68f * sin((90.0 + 60.0 / n * i) * 0.0175) << " " << 0.68f * cos((90.0 + 60.0 / n * i) * 0.0175) << std::endl;

		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, yup, .6f);

		glEnd();
	}
}
void Scene1::EnablePolygonFrontDown(float xleft, float xright, float ydown, float yup)
{
	if (ccc[2])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, yup, .6f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(1.0f, 0.0f + (float)i / n);
			glVertex3f(xleft, 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175));
		}

		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, ydown, 0.0f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, ydown, 0.0f);

		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(0.0f, 1.0f - (float)i / n);
			glVertex3f(xright, 0.68f * sin((-90.0 + 60.0 / n * i) * 0.0175), 0.68f * cos((-90.0 + 60.0 / n * i) * 0.0175));
			if (b)
				std::cout << 0.68f * sin((-90.0 + 60.0 / n * i) * 0.0175) << " " << 0.68f * cos((-90.0 + 60.0 / n * i) * 0.0175) << std::endl;

		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, yup, .6f);

		glEnd();
	}
	
}
void Scene1::EnablePolygonBackUp(float xleft, float xright, float ydown, float yup)
{
	if (ccc[3])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, ydown, -.6f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(1.0f, 0.0f +(float) i / n);
			glVertex3f(xleft, 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175));
		}
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, yup, 0.0f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, yup, 0.0f);
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(0.0f, 1.0f - (float)i / n);
			glVertex3f(xright, 0.68f * sin((90.0 + 60.0 / n * i) * 0.0175), 0.68f * cos((90.0 + 60.0 / n * i) * 0.0175));
			if (b)
				std::cout << 0.68f * sin((90.0 + 60.0 / n * i) * 0.0175) << " " << 0.68f * cos((90.0 + 60.0 / n * i) * 0.0175) << std::endl;

		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, ydown, -.6f);

		glEnd();
	}
	
}
void Scene1::EnablePolygonBackMiddle(float xleft, float xright, float ydown, float yup)
{
	if (ccc[4])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, ydown, -.6f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(1.0f, (float)i / n);
			glVertex3f(xleft, 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175));
		}
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, yup, -.6f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, yup, -.6f);

		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(0.0f, 1.0f - (float)i / n);
			glVertex3f(xright, 0.68f * sin((150.0 + 60.0 / n * i) * 0.0175), 0.68f * cos((150.0 + 60.0 / n * i) * 0.0175));
			if (b)
				std::cout << 0.68f * sin((150.0 + 60.0 / n * i) * 0.0175) << " " << 0.68f * cos((150.0 + 60.0 / n * i) * 0.0175) << std::endl;

		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, ydown, -.6f);

		glEnd();
	}
	
}
void Scene1::EnablePolygonBackDown(float xleft, float xright, float ydown, float yup)
{
	if (ccc[5])
	{
		glBegin(GL_POLYGON);

		//glTexCoord2f(1.0f, 0.0f);
		//glVertex3f(xleft, ydown, 0.0f);
		int n = nnn;
		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(1.0f, 0.0f + (float)i / n);
			glVertex3f(xleft, 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175));
		}
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(xleft, yup, -.6f);

		//glTexCoord2f(0.0f, 1.0f);
		//glVertex3f(xright, yup, -.6f);


		for (int i = 0; i < n+1; i++)
		{
			glTexCoord2f(0.0f, 1.0f - (float)i / n);
			glVertex3f(xright, 0.68f * sin((-150.0 + 60.0 / n * i) * 0.0175), 0.68f * cos((-150.0 + 60.0 / n * i) * 0.0175));
			if (b)
				std::cout << 0.68f * sin((-150.0 + 60.0 / n * i) * 0.0175) << " " << 0.68f * cos((-150 + 60.0 / n * i) * 0.0175) << std::endl;

		}
		b = false;
		//glTexCoord2f(0.0f, 0.0f);
		//glVertex3f(xright, ydown, 0.0f);

		glEnd();
	}
}
//numbers
void Scene1::EnableTexture(int n, int m)
{
    if(n == 0)
    {
        if(m == 0){
        xl = -0.78f;//08
        xr = -0.48f;
        yd = 0.3f;
        yu = 0.68;//09
        EnablePolygonFrontUp(xl, xr, yd, yu);
        }
		if (m == 1) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
		if (m == 2) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = -0.78f;
			xr = -0.48f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
		if (m == 4) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr, yd, yu);
		}
		if (m == 5) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.68f;
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
			yu = 0.68;
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
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = -0.48f;
			xr = -0.16f;
			yd = 0.3f;
			yu = 0.68;
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
			yd = -0.68f;
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
			yu = 0.68;
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
        yd = -0.68f;
        yu = -0.3;
        EnablePolygonFrontDown(xl, xr, yd, yu);
        }
		if (m == 3) {
			xl = -0.16f;
			xr = 0.16f;
			yd = 0.3f;
			yu = 0.68;
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
			yd = -0.68f;
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
			yu = 0.68;
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
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
        if(m == 3){
        xl = 0.16f;
        xr = 0.48f;
        yd = 0.3f;
        yu = 0.68;
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
			yd = -0.68f;
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
			xr = 0.78f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonFrontUp(xl, xr, yd, yu);
		}
		if (m == 1) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr, yd, yu);
		}
		if (m == 2) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr, yd, yu);
		}
		if (m == 3) {
			xl = 0.48f;
			xr = 0.78f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr, yd, yu);
		}
        if(m == 4){
        xl = 0.48f;
        xr = 0.78f;
        yd = -0.3f;
        yu = 0.3;
        EnablePolygonBackMiddle(xl, xr, yd, yu);
        }
		if (m == 5) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr, yd, yu);
		}
    }
	//back middle
}
bool Scene1::Rotate()
{
	bool stop = false;
	for (int i = 0; i<CountDrum; i++)
	{
		if (startrotate[i])
		{
			if (rotate[i]<1800.0f)
				rotate[i] += 15.0f;
			else
			{
				startrotate[i] = false;
				stop = true;
			}
		}
	}
	return stop;
}
void Scene1::StartRotate(int *upbutton)
{
	for (int i = 0; i < CountDrum; i++)
	{
		if (startrotate[i] && rotate[i] != 0.0f)
			continue;
		if (rotate[i] >= 360.0f)
		{
			*upbutton += 1;
			startrotate[i] = true;
			rotate[i] = 0.0f;
		}
	}
}
//numbers
void Scene1::LoadAnimatedAuto()
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
}
//numbers
Scene1::~Scene1()
{
	//for (int i = 0; i<CountTexture; i++)
		//delete[] image->TextureCoordinats[i];
	//delete[] image->TextureCoordinats;
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
