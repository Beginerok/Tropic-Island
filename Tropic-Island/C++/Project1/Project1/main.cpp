
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <algorithm>
//#include <sstream>
//#include <locale>
#include <time.h>
#include "mp3.h"
#include "mp3frame.h"
//#define _CRT_SECURE_NO_WARNINGS 
long int rez = 0;
struct Type
{
	std::string filename;
	float length;
};
void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT, std::vector<Type> *v);

void AddTalk(std::vector<Type> *src, std::vector<Type> *dst, float &currentlength, float maxlength);
void AddMusic(std::vector<Type> *src, std::vector<Type> *dst, float &currentlength, float maxlength);
int Random(std::vector<Type> *vector);
int main(int argc, char* argv[])
{
	/*
	std::vector<Type> *vector = new std::vector<Type>();
	std::vector<Type> *vectortalk = new std::vector<Type>();
	char sPath[MAX_PATH] = "Z:\\Автоматизация\\музыка для радио от Сергея Косякова";
	char sPath2[MAX_PATH] = "Z:\\Радио";
	char sExt[10] = "mp3";
	char sEXT[10] = "MP3";
	GetFileList(sPath, sExt, sEXT, vector);
	printf("rez= %d\n", rez);
	rez = 0;
	GetFileList(sPath2, sExt, sEXT, vectortalk);
	printf("rez= %d\n", rez);

	std::ofstream fout;
	fout.open("playlist.m3u8");
	if (!fout.is_open())
	{
		std::cout << "Can't open file" << std::endl;
		exit(EXIT_FAILURE);
	}
	fout.write("#EXTM3U\n", strlen("#EXTM3U\n"));
	fout.write("#EXTINF:", strlen("#EXTINF:"));
	fout.write("12", strlen("12"));
	fout.write(",", strlen(","));
	fout.write((*vector)[0].filename.c_str(), (*vector)[0].filename.size());
	fout.write("\n", strlen("\n"));
	fout.write((*vector)[0].filename.c_str(), (*vector)[0].filename.size());
	fout.write("\n", strlen("\n"));

	
	std::string f_str;
	for (int i = 0;i < vector->size();i++)
	{
		fout.write(vector->at(i).filename.c_str(), vector->at(i).filename.size());
		fout.write("\n", 1);
		MP3 mp3(vector->at(i).filename.c_str());
		(*vector)[i].length = mp3.get_len();
		f_str = std::to_string(mp3.get_len());
		fout.write(f_str.c_str(),f_str.size());
		fout.write("\n", 1);
	}
	for (int i = 0;i < vectortalk->size();i++)
	{
		fout.write(vectortalk->at(i).filename.c_str(), vectortalk->at(i).filename.size());
		fout.write("\n", 1);
		MP3 mp3(vectortalk->at(i).filename.c_str());
		(*vectortalk)[i].length = mp3.get_len();
		f_str = std::to_string(mp3.get_len());
		fout.write(f_str.c_str(), f_str.size());
		fout.write("\n", 1);
	}
	

	fout.close();
	*/
	Type elem;
	/*
	MP3 mp3__("C:\\Users\\User\\Desktop\\РАДИО\\джингл1.mp3");
	std::cout << mp3__.get_name();
	std::cout << mp3__.get_artist();
	std::cout << mp3__.get_len() << " length\n";
	std::cout << mp3__.get_bitrate() << " bitrate\n";
	//cout << mp3.get_pic();
	//mp3.save_pic("where/you/want/to/save.jpg");
	elem.filename = "C:\\Users\\User\\Desktop\\РАДИО\\джингл1.mp3";
	elem.length = mp3__.get_len();
	*/
	std::vector<Type> *vector2 = new std::vector<Type>();

	//vector2->push_back(elem);
	
	setlocale(LC_ALL, "Russian");

	std::ifstream fin("playlist2.m3u8");
	if (!fin.is_open())
	{
		std::cout << "File not found!" << std::endl;
	}
	std::string str="";
	while (std::getline(fin,elem.filename))
	{
		std::getline(fin, str);
		elem.length = std::stof(str);
		if(elem.length != 0.0)
			vector2->push_back(elem);
	}
	fin.close();
	
	int sum = 0;
	for (int i = 0;i < vector2->size();i++)
		if ((*vector2)[i].length == 0.0)
			sum++;
	
	std::cout <<"size="<< vector2->size() << std::endl<<"0: " <<sum<< std::endl;
	
	std::cout << (*vector2)[0].filename << std::endl << (*vector2)[0].length << std::endl;
	std::cout << (*vector2)[vector2->size()-1].filename << std::endl << (*vector2)[vector2->size() - 1].length << std::endl;
	

	//setlocale(LC_ALL, "ru_RU.UTF-8");
	std::vector<Type> *vector3 = new std::vector<Type>();
	std::ifstream fin2("playlist3.m3u8");
	if (!fin2.is_open())
	{
		std::cout << "File not found!" << std::endl;
	}
	while (std::getline(fin2, elem.filename))
	{
		std::getline(fin2, str);
		elem.length = std::stof(str);
		if (elem.length != 0.0)
			vector3->push_back(elem);
	}
	fin2.close();
	
	sum = 0;
	for (int i = 0;i < vector3->size();i++)
		if ((*vector3)[i].length == 0.0)
			sum++;
	
	std::cout << "size=" << vector3->size() << std::endl << "0: " << sum << std::endl;
	
	std::cout << (*vector3)[0].filename << std::endl << (*vector3)[0].length << std::endl;
	
	std::sort(vector2->begin(), vector2->end(), [](const Type& a, const Type& b) {return a.length > b.length; });

	for (int i = 0; i < vector2->size(); i++)
		std::cout << vector2->at(i).length << " ";
	float length = 3600.0, currentlength = 0.0f;
	std::vector<Type> *vec = new std::vector<Type>();

	srand(time(0));
	AddMusic(vector2, vec, currentlength, length);
	std::cout <<"vec: "<< std::endl;
	for (int i = 0; i < vec->size(); i++)
		std::cout << vec->at(i).length << " ";
	std::cout << std::endl << "cl:" << currentlength << std::endl;
	
	std::sort(vector3->begin(), vector3->end(), [](const Type& a, const Type& b) {return a.length > b.length; });
	for (int i = 0; i < vector3->size(); i++)
		std::cout << vector3->at(i).length << " ";

	
	length = 2.5 * 3600.0;
	AddTalk(vector3, vec, currentlength, length);
	AddMusic(vector2, vec, currentlength, length);
	std::cout << "vec: " << std::endl;
	for (int i = 0; i < vec->size(); i++)
		std::cout << vec->at(i).length << " ";
	std::cout << std::endl << "cl:" << currentlength << std::endl;

	length = 10800.0;
	//
	AddTalk(vector3, vec, currentlength, length);
	//
	AddMusic(vector2, vec, currentlength, length);
	std::cout << "vec: " << std::endl;
	for (int i = 0; i < vec->size(); i++)
		std::cout << vec->at(i).length << " ";
	std::cout << std::endl << "cl:" << currentlength << std::endl;
	
	std::ofstream fout;
	fout.open("playlist.m3u8");
	if (!fout.is_open())
	{
		std::cout << "Can't open file" << std::endl;
		exit(EXIT_FAILURE);
	}
	fout.write("#EXTM3U\n", strlen("#EXTM3U\n"));
	for (int i = 0; i < vec->size(); i++)
	{
		fout.write("#EXTINF:", strlen("#EXTINF:"));
		str = std::to_string((*vec)[i].length);
		fout.write(str.c_str(), strlen(str.c_str()));
		fout.write(",", strlen(","));
		fout.write((*vec)[i].filename.c_str(), (*vec)[i].filename.size());
		fout.write("\n", strlen("\n"));
		fout.write((*vec)[i].filename.c_str(), (*vec)[i].filename.size());
		fout.write("\n", strlen("\n"));
	}
	fout.close();
	//vector->clear();
	//vectortalk->clear();

	std::cin.get();
	return 0;
}
void AddTalk(std::vector<Type> *src,std::vector<Type> *dst, float &currentlength,float maxlength)
{
	int num;
	bool b = false;
	for (int i = 0; i < 1; i++)
	{
		num = Random(src);
		if (src->at(num).length + currentlength <= maxlength)
		{
			b = true;
			dst->push_back(src->at(num));
			currentlength += dst->back().length;
		}
		if (!b)
			AddTalk(src, dst, currentlength, maxlength);
	}
}
void AddMusic(std::vector<Type> *src, std::vector<Type> *dst, float &currentlength, float maxlength)
{
	int num;
	for (int i = 0; i < 10; i++)
	{
		num = Random(src);
		if (src->at(num).length + currentlength <= maxlength)
		{
			dst->push_back(src->at(num));
			currentlength += dst->back().length;
		}
	}
	for (int i = 0; i < src->size(); i++)
	{
		if (src->at(i).length + currentlength <= maxlength)
		{
			dst->push_back(src->at(i));
			currentlength += dst->back().length;
		}
	}
}
int Random(std::vector<Type> *vector)
{
	int min = 0, max = vector->size()-1;
	return min + rand() % (max - min + 1);
}
void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT,std::vector<Type> *v) {

	WIN32_FIND_DATA pFILEDATA;
	HANDLE hFile = FindFirstFile(strcat(sPath, "\\*.*"), &pFILEDATA);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!Необходимо именно здесь прописывать длину пути!!!!!!!!!!!!!!!!!!!!!!!
	sPath[strlen(sPath) - strlen(strstr(sPath, "*.*"))] = '\0';
	//Если пропишем после if (как предлагает Юра), то тогда, если вдруг натыкаемся на системную директорию
	// или файл, то FindFirstFile возвращает -1. Следовательно, всё, что выплнняется по условию
	//(hFile!=INVALID_HANDLE_VALUE) не выолнится и в частности, не будет поставлен конец строки!
	//А это значит, что по выходу из  рекурсивной функции GetFileList в том месте, где мы восстанавливаем
	//Длину, она будет восстановлена неправильно
	if (hFile != INVALID_HANDLE_VALUE) {
		char * chBuf;
		//sPath[strlen(sPath) - strlen(strstr(sPath,"*.*"))] = '\0';
		do {
			//Пропускаем . и ..
			if (strlen(pFILEDATA.cFileName) == 1 && strchr(pFILEDATA.cFileName, '.') != NULL)
				if (FindNextFile(hFile, &pFILEDATA) == 0)
					break;
			if (strlen(pFILEDATA.cFileName) == 2 && strstr(pFILEDATA.cFileName, "..") != NULL)
				if (FindNextFile(hFile, &pFILEDATA) == 0)
					break;
			//Если нашли директорию, запускаем поиск в ней рекурсивный поиск
			if (pFILEDATA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				GetFileList(strcat(sPath, pFILEDATA.cFileName), sExt, sEXT,v);

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!оБЯЗАТЕЛЬН востанавливать дллину пути................................     
				sPath[strlen(sPath) - strlen(pFILEDATA.cFileName) - 1] = '\0';
			}
			else {
				//Проверяем на соотвествие sExt расширения pFILEDATA.cFileName
				if ((chBuf = strrchr(pFILEDATA.cFileName, '.'))) {
					if (strstr(chBuf + 1, sExt) || strstr(chBuf + 1, sEXT)) {
						//Если не будем использовать CharToOem() то на экране русский шрифт каракулями выйдет
						CharToOem(sPath, sPath);
						//printf("%s", sPath);
						OemToChar(sPath, sPath);
						CharToOem(pFILEDATA.cFileName, pFILEDATA.cFileName);
						//printf("%s\n", pFILEDATA.cFileName);
						
						Type type;
						if (rez == 14)
							bool b = true;
						OemToChar(pFILEDATA.cFileName, pFILEDATA.cFileName);
						std::string str = pFILEDATA.cFileName;
						type.filename = sPath + str;
						v->push_back(type);
						//printf("%s\n",v->at(rez).filename);
						//printf("%d\n", rez);
						
						rez++;
					}
				}
			}
		} while (FindNextFile(hFile, &pFILEDATA));
	}
}