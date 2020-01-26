#include "example\FileReader.h"
FileReader::FileReader()
{
    lengthstroke = 64;
    countstroke = 0;
    strokoffile = 0;
    stroke = new char[lengthstroke];
    tmpstroke = new char[lengthstroke];
	_open__ = false;
	__open_ = _open__;
	rtp  = 0;
}
std::string FileReader::GetNumber()
{
    fgets(stroke,lengthstroke,file);
    int j = - 1;
    while(stroke[++j]!=32);
    std::string s ="";
    int i=0;
    while(stroke[++j]!=-51)//BeWare 
    {
        s+=stroke[j];
        tmpstroke[i++] = stroke[j];
    }
    return s;
}
struct head
{
	char chunkId[4];
	unsigned long chunkSize;
	char format[4];
	char subchunk1Id[4];
	unsigned long subchunk1Size;
	unsigned short audioformat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char subchunk2Id[4];
	unsigned long subchunk2Size;
}head_;
int FileReader::getfreq()
{
	return head_.sampleRate;
};
int FileReader::getsize()
{
	return len;
};
int FileReader::getformat()
{
	return head_.numChannels;
};
int FileReader::getsample()
{
	return head_.bitsPerSample;
};
void FileReader::FileReader__(const char * filename,const char *state)
{
	file = fopen(filename,state);
	//__open_ = !_open__;
	char ch;
	while((ch = fgetc(file))!= -1)
		if(ch == 10)
			strokoffile++;
	fclose(file);
	file = fopen(filename,state);
	//fread(&head_,sizeof(head_),1,file);
	//fclose(file);
}
unsigned char *FileReader::FileReader_(const char *filename)
{
	FileReader__(filename,"r");
	file = fopen(filename,"r");
	len = head_.chunkSize;
	unsigned char *bit = new unsigned char[len];
	fread(bit,len,1,file);
	_open__ = !__open_;
	return bit;
}
char *FileReader::GetStroke()
{
	if(countstroke != strokoffile)
	{
		countstroke++;
		return fgets(stroke,lengthstroke,file);
	}
	return "-1";
}
float FileReader::BConvert(int pos)
{
	float n;
	char *str = new char[lengthstroke];
	if(pos == 0)
		n = atof(stroke);
	else
	{
		int i=0;
		while(stroke[i]!=32)
			i++;
		int j=0;
		i++;
		if(pos == 1)
		{
			while(stroke[i]!=32)
				str[j++] = stroke[i++];
			n = atof(str);
		}
		if(pos == 2)
		{
			while(stroke[i++]!=32);
			while(stroke[i]!=-1)
				str[j++] = stroke[i++];
			n = atof(str);
		}
	}
	delete str;
	return n;
}
void FileReader::PutStroke()
{
	fputs(stroke,file);
}
void FileReader::EndStroke()
{
    fputc(-1,file);
}
void FileReader::Convert(float flt)
{
	sprintf(stroke,"%.3f ",flt);
}
bool FileReader::Opened()
{
	return __open_ || _open__;
}
FileReader::~FileReader()
{
	if(__open_ && !rtp)
	{
		__open_ = __open_;
		fclose(file);
		delete stroke;
		delete tmpstroke;
	}
	if(_open__ && !rtp)
	{
		_open__ = !_open__;
		fclose(file);
		delete stroke;
		delete tmpstroke;
	}
}
