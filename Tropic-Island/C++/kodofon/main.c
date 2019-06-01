#include <stdio.h>
#include <stdlib.h>
void HexToBin(char**oc,char**se,int size,int size_oc)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size_oc;j++)
        {
            switch(oc[i][j])
            {
            case '0':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='0';
                se[i][2+j*4]='0';
                se[i][3+j*4]='0';
                break;
            }
            case '1':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='0';
                se[i][2+j*4]='0';
                se[i][3+j*4]='1';
                break;
            }
            case '2':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='0';
                se[i][2+j*4]='1';
                se[i][3+j*4]='0';
                break;
            }
            case '3':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='0';
                se[i][2+j*4]='1';
                se[i][3+j*4]='1';
                break;
            }
            case '4':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='1';
                se[i][2+j*4]='0';
                se[i][3+j*4]='0';
                break;
            }
            case '5':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='1';
                se[i][2+j*4]='0';
                se[i][3+j*4]='1';
                break;
            }
            case '6':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='1';
                se[i][2+j*4]='1';
                se[i][3+j*4]='0';
                break;
            }
            case '7':
            {
                se[i][0+j*4]='0';
                se[i][1+j*4]='1';
                se[i][2+j*4]='1';
                se[i][3+j*4]='1';
                break;
            }
            case '8':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='0';
                se[i][2+j*4]='0';
                se[i][3+j*4]='0';
                break;
            }
            case '9':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='0';
                se[i][2+j*4]='0';
                se[i][3+j*4]='1';
                break;
            }
            case 'A':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='0';
                se[i][2+j*4]='1';
                se[i][3+j*4]='0';
                break;
            }
            case 'B':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='0';
                se[i][2+j*4]='1';
                se[i][3+j*4]='1';
                break;
            }
            case 'C':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='1';
                se[i][2+j*4]='0';
                se[i][3+j*4]='0';
                break;
            }
            case 'D':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='1';
                se[i][2+j*4]='0';
                se[i][3+j*4]='1';
                break;
            }
            case 'E':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='1';
                se[i][2+j*4]='1';
                se[i][3+j*4]='0';
                break;
            }
            case 'F':
            {
                se[i][0+j*4]='1';
                se[i][1+j*4]='1';
                se[i][2+j*4]='1';
                se[i][3+j*4]='1';
                break;
            }
            }

        }
    }
}



char Bin3ToHex(char*str,int pos)
{
    char*substr=(char*)malloc(sizeof(char)*3);
    substr[0] = str[pos-2];
    substr[1] = str[pos-1];
    substr[2] = str[pos];
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='0')
        return '0';
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='1')
        return '1';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='0')
        return '2';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='1')
        return '3';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='0')
        return '4';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='1')
        return '5';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='0')
        return '6';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='1')
        return '7';
}

char Bin4ToHex(char*str,int pos)
{
    char*substr=(char*)malloc(sizeof(char)*4);
    substr[0] = str[pos-3];
    substr[1] = str[pos-2];
    substr[2] = str[pos-1];
    substr[3] = str[pos];
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='0' && substr[3]=='0')
        return '0';
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='0' && substr[3]=='1')
        return '1';
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='1' && substr[3]=='0')
        return '2';
    if(substr[0]=='0' && substr[1]=='0' && substr[2]=='1' && substr[3]=='1')
        return '3';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='0' && substr[3]=='0')
        return '4';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='0' && substr[3]=='1')
        return '5';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='1' && substr[3]=='0')
        return '6';
    if(substr[0]=='0' && substr[1]=='1' && substr[2]=='1' && substr[3]=='1')
        return '7';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='0' && substr[3]=='0')
        return '8';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='0' && substr[3]=='1')
        return '9';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='1' && substr[3]=='0')
        return 'A';
    if(substr[0]=='1' && substr[1]=='0' && substr[2]=='1' && substr[3]=='1')
        return 'B';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='0' && substr[3]=='0')
        return 'C';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='0' && substr[3]=='1')
        return 'D';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='1' && substr[3]=='0')
        return 'E';
    if(substr[0]=='1' && substr[1]=='1' && substr[2]=='1' && substr[3]=='1')
        return 'F';
}
void BinToHex(char*str,char**ocx,int size,int oct_size/*,int pos*/)
{
    int pos = strlen(str)-1;
    for(int i=0;i<size && pos>5;i++)
    {
            ocx[i][1] = Bin4ToHex(str,pos);
            pos-=4;
            ocx[i][0] = Bin3ToHex(str,pos);
            pos-=3;
    }
}
int main(int argc,char*argv[])
{
    const int SIZE = 64,oct_size=2;
    char**oct=(char**)malloc(sizeof(char*)*SIZE);
    char**sep=(char**)malloc(sizeof(char*)*SIZE);
    char**octx=(char**)malloc(sizeof(char*)*SIZE);
    for(int i=0;i<SIZE;i++)
    {
        oct[i]=(char*)malloc(sizeof(char)*oct_size);
        sep[i]=(char*)malloc(sizeof(char)*8);
        octx[i]=(char*)malloc(sizeof(char)*oct_size);
    }
    printf("%d\n",argc);
    int i = 1;
    while(i<argc)
    {
        oct[i-1][0]=argv[i][0];
        oct[i-1][1]=argv[i][1];
        printf("%s\n",oct[i-1]);
        //printf(argv[i]);
        //printf(argv[i]);
        i++;
    }
    HexToBin(oct,sep,SIZE,oct_size);
    for(int i=0;i<argc-1;i++)
    {
        printf("%s\n",sep[i]);//
    }

    char*str=(char*)malloc(sizeof(char)*(argc-1)*8);
    for(int i=argc-1;i>-1;i--)
        strcat(str,sep[i]);
    printf("%s\n",str);
    BinToHex(str,octx,SIZE,oct_size);
    for(int i=0;i<argc;i++)//if error use i<argc-1
    {
        printf("%s ",octx[i]);
    }
    for(int i=0;i<SIZE;i++)
    {
        free(sep[i]);
        free(oct[i]);
        free(octx[i]);
    }
    free(oct);
    free(octx);
    free(sep);
    free(str);
    getchar();
    return 0;
}