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
	lhead_ = new lhead[song_];
	/*buf = new unsigned char[190884];*/
	//data = new Data("content//bonus.wav");
	//data->ok = true;
}
class	Data
{
	byte* bits;
	int		length;
	int		pos;
	std::string	file;
	long getLong()
	{
		if (pos + 3 >= length)
			return -1;

		long 	v = *(long*)(bits + pos);

		pos += 4;

		return v;
	}
	int		getBytes(void* ptr, int len);

	int	dataOffs;
	int	dataLength;
	FILE*fp;
	int		numChannels;
	int		frequency;
	int		bitsPerSample;
	bool	ok;

	Data::Data(const char* theFileName);
};
int	Data::getBytes(void* ptr, int len)
{
	if (pos >= length)
		return -1;

	if (pos + len > length)
		len = length - pos;

	memcpy(ptr, bits + pos, len);

	pos += len;

	return len;
}
Data::Data(const char* theFileName)
{
	//data = NULL;
	fp = fopen(theFileName, "rb");
	numChannels = 0;
	frequency = 0;
	bitsPerSample = 8;
	ok = true;
}
int Sound::Init()
{
	dev = alcOpenDevice(0);
	ctx = alcCreateContext(dev, 0);
	alcMakeContextCurrent(ctx);
	alGenBuffers(song_, buffer);
	alGenSources(song_, source);
	int j = 0;
/*
	lhead_[0].i1 = 190884;
	lhead_[0].ul1 = 1;
	lhead_[0].us5 = 16;
	lhead_[0].ul2 = 22050;
	lhead_[1].i1 = 47532;
	lhead_[1].ul1 = 1;
	lhead_[1].us5 = 16;
	lhead_[1].ul2 = 22050;
	lhead_[2].i1 = 46376;
	lhead_[2].ul1 = 1;
	lhead_[2].us5 = 16;
	lhead_[2].ul2 = 22050;
*/
#ifdef _WIN32
	file = open("content//winner.wav", _A_ARCH);

#else
	file = open(filename, O_RDONLY);
#endif // _WIN32
	if (file == -1)
	{
		printf("Open failed on input file: %s\n", "content//winner.wav");
#ifdef _WIN32
		wchar_t path[MAX_PATH];
		GetCurrentDirectory(sizeof(path), path);
		std::wcout << path << std::endl;
#endif // _WIN32
	}
	org = 0;

	/*
	long	magic = data->getLong();
	long	length = data->getLong();
	long	magic2 = data->getLong();

	if (magic != RIFF || magic2 != WAVE)
	{
		data->ok = false;

		return;
	}

	for (; data->getPos() < data->getLength(); )
	{
		magic = data->getLong();
		length = data->getLong();

		if (magic == FMT)
		{
			WavFmt	format;

			data->getBytes(&format, sizeof(format));

			if (format.encoding != 1)
			{
				data->ok = false;

				return;
			}

			data->numChannels = format.channels;
			data->frequency = format.frequency;
			data->bitsPerSample = format.bitsPerSample;
		}
		else
			if (magic == DATA)
			{
				data->dataOffs = data->getPos();
				data->dataLength = length;

				break;
			}
			else
				data->seekCur(length);
	}

	if (data->numChannels < 1 || data->frequency == 0 || data->dataOffs == 0 || data->dataLength == 0)
		data->ok = false;
	if (data->numChannels == 2)		// stereo
		if (data->bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
		else
			format = AL_FORMAT_STEREO8;
	else
		if (data->bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_MONO8;
	*/
	FILE* file_;
	errno_t err;
	err = fopen_s(&file_, "content//winner.wav", "rb");
	if (err)
	{
		printf_s("Failed open file, error %d", err);
		return 0;
	}

	WAVHEADER header;

	fread_s(&header, sizeof(WAVHEADER), sizeof(WAVHEADER), 1, file_);
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
	for (int i = 0; i < song_; i++)
	{
	/*
		if (lhead_[j].ul1 == 1)
		{
			if (lhead_[j].us5 == 16)
				format = AL_FORMAT_MONO16;
			else
				format = AL_FORMAT_MONO8;
		}
		else
		{
			if (lhead_[j].us5 == 16)
				format = AL_FORMAT_STEREO16;
			else
				format = AL_FORMAT_STEREO8;
		}
		freq = lhead_[j].ul2;
		size_ = lhead_[j].i1;
	*/
		lseek(file, 0, org);
		buf = new unsigned char[header.subchunk2Size/*data->dataLength*/];
		read(file, buf, header.subchunk2Size/*data->dataLength*/ /*size_*/);
		org = 1;
		alBufferData(buffer[j], format, buf,header.subchunk2Size /*data->dataLength*//*size_*/,header.sampleRate/*data->frequency*//* freq*/);
		alSourcei(source[j], AL_BUFFER, buffer[j]);
		j++;
	}
	
	
	return 0;// data->ok;
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
	delete lhead_;
	delete buf;
	alcMakeContextCurrent(0);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
	org = 2;
	close(file);
}