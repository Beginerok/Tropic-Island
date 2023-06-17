#include "Scene1.h"
#ifdef __unix__
#include <stdlib.h>
#include <unistd.h>
#endif
Scene1::Scene1(void)
{
	b = true;
	rotate__ = 0.0;
	image = new Image[CountTexture];
	image->VertexCoordinats = new float* [CountTexture];
	//image->Name = new std::string[CountTexture];
	for (int i = 0; i < CountTexture; i++)
	{
		image->VertexCoordinats[i] = new float[4];
		//image->Name[i] = "";
	}
#if SDLAPI_==1 || WINAPI_==1
	image->IndexTexture = new unsigned int[CountTexture];
#else
	//image->IndexTexture = new QOpenGLTexture[CountTexture];
#endif
	image->number = new int[CountTexture];
	CountIndexTexture = 0;
	AnimateBar = 0;
	rotate = new float[CountDrum];
	startrotate = new bool[CountDrum];
	for (int i = 0; i < CountDrum; i++) {
		rotate[i] = 360.0f;
		startrotate[i] = false;
	}
	flogout.open("log.txt");
	coor = new Coor[3];
	nnn = 20;
	changedrum = new bool[CountDrum];
	for(int i=0;i<CountDrum;i++)
		changedrum[i] = false;
}
#if QTAPI_==1
QOpenGLTexture* Scene1::QTLoadImage(QString path)
{
	qtimage.load(path);
	if (qtimage.isNull())
		std::cout << path.toStdString() << std::endl;
	tmp = new QOpenGLTexture(qtimage.mirrored());
	tmp->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	tmp->setMagnificationFilter(QOpenGLTexture::Linear);
	CountIndexTexture++;
	return tmp;
}
#elif WINAPI_==1 || SDLAPI_==1
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
	err = ilGetError();
	if (err != IL_NO_ERROR) {
#ifdef _WIN32
		strError = (wchar_t *)iluErrorString(err);
#else
		strError = iluErrorString(err);
#endif
#ifdef _WIN32
		MessageBox(NULL, NULL, L"ќшибка при загрузке il!", MB_OK);
#endif
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
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	type = ilGetInteger(IL_IMAGE_FORMAT);
	copyData = ilGetData();
	image->IndexTexture[CountIndexTexture] = 0;
	glGenTextures(1, &image->IndexTexture[CountIndexTexture]);
	glBindTexture(GL_TEXTURE_2D, image->IndexTexture[CountIndexTexture]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	return image->IndexTexture[CountIndexTexture++];
};

#endif
void Scene1::LoadWelcome()
{
	std::ifstream in("welcome coordinats.txt");
	Image_s im;
	if (in.is_open())
	{
		std::string path__;
#if SDLAPI_==1 || WINAPI_==1
		while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup) && (in >> im.Z) && (in >> im.alpha))
#elif QTAPI_ == 1
		while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Yup) && (in >> im.Ydown) && (in >> im.Z) && (in >> im.alpha))
#endif
		{
#if SDLAPI_==1 || WINAPI_==1
			im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str())); 
#elif QTAPI_ == 1
			im.IndexTexture = QTLoadImage(path__.c_str());
#endif
			path__ = path__.substr(path__.find_last_of("/\\") + 1);
			size_t dot_i = path__.find_last_of('.');
			im.Name = path__.substr(0, dot_i);
			im.number = welcomev.size();
			welcomev.push_back(im);
		}
	}
	in.close();
	/*
	std::ofstream out;          // поток дл€ записи
	out.open("coordinats.txt"); // окрываем файл дл€ записи
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
int Scene1::FindTexture(std::string name,std::vector<Image> v)
{
	int result = -1;
	for (int i = 0; i < v.size(); i++)
		if (strcmp(v[i].Name.c_str(), name.c_str()) == 0)
			result = i;
	return result;
}
int Scene1::FindTexture(std::string name)
{
	int result = -1;
	for (int i = 0; i < CountIndexTexture; i++)
		if (strcmp(image[i].Name.c_str(), name.c_str()) == 0)
			result = i;
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
	numb = FindTexture(NameAnimateBar, welcomev);
	EnableTexture(welcomev[numb],true,true);
	NameAnimateBar.clear();
	AnimateBar++;
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void Scene1::EnableTexture(Image_s im, bool third, bool alpha)
{
#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, im.IndexTexture);
#elif QTAPI_ == 1
	im.IndexTexture->bind();
#endif
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
#if SDLAPI_==1 || WINAPI_==1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup))
#elif QTAPI_ == 1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Yup) && (in >> im.Ydown))
#endif
			{
#if SDLAPI_==1 || WINAPI_==1
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
#elif QTAPI_ == 1
				im.IndexTexture = QTLoadImage(path__.c_str());
#endif
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
#if SDLAPI_==1 || WINAPI_==1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup))
#elif QTAPI_ == 1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Yup) && (in >> im.Ydown))
#endif
			{
#if SDLAPI_==1 || WINAPI_==1
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
#elif QTAPI_ == 1
				im.IndexTexture = QTLoadImage(path__.c_str());
#endif
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
		Image tmp;
		std::ofstream out;          // поток дл€ записи
		out.open("numbers coordinats.txt"); // окрываем файл дл€ записи
		if (out.is_open())
		{
			out << "content//numbers_and_words//0.png" << std::endl;
			vectornumbersandwords.push_back("0");

#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//0.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "0";
			tmp.IndexTexture=QTLoadImage("content//numbers_and_words//0.png");
			numbersv.push_back(tmp);
#endif
			image[CountIndexTexture - 1].Name = "0";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//1.png" << std::endl;
			vectornumbersandwords.push_back("1");

#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//1.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "1";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//1.png");
			numbersv.push_back(tmp);
#endif
			image[CountIndexTexture - 1].Name= "1";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//2.png" << std::endl;
			vectornumbersandwords.push_back("2");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//2.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "2";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//2.png");
			numbersv.push_back(tmp);
#endif
			image[CountIndexTexture - 1].Name= "2";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//numbers_and_words//3.png" << std::endl;
			vectornumbersandwords.push_back("3");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//3.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "3";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//3.png");
			numbersv.push_back(tmp);
#endif
			image[CountIndexTexture - 1].Name= "3";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("4");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//4.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "4";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//4.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//4.png" << std::endl;
			image[CountIndexTexture - 1].Name = "4";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("5");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//5.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "5";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//5.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//5.png" << std::endl;
			image[CountIndexTexture - 1].Name = "5";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("6");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//6.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "6";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//6.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//6.png" << std::endl;
			image[CountIndexTexture - 1].Name = "6";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("7");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//7.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "7";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//7.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//7.png" << std::endl;
			image[CountIndexTexture - 1].Name = "7";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("8");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//8.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "8";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//8.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//8.png" << std::endl;
			image[CountIndexTexture - 1].Name = "8";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			vectornumbersandwords.push_back("9");
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//9.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "9";
			tmp.IndexTexture = QTLoadImage("content//numbers_and_words//9.png");
			numbersv.push_back(tmp);
#endif
			out << "content//numbers_and_words//9.png" << std::endl;
			image[CountIndexTexture - 1].Name = "9";
			image->number[CountIndexTexture - 1] = CountIndexTexture - 1;

			out << "content//cross.png" << std::endl;
			vectornumbersandwords.push_back("cross");//1
#if SDLAPI_==1 || WINAPI_==1
			LoadImage(reinterpret_cast<const ILstring>("content//cross.png"));
#elif QTAPI_==1
			//tmp.Name = new std::string[10];
			tmp.Name = "cross";
			tmp.IndexTexture = QTLoadImage("content//cross.png");
			numbersv.push_back(tmp);
#endif
			image[CountIndexTexture - 1].Name = "cross";
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

#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(str)]);
#elif QTAPI_==1
		numbersv[FindTexture(str,numbersv)].IndexTexture->bind();
#endif
		EnableTextureNumbers(i,pos);
		str.clear();
	}
	delete[] word;
}
void Scene1::EnableTextureNumbers(int position,int numberword)
{
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
#if SDLAPI_==1 || WINAPI_==1
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y, 1.0f);
#elif QTAPI_==1
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y + coor[numberword].height, 1.0f);
#endif
		glTexCoord2f(0.0f, 1.0f);
#if SDLAPI_==1 || WINAPI_==1
		glVertex3f(coor[numberword].x[position], coor[numberword].y, 1.0f);
#elif QTAPI_==1
		glVertex3f(coor[numberword].x[position], coor[numberword].y + coor[numberword].height, 1.0f);
#endif
		glTexCoord2f(0.0f, 0.0f);

#if SDLAPI_==1 || WINAPI_==1
		glVertex3f(coor[numberword].x[position], coor[numberword].y + coor[numberword].height, 1.0f);
#elif QTAPI_==1
		glVertex3f(coor[numberword].x[position], coor[numberword].y, 1.0f);
#endif
		glTexCoord2f(1.0f, 0.0f);
#if SDLAPI_==1 || WINAPI_==1
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y + coor[numberword].height,1.0f);
#elif QTAPI_==1
		glVertex3f(coor[numberword].x[position] + coor[numberword].width, coor[numberword].y, 1.0f); 
#endif
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
#if SDLAPI_==1 || WINAPI_==1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Ydown) && (in >> im.Yup) && (in >> im.Z) && (in >> im.alpha))
#elif QTAPI_ == 1
			while ((in >> path__) && (in >> im.Xright) && (in >> im.Xleft) && (in >> im.Yup) && (in >> im.Ydown) && (in >> im.Z) && (in >> im.alpha))
#endif
			{
#if SDLAPI_==1 || WINAPI_==1
				im.IndexTexture = LoadImage(reinterpret_cast<const ILstring>(path__.c_str()));
#elif QTAPI_ == 1
				im.IndexTexture = QTLoadImage(path__.c_str());
#endif
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
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]);
#elif QTAPI_==1
		numbersv[FindTexture("cross",numbersv)].IndexTexture->bind();
#endif
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
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]); 
#elif QTAPI_ == 1
		numbersv[FindTexture("cross", numbersv)].IndexTexture->bind();
#endif

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
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture("cross")]);
#elif QTAPI_==1
		numbersv[FindTexture("cross", numbersv)].IndexTexture->bind();
#endif
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
	Image tmp;
	if (iter == 0)
	{
		vectordrum.push_back("auto1");//1
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto1.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "auto1";
		tmp.IndexTexture = QTLoadImage("content//drum//auto1.png");
		drumv.push_back(tmp);
#endif
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

		image[CountIndexTexture - 1].Name = "auto1";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 1)
	{
		vectordrum.push_back("auto2");//2
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto2.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "auto2";
		tmp.IndexTexture = QTLoadImage("content//drum//auto2.png");
		drumv.push_back(tmp);
#endif
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

		image[CountIndexTexture - 1].Name = "auto2";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 2)
	{

		vectordrum.push_back("auto3");//3
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto3.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "auto3";
		tmp.IndexTexture = QTLoadImage("content//drum//auto3.png");
		drumv.push_back(tmp);
#endif
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

		image[CountIndexTexture - 1].Name = "auto3";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 3)
	{
		vectordrum.push_back("auto4");//4
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto4.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "auto4";
		tmp.IndexTexture = QTLoadImage("content//drum//auto4.png");
		drumv.push_back(tmp);
#endif
		/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image[CountIndexTexture - 1].Name = "auto4";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 4)
	{
		vectordrum.push_back("auto5");//5
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//auto5.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "auto5";
		tmp.IndexTexture = QTLoadImage("content//drum//auto5.png");
		drumv.push_back(tmp);
#endif
		/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image[CountIndexTexture - 1].Name = "auto5";
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

		image[CountIndexTexture - 1].Name = "auto6";
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

		image[CountIndexTexture - 1].Name = "auto7";
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

		image[CountIndexTexture - 1].Name = "auto8";
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

		image[CountIndexTexture - 1].Name = "auto9";
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

		image[CountIndexTexture - 1].Name = "auto10";
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

		image[CountIndexTexture - 1].Name = "auto11";
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

		image[CountIndexTexture - 1].Name = "auto12";
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

		image[CountIndexTexture - 1].Name = "auto13";
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

		image[CountIndexTexture - 1].Name = "auto14";
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

		image[CountIndexTexture - 1].Name = "auto15";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	*/
	if (iter == 15)
	{
		vectordrum.push_back("bonus");//16
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//bonus.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "bonus";
		tmp.IndexTexture = QTLoadImage("content//drum//bonus.png");
		drumv.push_back(tmp);
#endif
		/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image[CountIndexTexture - 1].Name = "bonus";
		image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	}
	if (iter == 16)
	{
		vectordrum.push_back("wild");//17
#if SDLAPI_==1 || WINAPI_==1
		LoadImage(reinterpret_cast<const ILstring>("content//drum//wild.png"));
#elif QTAPI_==1
		//tmp.Name = new std::string[10];
		tmp.Name = "wild";
		tmp.IndexTexture = QTLoadImage("content//drum//wild.png");
		drumv.push_back(tmp);
#endif
		/*
		image->TextureCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][1] = .0f;
		image->TextureCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->TextureCoordinats[CountIndexTexture - 1][3] = .0f;*/

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;

		image[CountIndexTexture - 1].Name = "wild";
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
		glRotatef(rotate[i], 1, 0, 0);
		for (int j = 0; j < counttextureondrums; j++)
		{
#if SDLAPI_==1 || WINAPI_==1
			glBindTexture(GL_TEXTURE_2D, image->IndexTexture[FindTexture(drum[++k])]);
#elif QTAPI_==1
			drumv[FindTexture(drum[++k],drumv)].IndexTexture->bind();
#endif
			EnableTexture(i, j);
		}
		glPopMatrix();
	}
	return stop;
}
void Scene1::StartRotate(int* upbutton)
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
bool Scene1::Rotate()
{
	bool stop = false;
	for (int i = 0; i < CountDrum; i++)
	{
		if (startrotate[i])
		{
			if (rotate[i] < 1800.0f)
			{
				if (rotate[i] < 600)
					rotate[i] += 5.0f;
				else if (rotate[i] <1200)
					rotate[i] += 10.0f;
				else if (rotate[i] < 1800)
					rotate[i] += 5.0f;
				if ((rotate[i] >= 300.0f-i*60) && (rotate[i] < 315.0f - i * 60))
					changedrum[i] = true;
				else if (rotate[i] >= 315.0f - i * 60)
					changedrum[i] = false;
			}
			else
			{
				startrotate[i] = false;
				stop = true;
			}
		}
	}
	return stop;
}
void Scene1::EnablePolygonFrontUp(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 = (float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1-(float)i / n;
		float yTex2 = 1-(float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((90.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((90.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((90.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((90.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((90.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((90.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((90.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((90.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnablePolygonFrontMiddle(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 =(float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1-(float)i / n;
		float yTex2 = 1- (float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((30.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((30.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((30.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((30.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnablePolygonFrontDown(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 = (float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1 - (float)i / n;
		float yTex2 = 1 - (float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnablePolygonBackUp(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 = (float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1 - (float)i / n;
		float yTex2 = 1 - (float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((150.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((150.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((150.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((150.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnablePolygonBackMiddle(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 = (float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1 - (float)i / n;
		float yTex2 = 1 - (float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((210.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((210.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((210.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((210.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnablePolygonBackDown(float xright, float xleft)
{
	glBegin(GL_QUADS);
	int n = nnn;
	for (int i = 0; i < n; i++)
	{
#if SDLAPI_==1 || WINAPI_==1
		float yTex = (float)i / n;
		float yTex2 = (float)(i + 1) / n;
#elif QTAPI_==1
		float yTex = 1 - (float)i / n;
		float yTex2 = 1 - (float)(i + 1) / n;
#endif
		glTexCoord2f(1.0f, yTex);
		glVertex3f(xleft, 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175));
		glTexCoord2f(1.0f, yTex2);
		glVertex3f(xleft, 0.68f * sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex2);
		glVertex3f(xright, 0.68f * sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175), 0.68f * cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175));
		glTexCoord2f(0.0f, yTex);
		glVertex3f(xright, 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175), 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175));
	}
	glEnd();
}
void Scene1::EnableTexture(int n, int m)
{
    if(n == 0)
    {
		if (m == 0) {
			xl = -0.78f;
			xr = -0.48f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonFrontUp(xl, xr);
		}
		if (m == 1) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr);
		}
		if (m == 2) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr);
		}
		if (m == 3) {
			xl = -0.78f;
			xr = -0.48f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr);
		}
		if (m == 4) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr);
		}
		if (m == 5) {
			xl = -0.78f;
			xr = -0.48f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr);
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
			EnablePolygonFrontUp(xl, xr);
		}
		if (m == 1) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr);
		}
		if (m == 2) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr);
		}
		if (m == 3) {
			xl = -0.48f;
			xr = -0.16f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr);
		}
		if (m == 4) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr);
		}
		if (m == 5) {
			xl = -0.48f;
			xr = -0.16f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr);
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
			EnablePolygonFrontUp(xl, xr);
		}
		if (m == 1) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr);
		}
		if (m == 2) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr);
		}
		if (m == 3) {
			xl = -0.16f;
			xr = 0.16f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr);
		}
		if (m == 4) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr);
		}
		if (m == 5) {
			xl = -0.16f;
			xr = 0.16f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr);
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
			EnablePolygonFrontUp(xl, xr);
		}
		if (m == 1) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr);
		}
		if (m == 2) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr);
		}
		if (m == 3) {
			xl = 0.16f;
			xr = 0.48f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr);
		}
		if (m == 4) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr);
		}
		if (m == 5) {
			xl = 0.16f;
			xr = 0.48f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr);
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
			EnablePolygonFrontUp(xl, xr);
		}
		if (m == 1) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonFrontMiddle(xl, xr);
		}
		if (m == 2) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonFrontDown(xl, xr);
		}
		if (m == 3) {
			xl = 0.48f;
			xr = 0.78f;
			yd = 0.3f;
			yu = 0.68;
			EnablePolygonBackUp(xl, xr);
		}
		if (m == 4) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.3f;
			yu = 0.3;
			EnablePolygonBackMiddle(xl, xr);
		}
		if (m == 5) {
			xl = 0.48f;
			xr = 0.78f;
			yd = -0.68f;
			yu = -0.3;
			EnablePolygonBackDown(xl, xr);
		}
    }
	//back middle
}
void Scene1::LoadDrum(QOpenGLExtraFunctions* f)
{
	std::set<float> sleft, sright;
	sleft.insert(-0.78);
	sleft.insert(-0.48);
	sleft.insert(-0.16);
	sleft.insert(0.16);
	sleft.insert(0.48);
	sright.insert(-0.48);
	sright.insert(-0.16);
	sright.insert(0.16);
	sright.insert(0.48);
	sright.insert(0.78);
	std::set<float>::iterator itr, itrright;
	int jIter = 0, nn = 324;//288
	int n = 10;
	float* buf = new float[nn * n * 5];
	indices = new GLuint[36 * n * 5];
	// Displaying set elements
	/* [] =
	{// x,	y,	z,	r,	g,	b,	s,	t
		0.0,0.0,1.0,1.0,0.0,0.0,0.0,1.0,
		0.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,
		1.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,
		1.0,1.0,1.0,0.0,1.0,1.0,1.0,0.0,
		0.0,0.0,1.0,1.0,0.0,0.0,0.0,1.0,
		1.0,0.0,1.0,0.5,0.5,0.5,1.0,1.0,//

		0.0,0.0,1.0,1.0,0.0,0.0,0.0,1.0,
		0.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0,
		-1.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,
		-1.0,1.0,1.0,0.0,1.0,1.0,1.0,0.0,
		0.0,0.0,1.0,1.0,0.0,0.0,0.0,1.0,
		-1.0,0.0,1.0,0.5,0.5,0.5,1.0,1.0
	};
	*/
	for (itr = sleft.begin(), itrright = sright.begin();
		itr != sleft.end(); itr++, itrright++)
	{
		float xleft = *itr;
		float xright = *itrright;
		for (int i = 0; i < n; i++)
		{
			//front up
			float yTex = 1 - (float)i / n;
			float yTex2 = 1 - (float)(i + 1) / n;
			buf[(0 + i * nn) + jIter * n * nn] = xleft;
			buf[(1 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(2 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(3 + i * nn) + jIter * n * nn] = 0.0;
			buf[(4 + i * nn) + jIter * n * nn] = 0.0;
			buf[(5 + i * nn) + jIter * n * nn] = 0.0;
			buf[(6 + i * nn) + jIter * n * nn] = 1.0;
			buf[(7 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(8 + i * nn) + jIter * n * nn] = yTex;

			buf[(9 + i * nn) + jIter * n * nn] = xleft;
			buf[(10 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(11 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(12 + i * nn) + jIter * n * nn] = 0.0;
			buf[(13 + i * nn) + jIter * n * nn] = 0.0;
			buf[(14 + i * nn) + jIter * n * nn] = 0.0;
			buf[(15 + i * nn) + jIter * n * nn] = 1.0;
			buf[(16 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(17 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(18 + i * nn) + jIter * n * nn] = xright;
			buf[(19 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(20 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(21 + i * nn) + jIter * n * nn] = 0.0;
			buf[(22 + i * nn) + jIter * n * nn] = 0.0;
			buf[(23 + i * nn) + jIter * n * nn] = 0.0;
			buf[(24 + i * nn) + jIter * n * nn] = 1.0;
			buf[(25 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(26 + i * nn) + jIter * n * nn] = yTex;

			buf[(27 + i * nn) + jIter * n * nn] = xright;
			buf[(28 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * i) * 0.0175);
			buf[(29 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * i) * 0.0175);
			buf[(30 + i * nn) + jIter * n * nn] = 0.0;
			buf[(31 + i * nn) + jIter * n * nn] = 0.0;
			buf[(32 + i * nn) + jIter * n * nn] = 0.0;
			buf[(33 + i * nn) + jIter * n * nn] = 1.0;
			buf[(34 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(35 + i * nn) + jIter * n * nn] = yTex;

			buf[(36 + i * nn) + jIter * n * nn] = xleft;
			buf[(37 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(38 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(39 + i * nn) + jIter * n * nn] = 0.0;
			buf[(40 + i * nn) + jIter * n * nn] = 0.0;
			buf[(41 + i * nn) + jIter * n * nn] = 0.0;
			buf[(42 + i * nn) + jIter * n * nn] = 1.0;
			buf[(43 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(44 + i * nn) + jIter * n * nn] = yTex2;

			buf[(45 + i * nn) + jIter * n * nn] = xright;
			buf[(46 + i * nn) + jIter * n * nn] = 0.68f * sin((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(47 + i * nn) + jIter * n * nn] = 0.68f * cos((90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(48 + i * nn) + jIter * n * nn] = 0.0;
			buf[(49 + i * nn) + jIter * n * nn] = 0.0;
			buf[(50 + i * nn) + jIter * n * nn] = 0.0;
			buf[(51 + i * nn) + jIter * n * nn] = 1.0;
			buf[(52 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(53 + i * nn) + jIter * n * nn] = yTex2;


			//front middle
			
			yTex = 1 - (float)i / n;
			yTex2 = 1 - (float)(i + 1) / n;
			buf[(54 + i * nn) + jIter * n * nn] = xleft;
			buf[(55 + i * nn) + jIter * n * nn] = 0.68f * sin((30.0 - 60.0 / n * i) * 0.0175);
			buf[(56 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(57 + i * nn) + jIter * n * nn] = 0.0;
			buf[(58 + i * nn) + jIter * n * nn] = 0.0;
			buf[(59 + i * nn) + jIter * n * nn] = 0.0;
			buf[(60 + i * nn) + jIter * n * nn] = 1.0;
			buf[(61 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(62 + i * nn) + jIter * n * nn] = yTex;

			buf[(63 + i * nn) + jIter * n * nn] = xleft;
			buf[(64 + i * nn) + jIter * n * nn] = 0.68f * sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(65 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(66 + i * nn) + jIter * n * nn] = 0.0;
			buf[(67 + i * nn) + jIter * n * nn] = 0.0;
			buf[(68 + i * nn) + jIter * n * nn] = 0.0;
			buf[(69 + i * nn) + jIter * n * nn] = 1.0;
			buf[(70 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(71 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(72 + i * nn) + jIter * n * nn] = xright;
			buf[(73 + i * nn) + jIter * n * nn] = 0.68f * sin((30 - 60.0 / n * i) * 0.0175);
			buf[(74 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(75 + i * nn) + jIter * n * nn] = 0.0;
			buf[(76 + i * nn) + jIter * n * nn] = 0.0;
			buf[(77 + i * nn) + jIter * n * nn] = 0.0;
			buf[(78 + i * nn) + jIter * n * nn] = 1.0;
			buf[(79 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(80 + i * nn) + jIter * n * nn] = yTex;

			buf[(81 + i * nn) + jIter * n * nn] = xright;
			buf[(82 + i * nn) + jIter * n * nn] = 0.68f * sin((30.0 - 60.0 / n * i) * 0.0175);
			buf[(83 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * i) * 0.0175);
			buf[(84 + i * nn) + jIter * n * nn] = 0.0;
			buf[(85 + i * nn) + jIter * n * nn] = 0.0;
			buf[(86 + i * nn) + jIter * n * nn] = 0.0;
			buf[(87 + i * nn) + jIter * n * nn] = 1.0;
			buf[(88 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(89 + i * nn) + jIter * n * nn] = yTex;

			buf[(90 + i * nn) + jIter * n * nn] = xleft;
			buf[(91 + i * nn) + jIter * n * nn] = 0.68f * sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(92 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(93 + i * nn) + jIter * n * nn] = 0.0;
			buf[(94 + i * nn) + jIter * n * nn] = 0.0;
			buf[(95 + i * nn) + jIter * n * nn] = 0.0;
			buf[(96 + i * nn) + jIter * n * nn] = 1.0;
			buf[(97 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(98 + i * nn) + jIter * n * nn] = yTex2;

			buf[(99 + i * nn) + jIter * n * nn] = xright;
			buf[(100 + i * nn) + jIter * n * nn] = 0.68f * sin((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(101 + i * nn) + jIter * n * nn] = 0.68f * cos((30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(102 + i * nn) + jIter * n * nn] = 0.0;
			buf[(103 + i * nn) + jIter * n * nn] = 0.0;
			buf[(104 + i * nn) + jIter * n * nn] = 0.0;
			buf[(105 + i * nn) + jIter * n * nn] = 1.0;
			buf[(106 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(107 + i * nn) + jIter * n * nn] = yTex2;
			
			//front down
			yTex = 1 - (float)i / n;
			yTex2 = 1 - (float)(i + 1) / n;

			buf[(108 + i * nn) + jIter * n * nn] = xleft;
			buf[(109 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(110 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(111 + i * nn) + jIter * n * nn] = 0.0;
			buf[(112 + i * nn) + jIter * n * nn] = 0.0;
			buf[(113 + i * nn) + jIter * n * nn] = 0.0;
			buf[(114 + i * nn) + jIter * n * nn] = 1.0;
			buf[(115 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(116 + i * nn) + jIter * n * nn] = yTex;

			buf[(117 + i * nn) + jIter * n * nn] = xleft;
			buf[(118 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(119 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(120 + i * nn) + jIter * n * nn] = 0.0;
			buf[(121 + i * nn) + jIter * n * nn] = 0.0;
			buf[(122 + i * nn) + jIter * n * nn] = 0.0;
			buf[(123 + i * nn) + jIter * n * nn] = 1.0;
			buf[(124 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(125 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(126 + i * nn) + jIter * n * nn] = xright;
			buf[(127 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(128 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(129 + i * nn) + jIter * n * nn] = 0.0;
			buf[(130 + i * nn) + jIter * n * nn] = 0.0;
			buf[(131 + i * nn) + jIter * n * nn] = 0.0;
			buf[(132 + i * nn) + jIter * n * nn] = 1.0;
			buf[(133 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(134 + i * nn) + jIter * n * nn] = yTex;

			buf[(135 + i * nn) + jIter * n * nn] = xright;
			buf[(136 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(137 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * i) * 0.0175);
			buf[(138 + i * nn) + jIter * n * nn] = 0.0;
			buf[(139 + i * nn) + jIter * n * nn] = 0.0;
			buf[(140 + i * nn) + jIter * n * nn] = 0.0;
			buf[(141 + i * nn) + jIter * n * nn] = 1.0;
			buf[(142 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(143 + i * nn) + jIter * n * nn] = yTex;

			buf[(144 + i * nn) + jIter * n * nn] = xleft;
			buf[(145 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(146 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(147 + i * nn) + jIter * n * nn] = 0.0;
			buf[(148 + i * nn) + jIter * n * nn] = 0.0;
			buf[(149 + i * nn) + jIter * n * nn] = 0.0;
			buf[(150 + i * nn) + jIter * n * nn] = 1.0;
			buf[(151 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(152 + i * nn) + jIter * n * nn] = yTex2;

			buf[(153 + i * nn) + jIter * n * nn] = xright;
			buf[(154 + i * nn) + jIter * n * nn] = 0.68f * sin((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(155 + i * nn) + jIter * n * nn] = 0.68f * cos((-30.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(156 + i * nn) + jIter * n * nn] = 0.0;
			buf[(157 + i * nn) + jIter * n * nn] = 0.0;
			buf[(158 + i * nn) + jIter * n * nn] = 0.0;
			buf[(159 + i * nn) + jIter * n * nn] = 1.0;
			buf[(160 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(161 + i * nn) + jIter * n * nn] = yTex2;

			//backup
			yTex = 1 - (float)i / n;
			yTex2 = 1 - (float)(i + 1) / n;

			buf[(162 + i * nn) + jIter * n * nn] = xleft;
			buf[(163 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(164 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(165 + i * nn) + jIter * n * nn] = 0.0;
			buf[(166 + i * nn) + jIter * n * nn] = 0.0;
			buf[(167 + i * nn) + jIter * n * nn] = 0.0;
			buf[(168 + i * nn) + jIter * n * nn] = 1.0;
			buf[(169 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(170 + i * nn) + jIter * n * nn] = yTex;

			buf[(171 + i * nn) + jIter * n * nn] = xleft;
			buf[(172 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(173 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(174 + i * nn) + jIter * n * nn] = 0.0;
			buf[(175 + i * nn) + jIter * n * nn] = 0.0;
			buf[(176 + i * nn) + jIter * n * nn] = 0.0;
			buf[(177 + i * nn) + jIter * n * nn] = 1.0;
			buf[(178 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(179 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(180 + i * nn) + jIter * n * nn] = xright;
			buf[(181 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(182 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(183 + i * nn) + jIter * n * nn] = 0.0;
			buf[(184 + i * nn) + jIter * n * nn] = 0.0;
			buf[(185 + i * nn) + jIter * n * nn] = 0.0;
			buf[(186 + i * nn) + jIter * n * nn] = 1.0;
			buf[(187 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(188 + i * nn) + jIter * n * nn] = yTex;

			buf[(189 + i * nn) + jIter * n * nn] = xright;
			buf[(190 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * i) * 0.0175);
			buf[(191 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * i) * 0.0175);
			buf[(192 + i * nn) + jIter * n * nn] = 0.0;
			buf[(193 + i * nn) + jIter * n * nn] = 0.0;
			buf[(194 + i * nn) + jIter * n * nn] = 0.0;
			buf[(195 + i * nn) + jIter * n * nn] = 1.0;
			buf[(196 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(197 + i * nn) + jIter * n * nn] = yTex;

			buf[(198 + i * nn) + jIter * n * nn] = xleft;
			buf[(199 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(200 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(201 + i * nn) + jIter * n * nn] = 0.0;
			buf[(202 + i * nn) + jIter * n * nn] = 0.0;
			buf[(203 + i * nn) + jIter * n * nn] = 0.0;
			buf[(204 + i * nn) + jIter * n * nn] = 1.0;
			buf[(205 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(206 + i * nn) + jIter * n * nn] = yTex2;

			buf[(207 + i * nn) + jIter * n * nn] = xright;
			buf[(208 + i * nn) + jIter * n * nn] = 0.68f * sin((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(209 + i * nn) + jIter * n * nn] = 0.68f * cos((150.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(210 + i * nn) + jIter * n * nn] = 0.0;
			buf[(211 + i * nn) + jIter * n * nn] = 0.0;
			buf[(212 + i * nn) + jIter * n * nn] = 0.0;
			buf[(213 + i * nn) + jIter * n * nn] = 1.0;
			buf[(214 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(215 + i * nn) + jIter * n * nn] = yTex2;

			//backmiddle

			yTex = 1 - (float)i / n;
			yTex2 = 1 - (float)(i + 1) / n;

			buf[(216 + i * nn) + jIter * n * nn] = xleft;
			buf[(217 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(218 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(219 + i * nn) + jIter * n * nn] = 0.0;
			buf[(220 + i * nn) + jIter * n * nn] = 0.0;
			buf[(221 + i * nn) + jIter * n * nn] = 0.0;
			buf[(222 + i * nn) + jIter * n * nn] = 1.0;
			buf[(223 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(224 + i * nn) + jIter * n * nn] = yTex;

			buf[(225 + i * nn) + jIter * n * nn] = xleft;
			buf[(226 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(227 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(228 + i * nn) + jIter * n * nn] = 0.0;
			buf[(229 + i * nn) + jIter * n * nn] = 0.0;
			buf[(230 + i * nn) + jIter * n * nn] = 0.0;
			buf[(231 + i * nn) + jIter * n * nn] = 1.0;
			buf[(232 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(233 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(234 + i * nn) + jIter * n * nn] = xright;
			buf[(235 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(236 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(237 + i * nn) + jIter * n * nn] = 0.0;
			buf[(238 + i * nn) + jIter * n * nn] = 0.0;
			buf[(239 + i * nn) + jIter * n * nn] = 0.0;
			buf[(240 + i * nn) + jIter * n * nn] = 1.0;
			buf[(241 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(242 + i * nn) + jIter * n * nn] = yTex;

			buf[(243 + i * nn) + jIter * n * nn] = xright;
			buf[(244 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * i) * 0.0175);
			buf[(245 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * i) * 0.0175);
			buf[(246 + i * nn) + jIter * n * nn] = 0.0;
			buf[(247 + i * nn) + jIter * n * nn] = 0.0;
			buf[(248 + i * nn) + jIter * n * nn] = 0.0;
			buf[(249 + i * nn) + jIter * n * nn] = 1.0;
			buf[(250 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(251 + i * nn) + jIter * n * nn] = yTex;

			buf[(252 + i * nn) + jIter * n * nn] = xleft;
			buf[(253 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(254 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(255 + i * nn) + jIter * n * nn] = 0.0;
			buf[(256 + i * nn) + jIter * n * nn] = 0.0;
			buf[(257 + i * nn) + jIter * n * nn] = 0.0;
			buf[(258 + i * nn) + jIter * n * nn] = 1.0;
			buf[(259 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(260 + i * nn) + jIter * n * nn] = yTex2;

			buf[(261 + i * nn) + jIter * n * nn] = xright;
			buf[(262 + i * nn) + jIter * n * nn] = 0.68f * sin((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(263 + i * nn) + jIter * n * nn] = 0.68f * cos((210.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(264 + i * nn) + jIter * n * nn] = 0.0;
			buf[(265 + i * nn) + jIter * n * nn] = 0.0;
			buf[(266 + i * nn) + jIter * n * nn] = 0.0;
			buf[(267 + i * nn) + jIter * n * nn] = 1.0;
			buf[(268 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(269 + i * nn) + jIter * n * nn] = yTex2;

			/*back down*/
			yTex = 1 - (float)i / n;
			yTex2 = 1 - (float)(i + 1) / n;

			buf[(270 + i * nn) + jIter * n * nn] = xleft;
			buf[(271 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(272 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(273 + i * nn) + jIter * n * nn] = 0.0;
			buf[(274 + i * nn) + jIter * n * nn] = 0.0;
			buf[(275 + i * nn) + jIter * n * nn] = 0.0;
			buf[(276 + i * nn) + jIter * n * nn] = 1.0;
			buf[(277 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(278 + i * nn) + jIter * n * nn] = yTex;

			buf[(279 + i * nn) + jIter * n * nn] = xleft;
			buf[(280 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(281 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(282 + i * nn) + jIter * n * nn] = 0.0;
			buf[(283 + i * nn) + jIter * n * nn] = 0.0;
			buf[(284 + i * nn) + jIter * n * nn] = 0.0;
			buf[(285 + i * nn) + jIter * n * nn] = 1.0;
			buf[(286 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(287 + i * nn) + jIter * n * nn] = yTex2;//yTex2

			buf[(288 + i * nn) + jIter * n * nn] = xright;
			buf[(289 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(290 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(291 + i * nn) + jIter * n * nn] = 0.0;
			buf[(292 + i * nn) + jIter * n * nn] = 0.0;
			buf[(293 + i * nn) + jIter * n * nn] = 0.0;
			buf[(294 + i * nn) + jIter * n * nn] = 1.0;
			buf[(295 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(296 + i * nn) + jIter * n * nn] = yTex;

			buf[(297 + i * nn) + jIter * n * nn] = xright;
			buf[(298 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(299 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * i) * 0.0175);
			buf[(300 + i * nn) + jIter * n * nn] = 0.0;
			buf[(301 + i * nn) + jIter * n * nn] = 0.0;
			buf[(302 + i * nn) + jIter * n * nn] = 0.0;
			buf[(303 + i * nn) + jIter * n * nn] = 1.0;
			buf[(304 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(305 + i * nn) + jIter * n * nn] = yTex;

			buf[(306 + i * nn) + jIter * n * nn] = xleft;
			buf[(307 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(308 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(309 + i * nn) + jIter * n * nn] = 0.0;
			buf[(310 + i * nn) + jIter * n * nn] = 0.0;
			buf[(311 + i * nn) + jIter * n * nn] = 0.0;
			buf[(312 + i * nn) + jIter * n * nn] = 1.0;
			buf[(313 + i * nn) + jIter * n * nn] = 0.0;//1.0
			buf[(314 + i * nn) + jIter * n * nn] = yTex2;

			buf[(315 + i * nn) + jIter * n * nn] = xright;
			buf[(316 + i * nn) + jIter * n * nn] = 0.68f * sin((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(317 + i * nn) + jIter * n * nn] = 0.68f * cos((-90.0 - 60.0 / n * (i + 1)) * 0.0175);
			buf[(318 + i * nn) + jIter * n * nn] = 0.0;
			buf[(319 + i * nn) + jIter * n * nn] = 0.0;
			buf[(320 + i * nn) + jIter * n * nn] = 0.0;
			buf[(321 + i * nn) + jIter * n * nn] = 1.0;
			buf[(322 + i * nn) + jIter * n * nn] = 1.0;//0.0
			buf[(323 + i * nn) + jIter * n * nn] = yTex2;//287
		}
		jIter++;
	}
	//GLuint buffer;
	f->glGenVertexArrays(1, &vao);
	f->glGenBuffers(1, &buffer);
	f->glBindVertexArray(vao);
	f->glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//f->glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
	f->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nn * n * 5, buf, GL_STATIC_DRAW);

	GLuint  indices_[] = {
	0,1,2,
	3,4,5,
	6,7,8,
	9,10,11
	};// Note that we start from 0!
	for (int i = 0; i < 36 * n; i++)
		indices[i] = (GLuint)i;
	GLuint EBO;
	f->glGenBuffers(1, &EBO);
	f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 60, indices, GL_STATIC_DRAW);
	// Position attribute
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	f->glEnableVertexAttribArray(0);
	// Color attribute
	f->glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	f->glEnableVertexAttribArray(1);
	// TexCoord attribute
	f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	f->glEnableVertexAttribArray(2);
	f->glEnableVertexAttribArray(0);
	f->glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	f->glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs
	//Game loop
	//f = QOpenGLContext::currentContext()->functions();
	glClearColor(0, 0, 0, 0); // заполн€ем экран белым цветом
	//glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
	//glShadeModel(GL_FLAT); // убираем режим сглаживани€ цветов
	//glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
	//gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	image1.load("content//drum//auto1.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат дл€ работы с OpenGL:
	texture = new QOpenGLTexture(image1.mirrored());
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image1.width(), image1.height(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, image1.bits());
	image1.load("content//drum//auto2.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат дл€ работы с OpenGL:
	texture2 = new QOpenGLTexture(image1.mirrored());
	texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture2->setMagnificationFilter(QOpenGLTexture::Linear);
	glGenTextures(1, &id2);
	glBindTexture(GL_TEXTURE_2D, id2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image1.width(), image1.height(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, image1.bits());
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	
}
void Scene1::ShowDrum(QOpenGLExtraFunctions* f, GLuint shaderProgram)
{
	glEnable(GL_DEPTH_TEST);
	f->glUseProgram(shaderProgram);
	//f->glBindBuffer(GL_ARRAY_BUFFER, buffer);
	f->glBindVertexArray(vao);
	//f->glDrawArrays(GL_TRIANGLES, 0, 6);
	GLfloat trans[16] =
	{
		1.0,0.0,0.0,0.0,
		0.0,1.0 * cos(rotate__ * 0.0175),0.0 - sin(rotate__ * 0.0175),0.0,
		0.0,0.0 + sin(rotate__ * 0.0175),1.0 * cos(rotate__ * 0.0175),0.0,
		0.0,0.0,0.0,1.0
	};
	if(b)
		rotate__ += 1;
	if (rotate__ >= 360)
	{
		rotate__ = 0;
		b = false;
	}
	unsigned int transformLoc = f->glGetUniformLocation(shaderProgram, "transform");
	f->glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	for (int j = 0; j < 5; j++)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i, 6/* 36 * 10 * 5*/);
		glBindTexture(GL_TEXTURE_2D, id2);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i + 6, 6/* 36 * 10 * 5*/);
		glBindTexture(GL_TEXTURE_2D, id);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i + 12, 6/* 36 * 10 * 5*/);
		glBindTexture(GL_TEXTURE_2D, id2);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i + 18, 6/* 36 * 10 * 5*/);
		glBindTexture(GL_TEXTURE_2D, id);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i + 24, 6/* 36 * 10 * 5*/);
		glBindTexture(GL_TEXTURE_2D, id2);
		for (int i = 0 + j * 10; i < 10 + j * 10; i++)
			f->glDrawArrays(GL_TRIANGLES, 36 * i + 30, 6/* 36 * 10 * 5*/);
	}
	//glBindTexture(GL_TEXTURE_2D, id2);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//f->glDrawArrays(GL_TRIANGLES, 6, 6);
	//f->glBindVertexArray(0);
	//glDisable(GL_DEPTH_TEST);
	GLfloat trans2[16] =
	{
		1.0,0.0,0.0,0.0,
		0.0,1.0 /** cos(-rotate__ * 0.0175)*/,0.0/* - sin(-rotate__ * 0.0175)*/,0.0,
		0.0,0.0 /* + sin(-rotate__ * 0.0175) */ ,1.0/* * cos(-rotate__ * 0.0175)*/,0.0,
		0.0,0.0,0.0,1.0
	};
	f->glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans2);
	f->glBindVertexArray(0);
}

void Scene1::LoadBorder(QOpenGLExtraFunctions* f)
{
	float buf2[] =
	{// x,	y,	z,	r,	g,	b,	s,	t
			-1.0,  1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			-1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
			 1.0,  1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
			 1.0,  1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
			-1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
			 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0
	};
	//	GLuint buffer2;
	f->glGenVertexArrays(1, &vao2);
	f->glGenBuffers(1, &buffer2);
	f->glBindVertexArray(vao2);
	f->glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	f->glBufferData(GL_ARRAY_BUFFER, sizeof(buf2), buf2, GL_STATIC_DRAW);
	indices_2 = new GLuint[6];
	for (int i = 0; i < 6; i++)
		indices_2[i] = (GLuint)i;
	GLuint EBO2;
	f->glGenBuffers(1, &EBO2);
	f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_2), indices_2, GL_STATIC_DRAW);
	// Position attribute
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	f->glEnableVertexAttribArray(0);
	// Color attribute
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	f->glEnableVertexAttribArray(1);
	// TexCoord attribute
	f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	f->glEnableVertexAttribArray(2);
	f->glEnableVertexAttribArray(0);
	f->glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	f->glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs
	image2.load("content//border.png"); // загружаем изображение в переменную image1
	// конвертируем изображение в формат дл€ работы с OpenGL:
	texture3 = new QOpenGLTexture(image2.mirrored());
	texture3->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture3->setMagnificationFilter(QOpenGLTexture::Linear);
	glGenTextures(1, &id3);
	glBindTexture(GL_TEXTURE_2D, id3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image2.width(), image2.height(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, image2.bits());
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Scene1::ShowBorder(QOpenGLExtraFunctions* f, GLuint shaderProgram)
{
	f->glUseProgram(shaderProgram);
	//f->glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	f->glBindVertexArray(vao2);
	glBindTexture(GL_TEXTURE_2D, id3);

	//glEnable(GL_BLEND);

	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_BLEND);
	f->glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	f->glBindVertexArray(0);
}
Scene1::~Scene1()
{
	for (int i = 0; i<CountTexture; i++)
		delete[] image->VertexCoordinats[i];
	for (int i = 0; i<CountTexture; i++)
		image[i].Name.clear();
	delete[] image->VertexCoordinats;
#if WINAPI_==1 || SDLAPI_==1
	delete image->IndexTexture;
#endif
	delete image->number;
	delete image;
	delete rotate;
	delete startrotate;
	flogout.close();
}
