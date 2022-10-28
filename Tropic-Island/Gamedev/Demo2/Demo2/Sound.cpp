#include "Sound.h"
#ifdef _WIN32
	#pragma warning(disable : 4996)
	#pragma comment(lib,"OpenAL32.lib")
#endif

Sound::Sound()
{
	CountSounds = 7;
	sounds = new Sounds[CountSounds];
	sounds->Name = new std::string[CountSounds];
	for (int i = 0; i < CountSounds; i++)
		sounds->Name[i] = "";
	sounds->buffer = new unsigned int[CountSounds];
	sounds->source = new unsigned int[CountSounds];
	sounds->number = new int[CountSounds];
	CounterSounds = 0;
}
int Sound::Init(int argc, char*argv[])
{
#ifndef _WIN32
    alutInit(&argc, argv);
#endif
	dev = alcOpenDevice(0);
	ctx = alcCreateContext(dev, 0);
	alcMakeContextCurrent(ctx);
	alGenBuffers(CountSounds, sounds->buffer);
	alGenSources(CountSounds, sounds->source);
	sounds->Name[0] = "content//test2.wav";
	sounds->Name[1] = "content//konga.wav";
	sounds->Name[2] = "content//internet.wav";
	sounds->Name[3] = "content//winner.wav";
	sounds->Name[4] = "content//coin.wav";
	sounds->Name[5] = "content//fast.wav";
	sounds->Name[6] = "content//stop.wav";
	for (int j = 0; j < CountSounds; j++)
	{
#ifdef _WIN32
		FILE* file_;
		errno_t err;
		err = fopen_s(&file_,sounds->Name[j].c_str(), "rb");
		if (err)
		{
			printf_s("Failed open file, error %d", err);
			return 0;
		}
		WAVHEADER header;
		fread_s(&header, sizeof(WAVHEADER), sizeof(WAVHEADER), 1, file_);
		/*
		printf("chunkId:%s\n", header.chunkId);
		printf("chunkSize:%lu\n", header.chunkSize);
		printf("format:%s\n", header.format);
		printf("subchunk1Id:%s\n", header.subchunk1Id);
		printf("subchunk1Size:%lu\n", header.subchunk1Size);
		printf("audioformat:%d\n", header.audioFormat);
		printf("numCannels:%d\n", header.numChannels);
		printf("sampleRate:%lu\n", header.sampleRate);
		printf("byteRate:%lu\n", header.byteRate);
		printf("blockAlign:%d\n", header.blockAlign);
		printf("bitsPerSample:%d\n", header.bitsPerSample);
		printf("subchunk2Id:%s\n", header.subchunk2Id);
		printf("subchunk2Size:%lu\n", header.subchunk2Size);
		*/
		fclose(file_);
		if (header.numChannels == 1)
		{
			if (header.subchunk1Size == 16)
				format = AL_FORMAT_MONO16;
			else
				format = AL_FORMAT_MONO8;
		}
		else
		{
			if (header.subchunk1Size == 16)
				format = AL_FORMAT_STEREO16;
			else
				format = AL_FORMAT_STEREO8;
		}
		file = open(sounds->Name[j].c_str(), _A_SYSTEM);
		if (file == -1)
		{
			printf("Open failed on input file: %s\n",sounds->Name[j].c_str());
			wchar_t path[MAX_PATH];
			GetCurrentDirectory(sizeof(path), path);
			std::wcout << path << std::endl;
		}
		org = 0;
		lseek(file,0,org);
		//std::cout<<"hchs="<<header.subchunk2Size<<std::endl;
		buf = new unsigned char[header.subchunk2Size];
		read(file, buf, header.subchunk2Size);
		close(file);
		alBufferData(sounds->buffer[j], format, buf, header.subchunk2Size, header.sampleRate);
		delete buf;
#else
        sounds->buffer[j] = alutCreateBufferFromFile(sounds->Name[j].c_str());
#endif // _WIN32
		alSourcei(sounds->source[j], AL_BUFFER, sounds->buffer[j]);
	}

	return 0;
}
int Sound::Play(int src)
{
	alGetSourcei(sounds->source[src], AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		return 0;
	alSourcePlay(sounds->source[src]);
	return 1;
}
int Sound::Stop(int src, bool force)
{
	alGetSourcei(sounds->source[src], AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING || force)
		alSourceStop(sounds->source[src]);
	return 0;
}
int Sound::StopAll()
{
	for (int i = 0; i < CountSounds; i++)
		Stop(i, false);
	return 0;
}

void Sound::Pause(int src)
{
	alGetSourcei(sounds->source[src], AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		alSourcePause(sounds->source[src]);
}
Sound::~Sound()
{
	alDeleteSources(CountSounds, sounds->source);
	alDeleteBuffers(CountSounds, sounds->buffer);
	delete sounds;
	delete buf;
	alcMakeContextCurrent(0);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
}
