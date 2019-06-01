#include "FileReader.h"
#ifdef _WINDOWS_2
    #pragma warning(disable : 4996)
#endif
FileReader::FileReader()
{
    countbyte=0;
    countstroke=0;
    strokoffile=0;
    stroke=new char__[64];
    tmpstroke=new char__[64];
	open_=false;
	str=new char__[64];
}
void__ FileReader::ReadFile(int__ size_,void__ *buf)
{
	lseek(life,0,org);
    read(life,buf,size_);
	org=1;
}
std::string FileReader::GetNumber()
{
    fgets(stroke,64,file);
    int__ j=- 1;
    while(stroke[++j]!=32);
    std::string s="";
    int__ i=0;
    while(stroke[++j]!=10)
    {
        s+=stroke[j];
        tmpstroke[i++]=stroke[j];
    }
    return s;
}
void FileReader::FileReader__(const char__ *filename,const char__ *state)
{
	std::string ext="";
	int__ l=strlen(filename);
	while(--l>0&&filename[l]!='.')
		ext+=filename[l];
	if(strstr(ext.c_str(),"fnoc") || strstr(ext.c_str(),"lmx")|| strstr(ext.c_str(), "lmth"))
	{
		ext_=true;
		file=fopen(filename,state);
		if (file == NULL) {
			printf("not found file: %s", filename);
		}
		open_ = true;
		char__ ch;
		while((ch=fgetc(file))!=EOF)
		{
	        if(ch==10)
				strokoffile++;
			countbyte++;
		}
		fclose(file);
		file=fopen(filename,state);
	}
	else
	{
        #ifdef _WINDOWS_2
            life=open(filename,_A_ARCH);
			if (life == -1)
				printf("Open failed on input file: %s",filename);
		#else
		    life=open(filename,O_RDONLY);
		#endif // _WINDOWS_2
		ext_=false;
		org=0;
	}
}
char__ *FileReader::GetStroke()
{
    if(countstroke!=strokoffile)
    {
        countstroke++;
        return fgets(stroke,64,file);
    }
    open_=false;
    return new char__;
}
float__ FileReader::BConvert(int__ pos)
{
    float__ n;
    if(pos==0)
        n=atof(stroke);
    else
    {
        int__ i=0;
        while(stroke[i]!=32)
            i++;
        int__ j=0;
        i++;
        if(pos==1)
        {
            while(stroke[i]!=32)
                str[j++]=stroke[i++];
            n=atof(str);
        }
        if(pos==2)
        {
            while(stroke[i++]!=32);
            while(stroke[i]!=10)
                str[j++]=stroke[i++];
            n=atof(str);
        }
    }
    return n;
}
void__ FileReader::PutStroke()
{
    fputs(stroke,file);
}
void__ FileReader::PutBuf(int__ size_,void__ *buf)
{
    fwrite(buf,size_,1,file);
}
void__ FileReader::EndStroke()
{
    fputc(10,file);
}
void__ FileReader::Convert(float__ flt)
{
    sprintf(stroke,"%.3f ",flt);
}
bool__ FileReader::Opened()
{
    return open_;
}
FileReader::~FileReader()
{
	org=2;
    open_=false;
	if(ext_)
		fclose(file);
	else
		close(life);
    delete stroke;
    delete tmpstroke;
	delete str;
}
