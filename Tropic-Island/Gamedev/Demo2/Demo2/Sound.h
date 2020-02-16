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
	// WAV-������ ���������� � RIFF-���������:

	// �������� ������� "RIFF" � ASCII ���������
	// (0x52494646 � big-endian �������������)
	char chunkId[4];

	// 36 + subchunk2Size, ��� ����� �����:
	// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
	// ��� ���������� ������ �������, ������� � ���� �������.
	// ����� ������, ��� ������ ����� - 8, �� ����,
	// ��������� ���� chunkId � chunkSize.
	unsigned long chunkSize;

	// �������� ������� "WAVE"
	// (0x57415645 � big-endian �������������)
	char format[4];

	// ������ "WAVE" ������� �� ���� ����������: "fmt " � "data":
	// ���������� "fmt " ��������� ������ �������� ������:

	// �������� ������� "fmt "
	// (0x666d7420 � big-endian �������������)
	char subchunk1Id[4];

	// 16 ��� ������� PCM.
	// ��� ���������� ������ ����������, ������� � ���� �������.
	unsigned long subchunk1Size;

	// ����� ������, ������ ������ ����� �������� ����� http://audiocoding.ru/wav_formats.txt
	// ��� PCM = 1 (�� ����, �������� �����������).
	// ��������, ������������ �� 1, ���������� ��������� ������ ������.
	unsigned short audioFormat;

	// ���������� �������. ���� = 1, ������ = 2 � �.�.
	unsigned short numChannels;

	// ������� �������������. 8000 ��, 44100 �� � �.�.
	unsigned long sampleRate;

	// sampleRate * numChannels * bitsPerSample/8
	unsigned long byteRate;

	// numChannels * bitsPerSample/8
	// ���������� ���� ��� ������ ������, ������� ��� ������.
	unsigned short blockAlign;

	// ��� ���������� "��������" ��� �������� ��������. 8 ���, 16 ��� � �.�.
	unsigned short bitsPerSample;

	// ���������� "data" �������� �����-������ � �� ������.

	// �������� ������� "data"
	// (0x64617461 � big-endian �������������)
	char subchunk2Id[4];

	// numSamples * numChannels * bitsPerSample/8
	// ���������� ���� � ������� ������.
	unsigned long subchunk2Size;

	// ����� ������� ��������������� Wav ������.
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