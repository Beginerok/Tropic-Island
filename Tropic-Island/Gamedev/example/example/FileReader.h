#ifndef FILEREADER_H
#define FILEREADER_H
#include <sstream>
class FileReader
{
public:
	FileReader();
    std::string GetNumber();
    void FileReader__(const char * filename,const char *state);
    unsigned char *FileReader_(const char *filename);
	int getfreq();
	int getformat();
	int getsize();
	int getsample();
	void ReadW();
public:
	char *GetStroke();
    void PutStroke();
    void Convert(float flt);
    float BConvert(int pos);
    void EndStroke();
    bool Opened();
	~FileReader();
protected:
private:
    FILE *file;
    char *stroke,*tmpstroke;
    int lengthstroke;
    bool _open__,__open_;
    int countstroke;
    int strokoffile;
	long len;
	int rtp;
};
#endif // FILEREADER_H