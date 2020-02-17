#include "Sound.h"
#ifdef _WIN32
	#pragma warning(disable : 4996)
	#pragma comment(lib,"OpenAL32_.lib")
#endif

Sound::Sound()
{
	song_ = 3;
	buffer = new unsigned int[song_];
	source = new unsigned int[song_];
	//lhead_ = new lhead[song_];
}
int Sound::Init()
{
	dev = alcOpenDevice(0);
	ctx = alcCreateContext(dev, 0);
	alcMakeContextCurrent(ctx);
	alGenBuffers(song_, buffer);
	alGenSources(song_, source);

	FILE* file_;
	errno_t err;
	err = fopen_s(&file_, "content//konga.wav", "rb");
	if (err)
	{
		printf_s("Failed open file, error %d", err);
		return 0;
	}

	WAVHEADER header;

	fread_s(&header, sizeof(WAVHEADER), sizeof(WAVHEADER), 1, file_);
	printf("audioformat:%d\n", header.audioFormat);
	printf("bitsPerSample:%d\n", header.bitsPerSample);
	printf("blockAlign:%d\n", header.blockAlign);
	printf("byteRate:%lu\n", header.byteRate);
	printf("chunkId:%s\n", header.chunkId);
	printf("chunkSize:%lu\n", header.chunkSize);
	printf("format:%s\n", header.format);
	printf("numCannels:%d\n", header.numChannels);
	printf("sampleRate:%lu\n", header.sampleRate);
	printf("subchunk1Id:%s\n", header.subchunk1Id);
	printf("subchunk1Size:%lu\n", header.subchunk1Size);
	printf("subchunk2Id:%s\n", header.subchunk2Id);
	printf("subchunk2Size:%lu\n", header.subchunk2Size);
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
#ifdef _WIN32
	file = open("content//konga.wav", _A_ARCH);
#else
	file = open(filename, O_RDONLY);
#endif // _WIN32
	if (file == -1)
	{
		printf("Open failed on input file: %s\n", "content//konga.wav");
#ifdef _WIN32
		wchar_t path[MAX_PATH];
		GetCurrentDirectory(sizeof(path), path);
		std::wcout << path << std::endl;
#endif // _WIN32
	}
	org = 0;
	int j = 0;
	//for (int i = 0; i < song_; i++)
	{
		lseek(file, 0, org);
		buf = new unsigned char[header.subchunk2Size];
		read(file, buf, header.subchunk2Size);
		org = 1;
		alBufferData(buffer[j], format, buf,header.subchunk2Size,header.sampleRate);
		alSourcei(source[j], AL_BUFFER, buffer[j]);
		j++;
	}
	
	
	return 0;;
}
int Sound::Play(int src)
{
	alGetSourcei(source[src], AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		return 0;
	alSourcePlay(source[src]);
	return 0;
}
int Sound::Stop(int src, bool force)
{
	alGetSourcei(source[src], AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING || force)
		alSourceStop(source[src]);
	return 0;
}
int Sound::StopAll()
{
	for (int i = 0; i < song_; i++)
		Stop(i, false);
	return 0;
}
Sound::~Sound()
{
	alDeleteSources(song_, source);
	alDeleteBuffers(song_, buffer);
	delete source;
	delete buffer;
	//delete lhead_;
	delete buf;
	alcMakeContextCurrent(0);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
	org = 2;
	close(file);
}