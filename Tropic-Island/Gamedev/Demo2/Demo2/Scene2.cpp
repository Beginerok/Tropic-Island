#include "Scene2.h"
Scene2::Scene2()
{
	CountTexture = 79;//+1+3
	NewTextureCoordinats=new float*[CountTexture];
	NewVertexCoordinats=new float*[CountTexture];
	for(int i=0;i<CountTexture;i++)
	{
		NewTextureCoordinats[i]=new float[4];
		NewVertexCoordinats[i]=new float[4];
	}

#if SDLAPI_==1 || WINAPI_==1
	IndexTexture = new unsigned int[CountTexture];
#endif
	CountIndexTexture = 0;
	//SetData();
	num_ = new char[25];
	loading = false;
	image = new Image2(); 
	image->VertexCoordinats = new float* [CountTexture];
	for (int i = 0; i < CountTexture; i++)
		image->VertexCoordinats[i] = new float[4];
}
#if QTAPI_==1
QOpenGLTexture* Scene2::QTLoadImage(QString path)
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
void Scene2::LoadImage(const ILstring path)
{
	/*
	std::ofstream out;          // ����� ��� ������
	out.open("scene2.txt", std::ios::app); // �������� ���� ��� ������
	if (out.is_open())
	{
		out << reinterpret_cast<const char*>(path)<< std::endl;

		image->VertexCoordinats[CountIndexTexture - 1][0] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][1] = -1.f;
		image->VertexCoordinats[CountIndexTexture - 1][2] = 1.f;
		image->VertexCoordinats[CountIndexTexture - 1][3] = -1.f;
		out << image->VertexCoordinats[CountIndexTexture - 1][0] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][1] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][2] << std::endl;
		out << image->VertexCoordinats[CountIndexTexture - 1][3] << std::endl;
		out << 0 << std::endl;
		out << 0 << std::endl;
		out.close();
	}
	*/
	ILenum ext;

	if (strstr(reinterpret_cast<const char*>(path), "png"))
	{
		ext = IL_PNG;
	}
	if (strstr(reinterpret_cast<const char*>(path), "jpg") || strstr(reinterpret_cast<const char*>(path), "jpeg"))
	{
		ext = IL_JPG;
	}
	if (strstr(reinterpret_cast<const char*>(path), "bmp"))
	{
		ext = IL_BMP;
	}
	//#ifdef _WINDOWS_2
	ilLoad(ext, reinterpret_cast<const ILstring>(path));
	//#else
		//ilLoad( ext, path);
	//#endif
		// ��������� ���� ������
	err = ilGetError();
	// ���� ��� �� ����� ���� ������ ����
	if (err != IL_NO_ERROR) {
		// ��������� ������ � �������
		strError = (wchar_t*)iluErrorString(err);
		// ������ ��������� �� ������
#ifdef _WIN32
		std::cout << "\nNot find file: ";
		std::wcout << path << std::endl;
		MessageBox(NULL, NULL, L"������ ��� �������� il!", MB_OK);
#endif
		// ����� �� ���������
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
	// ������ ��������
	copyData = ilGetData();
	IndexTexture[CountIndexTexture] = 0;
	glGenTextures(1, &IndexTexture[CountIndexTexture]);
	iluFlipImage();


	glBindTexture(GL_TEXTURE_2D, IndexTexture[CountIndexTexture]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	CountIndexTexture++;
};
void Scene2::SetData()
{
	
	if(loading)
		return;

	CountIndexTexture++;

    LoadImage(reinterpret_cast<const ILstring>("content//woman.jpg"));
	LoadImage(reinterpret_cast<const ILstring>("content//background5.jpg"));
	//3
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//diamonds//diamonds-t.png"));
	//15
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//clubs//clubs-t.png"));
	//28
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//spades//spades-t.png"));
	//42
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//cards//hearts//hearts-t.png"));
	//55

	NewTextureCoordinats[0][0]=1.f;
	NewTextureCoordinats[0][1]=.0f;
	NewTextureCoordinats[0][2]=1.f;
	NewTextureCoordinats[0][3]=.0f;

	NewVertexCoordinats[0][0]=1.f;
    NewVertexCoordinats[0][1]=-1.f;
    NewVertexCoordinats[0][2]=1.f;
    NewVertexCoordinats[0][3]=-1.f;
	/*
	std::ofstream out;          // ����� ��� ������
	out.open("scene2.txt", std::ios::app); // �������� ���� ��� ������
	if (out.is_open())
	{

		*/

		for (int i = 1; i < 6; i++)
		{
			NewVertexCoordinats[i][0] = -.6f + (i - 1) * .3f + (i - 1) * .075f;
			NewVertexCoordinats[i][1] = -.9f + (i - 1) * .3f + (i - 1) * .075f;
			NewVertexCoordinats[i][2] = 0.f;
			NewVertexCoordinats[i][3] = -.8f;

			/*
			out << NewVertexCoordinats[i][0] << std::endl;
			out << NewVertexCoordinats[i][1] << std::endl;
			out << NewVertexCoordinats[i][2] << std::endl;
			out << NewVertexCoordinats[i][3] << std::endl;
			*/
		}
		/*
		out.close();
	}
	*/
    LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP_PRESS.png"));
	//59
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//CREDITS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//WIN.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//TOTAL_BET.png"));
	//62
	NewVertexCoordinats[60][0] = -.6f;
	NewVertexCoordinats[60][1] = -.9f;
	NewVertexCoordinats[60][2] = .8f;
	NewVertexCoordinats[60][3] = .6f;

	NewVertexCoordinats[61][0] = .1f;
	NewVertexCoordinats[61][1] = -.1f;
	NewVertexCoordinats[61][2] = .8f;
	NewVertexCoordinats[61][3] = .6f;

	NewVertexCoordinats[62][0] = .7f;
	NewVertexCoordinats[62][1] = .4f;
	NewVertexCoordinats[62][2] = .8f;
	NewVertexCoordinats[62][3] = .6f;
	//63
    LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//0.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//1.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//numbers_and_words//9.png"));
	//72
	NewVertexCoordinats[63][0] = -.5f;
	NewVertexCoordinats[63][1] = -.55f;
	NewVertexCoordinats[63][2] = .8f;
	NewVertexCoordinats[63][3] = .6f;

	NewVertexCoordinats[64][0] = .2f;
	NewVertexCoordinats[64][1] = .15f;
	NewVertexCoordinats[64][2] = .8f;
	NewVertexCoordinats[64][3] = .6f;

	NewVertexCoordinats[65][0] = .8f;
	NewVertexCoordinats[65][1] = .75f;
	NewVertexCoordinats[65][2] = .8f;
	NewVertexCoordinats[65][3] = .6f;
	loading = true;
	
}

#endif
#if QTAPI_==1
void Scene2::LoadQT()
{
	std::ifstream in("scene2_norm.txt");
	Image_s2 im;
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
			im.number = scene2v.size();
			scene2v.push_back(im);
		}
	}
	in.close();
}
#endif
int Scene2::FindTexture(std::string name, std::vector<Image_s2> vec)
{
	int result = -1, size = vec.size();
	for (int i = 0; i < size; i++)
		if (strcmp(vec[i].Name.c_str(), name.c_str()) == 0)
		{
			result = i;
			break;
		}
	return result;
}
void Scene2::EnableTexture(Image_s2 im, bool third, bool alpha)
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
void Scene2::ShowBackGround(bool *GetFA,int *random_,int GetCredits, int GetWin, int GetTotalBet)
{
	int numb;
#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, IndexTexture[1]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[0]);
#elif QTAPI_==1
	numb = FindTexture("woman", scene2v);
	EnableTexture(scene2v[numb], true, true);
#endif
	
	NewTextureCoordinats[0][0]=1.f;
	NewTextureCoordinats[0][1]=.0f;
	NewTextureCoordinats[0][2]=1.f;
	NewTextureCoordinats[0][3]=.0f;
	for (int i = 1; i < 6; i++)
	{
		NewVertexCoordinats[i][0] = -.6f + (i - 1) * .3f + (i - 1) * .075f;
		NewVertexCoordinats[i][1] = -.9f + (i - 1) * .3f + (i - 1) * .075f;
		NewVertexCoordinats[i][2] = 0.f;
		NewVertexCoordinats[i][3] = -.8f;
	}
#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[0]]);
#elif QTAPI_==1
	numb = random_[0] - 1;
	scene2v[numb].IndexTexture->bind();
#endif
	EnableTexture(NewTextureCoordinats[0],NewVertexCoordinats[1]);

	if (GetFA[6] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
#elif QTAPI_==1
	numb = FindTexture("background5",scene2v);
	scene2v[numb].IndexTexture->bind();
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[1]]);
#elif QTAPI_==1
		numb = random_[1] - 1;
		scene2v[numb].IndexTexture->bind();
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	if (GetFA[7] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
#elif QTAPI_==1
		numb = FindTexture("background5", scene2v);
		scene2v[numb].IndexTexture->bind();

#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[2]]);
#elif QTAPI_==1
		numb = random_[2] - 1;
		scene2v[numb].IndexTexture->bind();
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	if (GetFA[8] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
#elif QTAPI_==1
		numb = FindTexture("background5", scene2v);
		scene2v[numb].IndexTexture->bind();

#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[3]]);
#elif QTAPI_==1
		numb = random_[3] - 1;
		scene2v[numb].IndexTexture->bind();
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	if (GetFA[9] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
#elif QTAPI_==1
		numb = FindTexture("background5", scene2v);
		scene2v[numb].IndexTexture->bind();

#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[4]]);
#elif QTAPI_==1
		numb = random_[4] - 1;
		scene2v[numb].IndexTexture->bind();
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	/*
	if (GetFA[5] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[55]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[1]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[56]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[1]);
	}
	
	if (GetFA[6] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	if (GetFA[7] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	if (GetFA[8] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	if (GetFA[9] != true)
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}
	else
	{
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}
	*/

	NewVertexCoordinats[60][0] = -.6f;
	NewVertexCoordinats[60][1] = -.9f;
	NewVertexCoordinats[60][2] = .8f;
	NewVertexCoordinats[60][3] = .6f;

	NewVertexCoordinats[61][0] = .1f;
	NewVertexCoordinats[61][1] = -.1f;
	NewVertexCoordinats[61][2] = .8f;
	NewVertexCoordinats[61][3] = .6f;

	NewVertexCoordinats[62][0] = .7f;
	NewVertexCoordinats[62][1] = .4f;
	NewVertexCoordinats[62][2] = .8f;
	NewVertexCoordinats[62][3] = .6f;
#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, IndexTexture[59]);
#elif QTAPI_==1
	numb = FindTexture("CREDITS",scene2v);
	scene2v[numb].IndexTexture->bind();
#endif
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[60]);

#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, IndexTexture[60]);
#elif QTAPI_==1
	numb = FindTexture("WIN", scene2v);
	scene2v[numb].IndexTexture->bind();
#endif
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[61]);

#if SDLAPI_==1 || WINAPI_==1
	glBindTexture(GL_TEXTURE_2D, IndexTexture[61]);
#elif QTAPI_==1
	numb = FindTexture("TOTAL_BET", scene2v);
	scene2v[numb].IndexTexture->bind();
#endif
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[62]);
	
	NewVertexCoordinats[63][0] = -.5f;
	NewVertexCoordinats[63][1] = -.55f;
	NewVertexCoordinats[63][2] = .8f;
	NewVertexCoordinats[63][3] = .6f;

	NewVertexCoordinats[64][0] = .2f;
	NewVertexCoordinats[64][1] = .15f;
	NewVertexCoordinats[64][2] = .8f;
	NewVertexCoordinats[64][3] = .6f;

	NewVertexCoordinats[65][0] = .8f;
	NewVertexCoordinats[65][1] = .75f;
	NewVertexCoordinats[65][2] = .8f;
	NewVertexCoordinats[65][3] = .6f;
	DrawNumeric(GetCredits, 0);
	DrawNumeric(GetWin, 1);
	DrawNumeric(GetTotalBet, 2);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void Scene2::DrawNumeric(int num,int position)
{
	std::string str = "";
#ifndef _WIN32
	sprintf(num_,"%d",num);
#else
	sprintf_s(num_,25,"%d",num);
#endif
	int n = strlen(num_);
	for (int j = 0; j < n; j++) {
		str += num_[j];
#if SDLAPI_==1 || WINAPI_==1
		glBindTexture(GL_TEXTURE_2D, IndexTexture[62 + str[j] - '0']);
#elif QTAPI_==1
		int numb = FindTexture(std::to_string(str[j]-'0'), scene2v);
		scene2v[numb].IndexTexture->bind();

#endif
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[63 + position], j);
	}
}
void Scene2::EnableTexture(float*texcoor, float*vercoor)
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
void Scene2::EnableTexture(float*texcoor, float*vercoor,int dx)
{
	glBegin(GL_QUADS);
	glTexCoord2f(texcoor[0], texcoor[2]);
	glVertex2f(vercoor[0] + dx*abs(vercoor[1] - vercoor[0]), vercoor[2]);
	glTexCoord2f(texcoor[1], texcoor[2]);
	glVertex2f(vercoor[1] + dx*abs(vercoor[1] - vercoor[0]), vercoor[2]);
	glTexCoord2f(texcoor[1], texcoor[3]);
	glVertex2f(vercoor[1] + dx*abs(vercoor[1] - vercoor[0]), vercoor[3]);
	glTexCoord2f(texcoor[0], texcoor[3]);
	glVertex2f(vercoor[0] + dx*abs(vercoor[1] - vercoor[0]), vercoor[3]);
	glEnd();
}

void Scene2::Destroy()
{
    for(int i=0;i<CountTexture;i++)
        delete[] NewTextureCoordinats[i];
    delete[] NewTextureCoordinats;
    for(int i=0;i<CountTexture;i++)
        delete[] NewVertexCoordinats[i];
    delete[] NewVertexCoordinats;
#if QTAPI_==1

#elif SDLAPI_==1 || WINAPI_==1
	for (int i = 0; i < CountTexture; i++)
		delete[] image->VertexCoordinats[i];
	delete[] image->VertexCoordinats;
	delete image->IndexTexture;
	delete IndexTexture;
#endif
	delete num_;
	delete image;
}
