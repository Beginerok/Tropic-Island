#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#ifndef _WIN32
	#include <AL/alut.h>
#endif
#include <stdio.h>
#include <iostream>
#include <string>
#ifdef _WIN32
	#include <io.h>
	#include <Windows.h>
#else
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/stat.h>
#endif // _WIN32
#ifdef _WIN32
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
#endif // _WIN32
struct Sounds
{
	unsigned int* buffer;
	unsigned int* source;
	std::string* Name;
	int* number;
};
class Sound
{
public:
	Sound();
	int Init(int argc, char*argv[]);
	int Play(int src);
	int Stop(int src, bool force);
	int StopAll();
	void SetPlay(int num);
	void Pause(int num);
	virtual ~Sound();
private:
protected:
	ALCdevice* dev;
	ALCcontext* ctx;
	int state;
	unsigned char* buf;
	unsigned int size_, freq;
	int format;
	int file;
	int org;
	Sounds *sounds;
	int CounterSounds, CountSounds;
};
