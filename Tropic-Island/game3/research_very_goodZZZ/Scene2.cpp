#include "Scene2.h"
Scene2::Scene2()
{
	CountTexture = 79;//+1+3
	NewTextureCoordinats=new float__*[CountTexture];
	NewVertexCoordinats=new float__*[CountTexture];
	for(int__ i=0;i<CountTexture;i++)
	{
		NewTextureCoordinats[i]=new float__[4];
		NewVertexCoordinats[i]=new float__[4];
	}
	IndexTexture = new uint__[CountTexture];
	CountIndexTexture = 0;
	//SetData();
	num_ = new char__[25];
	loading = false;
}
void__ Scene2::LoadImage(const ILstring path)
{
	ILenum ext;

	if(strstr(reinterpret_cast<const char*>(path),"png"))
	{
		ext=IL_PNG;
	}
	if(strstr(reinterpret_cast<const char*>(path),"jpg") || strstr(reinterpret_cast<const char*>(path),"jpeg"))
	{
		ext=IL_JPG;
	}
	if(strstr(reinterpret_cast<const char*>(path),"bmp"))
	{
		ext=IL_BMP;
	}
//#ifdef _WINDOWS_2
	ilLoad( ext, reinterpret_cast<const ILstring>(path));
//#else
	//ilLoad( ext, path);
//#endif
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
	IndexTexture[CountIndexTexture] = 0;
	glGenTextures(1, &IndexTexture[CountIndexTexture]);
	iluFlipImage();


	glBindTexture(GL_TEXTURE_2D, IndexTexture[CountIndexTexture]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	CountIndexTexture++;
};
void__ Scene2::SetData()
{
	if(loading)
		return;
	CountIndexTexture++;
#ifdef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content\\woman.jpg"));
	LoadImage(reinterpret_cast<const ILstring>("content\\background5.jpg"));
	//3
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\diamonds\\diamonds-t.png"));
	//15
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\clubs\\clubs-t.png"));
	//28
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\spades\\spades-t.png"));
	//42
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-9.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-10.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-v.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-d.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-k.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\cards\\hearts\\hearts-t.png"));
	//55
#else
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
#endif
	NewTextureCoordinats[0][0]=1.f;
	NewTextureCoordinats[0][1]=.0f;
	NewTextureCoordinats[0][2]=1.f;
	NewTextureCoordinats[0][3]=.0f;

	NewVertexCoordinats[0][0]=1.f;
    NewVertexCoordinats[0][1]=-1.f;
    NewVertexCoordinats[0][2]=1.f;
    NewVertexCoordinats[0][3]=-1.f;

	for(int__ i=1;i<6;i++)
	{
		NewVertexCoordinats[i][0]=-.6f+(i-1)*.3f+(i-1)*.075f;
		NewVertexCoordinats[i][1]=-.9f+(i-1)*.3f+(i-1)*.075f;
		NewVertexCoordinats[i][2]=0.f;
		NewVertexCoordinats[i][3]=-.8f;
	}
	/*
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\HELP.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\HELP_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\TAKE.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\TAKE_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\PLAY.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\PLAY_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\BET.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\BET_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\EXIT.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\КНОПКИ\\EXIT_PRESS.png"));
	*/
#ifdef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\TAKE.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\TAKE_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\FLIP.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\FLIP_PRESS.png"));
	//59
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\CREDITS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\WIN.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\TOTAL_BET.png"));
	//62
#else
    LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//TAKE_PRESS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//FLIP_PRESS.png"));
	//59
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//CREDITS.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//WIN.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//TOTAL_BET.png"));
	//62
#endif
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
#ifdef _WINDOWS_2
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\0.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\1.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content\\buttons\\9.png"));
	//72
#else
    LoadImage(reinterpret_cast<const ILstring>("content//buttons//0.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//1.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//2.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//3.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//4.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//5.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//6.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//7.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//8.png"));
	LoadImage(reinterpret_cast<const ILstring>("content//buttons//9.png"));
	//72
#endif
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
void__ Scene2::ShowBackGround(bool__ *GetFA,int__ *random_,int__ GetCredits, int__ GetWin, int__ GetTotalBet)
{
	glBindTexture(GL_TEXTURE_2D, IndexTexture[1]);
	EnableTexture(NewTextureCoordinats[0],NewVertexCoordinats[0]);

	glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[0]]);
	EnableTexture(NewTextureCoordinats[0],NewVertexCoordinats[1]);

	if (GetFA[0] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[1]]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	if (GetFA[2] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[2]]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	if (GetFA[3] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[3]]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	if (GetFA[4] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[2]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[random_[4]]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	/*
	glBindTexture(GL_TEXTURE_2D, IndexTexture[56]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[1]);
	glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	glBindTexture(GL_TEXTURE_2D, IndexTexture[60]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	glBindTexture(GL_TEXTURE_2D, IndexTexture[62]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	glBindTexture(GL_TEXTURE_2D, IndexTexture[64]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	*/
	if (GetFA[1] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[55]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[1]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[56]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[1]);
	}
	if (GetFA[0] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[2]);
	}
	if (GetFA[2] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[3]);
	}
	if (GetFA[3] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[4]);
	}
	if (GetFA[4] != true)
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[57]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, IndexTexture[58]);
		EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[5]);
	}

	glBindTexture(GL_TEXTURE_2D, IndexTexture[59]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[60]);

	glBindTexture(GL_TEXTURE_2D, IndexTexture[60]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[61]);

	glBindTexture(GL_TEXTURE_2D, IndexTexture[61]);
	EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[62]);

	DrawNumeric(GetCredits, 0);
	DrawNumeric(GetWin, 1);
	DrawNumeric(GetTotalBet, 2);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void__ Scene2::DrawNumeric(int__ num,int__ position)
{
	//int__ j = -1;
	std::string str = "";
	//for (auto && v : std::to_string(num)) {
#ifndef _WINDOWS_2
	sprintf(num_,"%d",num);
#else
	sprintf_s(num_,25,"%d",num);
#endif
	int__ n = strlen(num_);
	for (int__ j=0;j<n;j++) {
		str += num_[j];
		//std::cout << v /*- '0'*/ << "|";
		//str += v;
		//++j;
		//if (0 <= j && j <= 9)
		{
			glBindTexture(GL_TEXTURE_2D, IndexTexture[62 + str[j] - '0']);
			EnableTexture(NewTextureCoordinats[0], NewVertexCoordinats[63 + position], j);
		}
	}
}
void__ Scene2::EnableTexture(float__*texcoor, float__*vercoor)
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
void__ Scene2::EnableTexture(float__*texcoor, float__*vercoor,int__ dx)
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

void__ Scene2::Destroy()
{
    for(int__ i=0;i<CountTexture;i++)
        delete[] NewTextureCoordinats[i];
    delete[] NewTextureCoordinats;
    for(int__ i=0;i<CountTexture;i++)
        delete[] NewVertexCoordinats[i];
    delete[] NewVertexCoordinats;
	delete IndexTexture;
	delete num_;
}
