#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>
#include "typedefs.h"
#ifdef _WINDOWS_
    #include <io.h>
#else
    #include <unistd.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/stat.h>
#endif // _WINDOWS_
class FileReader
{
public:
    FileReader();
    std::string GetNumber();
    void FileReader__(const char__ *filename,const char__ *state);
    char__ * GetStroke();
    void__ PutStroke();
    void__ Convert(float__ flt);
    float__ BConvert(int__ pos);
    void__ EndStroke();
    bool__ Opened();
    void__ ReadFile(int__ size_,void__ *buf);
    void__ PutBuf(int__ size_,void__ *buf);
	void__ SetOff(int__ fes);
    virtual ~FileReader();
protected:
    FILE *file;
	int__ life;
    char__ *stroke,*str;
    bool__ open_,ext_;
    int__ countstroke;
    int__ strokoffile;
    char__ *tmpstroke;
    int__ countbyte;
	int__ org;
};
#endif
