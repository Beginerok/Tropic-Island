#include "Loader.h"
Loader::Loader(void)
{
	flogout.open("log.txt");
	CountIndexTexture = 0;
	image = new SimpleImage[CountTexture];
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
}
SimpleImage* Loader::LoadImage(const ILstring path,std::string path_)
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
		strError = (wchar_t*)iluErrorString(err);
		// Выдаем сообщение об ошибке
#ifdef _WIN32
		MessageBox(NULL, NULL, L"Ошибка при загрузке il!", MB_OK);
#endif
		// выход из программы
		flogout << "Error loading image: " << reinterpret_cast<const char*>(path) << std::endl;
		flogout.close();
		exit(EXIT_FAILURE);
	}
	// Ширина изображения
	width = ilGetInteger(IL_IMAGE_WIDTH);
	// Высота изображения
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	// Тип хранения данных
	type = ilGetInteger(IL_IMAGE_FORMAT);
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
	gluBuild2DMipmaps(GL_TEXTURE_2D, type, width, height, type, GL_UNSIGNED_BYTE, copyData);
	CountIndexTexture++;
	image->Name[CountIndexTexture - 1] = path_;
	image->number[CountIndexTexture - 1] = CountIndexTexture - 1;
	return image;
}
int Loader::FindTexture(std::string name)
{
	int result = -1;
	for (int i = 0; i < CountTexture; i++)
		if (strcmp(image->Name[i].c_str(), name.c_str()) == 0)
			result = image->number[i];
	return result;
}
void Loader::LoadCoordFromFile()
{

}
Loader::~Loader()
{
	for (int i = 0; i < CountTexture; i++)
		delete[] image->TextureCoordinats[i];
	delete[] image->TextureCoordinats;
	for (int i = 0; i < CountTexture; i++)
		delete[] image->VertexCoordinats[i];
	for (int i = 0; i < CountTexture; i++)
		image->Name[i].clear();
	delete[] image->VertexCoordinats;
	delete image->IndexTexture;
	delete image->Name;
	delete image->number;
	delete image;
	flogout.close();
}
