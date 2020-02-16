#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <iostream>
#include <string>
//#include "FileReader.h"
#ifdef _WIN32
	#include <io.h>
	#include <Windows.h>
#else
	#include <unistd.h>
	#include <string.h>
	#include <fcntl.h>
	#include <sys/stat.h>
#endif // _WIN32
struct lhead
{
	unsigned int i1;
	unsigned short ul1;
	unsigned short us5;
	unsigned int ul2;
};
struct WavFmt
{
	unsigned short encoding;
	unsigned short channels;
	unsigned int   frequency;
	unsigned int   byterate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
};
struct WAVHEADER
{
	// WAV-формат начинается с RIFF-заголовка:

	// Содержит символы "RIFF" в ASCII кодировке
	// (0x52494646 в big-endian представлении)
	char chunkId[4];

	// 36 + subchunk2Size, или более точно:
	// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
	// Это оставшийся размер цепочки, начиная с этой позиции.
	// Иначе говоря, это размер файла - 8, то есть,
	// исключены поля chunkId и chunkSize.
	unsigned long chunkSize;

	// Содержит символы "WAVE"
	// (0x57415645 в big-endian представлении)
	char format[4];

	// Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
	// Подцепочка "fmt " описывает формат звуковых данных:

	// Содержит символы "fmt "
	// (0x666d7420 в big-endian представлении)
	char subchunk1Id[4];

	// 16 для формата PCM.
	// Это оставшийся размер подцепочки, начиная с этой позиции.
	unsigned long subchunk1Size;

	// Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
	// Для PCM = 1 (то есть, Линейное квантование).
	// Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
	unsigned short audioFormat;

	// Количество каналов. Моно = 1, Стерео = 2 и т.д.
	unsigned short numChannels;

	// Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
	unsigned long sampleRate;

	// sampleRate * numChannels * bitsPerSample/8
	unsigned long byteRate;

	// numChannels * bitsPerSample/8
	// Количество байт для одного сэмпла, включая все каналы.
	unsigned short blockAlign;

	// Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
	unsigned short bitsPerSample;

	// Подцепочка "data" содержит аудио-данные и их размер.

	// Содержит символы "data"
	// (0x64617461 в big-endian представлении)
	char subchunk2Id[4];

	// numSamples * numChannels * bitsPerSample/8
	// Количество байт в области данных.
	unsigned long subchunk2Size;

	// Далее следуют непосредственно Wav данные.
};
enum
{
	RIFF = 0x46464952,
	WAVE = 0x45564157,
	FMT = 0x20746D66,
	DATA = 0x61746164,
};
class Sound
{
public:
	Sound();
	int Init();
	int Play(int src);
	int Stop(int src, bool force);
	int StopAll();
	void SetPlay(int num);
	virtual ~Sound();
private:
protected:
	ALCdevice* dev;
	ALCcontext* ctx;
	unsigned int* buffer, * source;
	int state;
	int song_;
	unsigned char* buf;
	unsigned int size_, freq;
	int format;
	lhead* lhead_;
	int file;
	int org;
	//Data* data;
};