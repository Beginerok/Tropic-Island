#include "sr/Cn.h"
#include <iostream>
using namespace std;
Cn *cn;
const int n = 256;
char text[n];
void p()
{
    while(true)
    {
        cn->ClearBuf();
        Sleep(1);
        cin>>text;
        cn->SetBuf(text);
        cn->Snd();
        if(text[0] == '0')
            break;
    }
}
void r()
{
    while(true)
    {
        cn->ClearBuf();
        Sleep(1);
        cn->Recv();
        cout<<cn->GetBuf()<<endl;
        if(cn->GetBuf()[0] == '0')
            break;
    }
}
int main(int argc, char *argv[])
{
	cn = new Cn(0);
	cout<<"input pn"<<endl;
	int prt;
	cin>>prt;
	cn->SetPrt(prt);
	cn->Init();
	cout<<"0 - for exit!"<<endl;
	r();
	cn->Close();
	system("pause");
	return 0;
}