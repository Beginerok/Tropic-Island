#include "Scene.h"
Scene::Scene()
{
    word=new char__[25];
    Data2=new uchar__[3145866];
    Texture=new uint__[92];
    glGenTextures(92,Texture);
    counttexture=0;
    counttexturecoor=35;
    texturecoordinats=new float__*[counttexturecoor];
    for(int__ i=0;i<counttexturecoor;i++)
        texturecoordinats[i]=new float__[4];
    countvertex=6;
    vertexcoordinats=new float__*[countvertex];
    for(int__ i=0;i<countvertex;i++)
        vertexcoordinats[i]=new float__[4];
    locatelinecoordinats=new float__***[21];
    for(int__ k=0;k<21;k++)
    {
        locatelinecoordinats[k]=new float__**[3];
        for(int__ i=0;i<3;i++)
        {
            locatelinecoordinats[k][i]=new float__*[6];
            for(int__ j=0;j<6;j++)
                locatelinecoordinats[k][i][j]=new float__[8];
        }
    }
    vecaa=new std::vector<int_>();
    veca=new std::vector<int_>();
    ves=new std::vector<int__>();
    SetData();
	oldbet=0;
    NewData=new uchar__[4*960*495];
    NewTexture=new uint__[1];
	NewTextureCoordinats=new float__[4];
}
void__ Scene::LoadData()
{
    for(std::vector<int_>::iterator iter=veca->begin();iter!=veca->end();iter++)
    {
        filereader->ReadFile((*ves)[counttexture],Data2);
        for(float__ i=0;i<(*iter).a*(*iter).b+18;i++)
        {
            int__ index=i*3;
            uchar__ R,G,B;
            G=Data2[index];
            R=Data2[index+1];
            B=Data2[index+2];
            Data2[index]=R;
            Data2[index+1]=G;
            Data2[index+2]=B;
        }
        glBindTexture(GL_TEXTURE_2D,Texture[counttexture]);
        gluBuild2DMipmaps(GL_TEXTURE_2D,3,(*iter).a,(*iter).b,GL_RGB,GL_UNSIGNED_BYTE,Data2);
        counttexture++;
    }
}
void__ Scene::LoadData2()
{
    for(std::vector<int_>::iterator iter=vecaa->begin();iter!=vecaa->end();iter++)
    {
        filereader->ReadFile((*ves)[counttexture],Data2);
        for(float__ i=0/*12.5*/;i<(*iter).a*(*iter).b+13.5;i++)
        {
            int__ index=i*4;
            uchar__ R,G,B,A;
            B=Data2[index];				//b
            G=Data2[index+1];//Green(B)//g
            A=Data2[index+2];//Red(G)//a
            R=Data2[index+3];//blue(R)//r
            Data2[index]=R;
            Data2[index+1]=G;//(G)
            Data2[index+2]=B;//(B)
            Data2[index+3]=A;//(R)
            //GBR
            //BGsR
        }
        glBindTexture(GL_TEXTURE_2D,Texture[counttexture]);
        //glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,Data);
        gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,(*iter).a,(*iter).b,GL_RGBA,GL_UNSIGNED_BYTE,Data2);
        counttexture++;
    }
}
void__ Scene::SetData()
{
    int_ i;
    i.a=256;
    i.b=256;
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    filereader=new FileReader();
    filereader->FileReader__("resource2.dat","r");
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    ves->push_back(196730);
    i.a=67;i.b=98;
    veca->push_back(i);
    i.a=39;i.b=95;
    veca->push_back(i);
    i.a=67;
    veca->push_back(i);
    i.b=98;
    veca->push_back(i);
    i.a=68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    i.a=68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    ves->push_back(20114);
    ves->push_back(11522);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    i.a=128;i.b=8;
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    veca->push_back(i);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    ves->push_back(3194);
    i.a=39;i.b=95;
    veca->push_back(i);
    i.a=67;
    veca->push_back(i);
    i.b=98;
    veca->push_back(i);
    i.a=68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    i.a=68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    ves->push_back(11522);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    i.a=39;i.b=95;
    veca->push_back(i);
    i.a=67;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    i.a=68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    i.a= 68;i.b=95;
    veca->push_back(i);
    i.a=67;i.b=98;
    veca->push_back(i);
    veca->push_back(i);
    ves->push_back(11522);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    ves->push_back(19502);
    ves->push_back(20114);
    ves->push_back(20114);
    i.a=92;i.b=97;
    veca->push_back(i);
    i.a=71;
    veca->push_back(i);
    i.a=79;i.b=101;
    veca->push_back(i);
    i.a=83;i.b=97;
    veca->push_back(i);
    i.a=67;
    veca->push_back(i);
    i.a=20;
    veca->push_back(i);
    i.a=63;
    veca->push_back(i);
    i.a=75;
    veca->push_back(i);
    i.a=92;i.b=101;
    veca->push_back(i);
    i.a=79;i.b=97;
    veca->push_back(i);
    i.a=71;i.b=101;
    veca->push_back(i);
    i.a=83;i.b=97;
    veca->push_back(i);
    i.a=123;
    veca->push_back(i);
    i.a=8;i.b=8;
    veca->push_back(i);
    ves->push_back(26894);
    ves->push_back(21074);
    ves->push_back(24362);
    ves->push_back(24566);
    ves->push_back(19910);
    ves->push_back(5942);
    ves->push_back(18746);
    ves->push_back(22238);
    ves->push_back(27998);
    ves->push_back(23402);
    ves->push_back(21938);
    ves->push_back(24566);
    ves->push_back(36206);
    ves->push_back(314);
    i.a=79;i.b=101;
    veca->push_back(i);
    i.a=67;i.b=97;
    veca->push_back(i);
    i.a=20;
    veca->push_back(i);
    i.a=63;
    veca->push_back(i);
    i.a=75;
    veca->push_back(i);
    i.a=63;
    veca->push_back(i);
    i.a=79;
    veca->push_back(i);
    i.b=99;
    veca->push_back(i);
    i.a=80;i.b=97;
    veca->push_back(i);
    i.a=84;i.b=41;
    veca->push_back(i);
    i.a=8;i.b=8;
    veca->push_back(i);
    ves->push_back(24362);
    ves->push_back(19910);
    ves->push_back(5942);
    ves->push_back(18746);
    ves->push_back(22238);
    ves->push_back(18746);
    ves->push_back(23402);
    ves->push_back(23882);
    ves->push_back(23402);
    ves->push_back(10454);
    ves->push_back(314);
    LoadData();
    i.a=88;i.b=61;
    vecaa->push_back(i);
    vecaa->push_back(i);
    vecaa->push_back(i);
    i.a=86;
    vecaa->push_back(i);
    vecaa->push_back(i);
    vecaa->push_back(i);
    i.a=88;i.b=63;
    vecaa->push_back(i);
    vecaa->push_back(i);
    vecaa->push_back(i);
    i.a=85;i.b=61;
    vecaa->push_back(i);
    vecaa->push_back(i);
    vecaa->push_back(i);
    i.a=82;
    vecaa->push_back(i);
    vecaa->push_back(i);
    vecaa->push_back(i);
    i.a=1024;i.b=768;
    vecaa->push_back(i);
    ves->push_back(21594);
    ves->push_back(21594);
    ves->push_back(21594);
    ves->push_back(21106);
    ves->push_back(21106);
    ves->push_back(21106);
    ves->push_back(22298);
    ves->push_back(22298);
    ves->push_back(22298);
    ves->push_back(20862);
    ves->push_back(20862);
    ves->push_back(20862);
    ves->push_back(20130);
    ves->push_back(20130);
    ves->push_back(20130);
    ves->push_back(3145866);
    LoadData2();
    //filereader->~FileReader();
	delete filereader;
	SetVerteces();
}
void__ Scene::SetVerteces()
{
    filereader=new FileReader();
    filereader->FileReader__("tre.xml","r");
    Vector3*vec=new Vector3();
    filereader->GetStroke();
    int__ count_=0;
    while(filereader->Opened())
    {
        vec->a[0]=filereader->BConvert(2);
        vec->a[1]=filereader->BConvert(1);
        vec->a[2]=filereader->BConvert(0);
        count_++;
        listv.push_back((*vec));
        filereader->GetStroke();
    }
    filereader->~FileReader();
    texturecoordinats[0][0]=1.14f;
    texturecoordinats[0][1]=0.18f;
    texturecoordinats[0][2]=1.0f;
    texturecoordinats[0][3]=0.01f;
    vec->a[0]=texturecoordinats[0][0];
    vec->a[1]=texturecoordinats[0][1];
    int__ n=3;
    for(int__ i=0;i<n;i++)
    {
        vec->a[2]=texturecoordinats[0][3]+(texturecoordinats[0][2]-texturecoordinats[0][3])*i/(n-1);
        listt.push_back((*vec));
    }
    n=9;
    for(int__ i=0;i<n;i++)
    {
        vec->a[2]=texturecoordinats[0][3]+(texturecoordinats[0][2]-texturecoordinats[0][3])*i/(n-1);
        listt.push_back((*vec));
    }
    vertexcoordinats[0][0]=1.f;
    vertexcoordinats[0][1]=-1.0f;
    vertexcoordinats[0][2]=1.f;
    vertexcoordinats[0][3]=-1.f;
    texturecoordinats[10][0]=1.03f;
    texturecoordinats[10][1]=0.04f;
    texturecoordinats[10][2]=1.f;
    texturecoordinats[10][3]=0.0f;
    for(int__ i=0;i<10;i++)
    {
        texturecoordinats[i][0]=.6f;
        texturecoordinats[i][1]=-0.3f;
        texturecoordinats[i][2]=1.0f;
        texturecoordinats[i][3]=0.01f;
    }
    texturecoordinats[1][0]=1.f;
    texturecoordinats[1][1]=.0f;
    texturecoordinats[1][2]=.95f;
    texturecoordinats[1][3]=0.01f;
    vertexcoordinats[1][0]=-.52f;
    vertexcoordinats[1][1]=-.32f;
    vertexcoordinats[1][2]=-.6f;
    vertexcoordinats[1][3]=-.8f;
    vertexcoordinats[2][0]=-.31f;
    vertexcoordinats[2][1]=-.11f;
    vertexcoordinats[2][2]=-.6f;
    vertexcoordinats[2][3]=-.8f;
    vertexcoordinats[3][0]=-.1f;
    vertexcoordinats[3][1]=.1f;
    vertexcoordinats[3][2]=-.6f;
    vertexcoordinats[3][3]=-.8f;
    vertexcoordinats[4][0]=.11f;
    vertexcoordinats[4][1]=.31f;
    vertexcoordinats[4][2]=-.6f;
    vertexcoordinats[4][3]=-.8f;
    vertexcoordinats[5][0]=.32f;
    vertexcoordinats[5][1]=.52f;
    vertexcoordinats[5][2]=-.6f;
    vertexcoordinats[5][3]=-.8f;
    texturecoordinats[11][0]=.35f;
    texturecoordinats[11][1]=1.35f;
    texturecoordinats[11][2]=1.f;
    texturecoordinats[11][3]=.0f;
    texturecoordinats[12][0]=.38f;
    texturecoordinats[12][1]=1.35f;
    texturecoordinats[12][2]=1.0f;
    texturecoordinats[12][3]=0.0f;
    texturecoordinats[13][0]=.35f;
    texturecoordinats[13][1]=1.35f;
    texturecoordinats[13][2]=1.0f;
    texturecoordinats[13][3]=0.0f;
    texturecoordinats[14][0]=.38f;
    texturecoordinats[14][1]=1.35f;
    texturecoordinats[14][2]=1.0f;
    texturecoordinats[14][3]=0.0f;
    texturecoordinats[15][0]=.38f;
    texturecoordinats[15][1]=1.38f;
    texturecoordinats[15][2]=1.0f;
    texturecoordinats[15][3]=0.0f;
    texturecoordinats[16][0]=.5f;
    texturecoordinats[16][1]=-0.6f;
    texturecoordinats[16][2]=1.0f;
    texturecoordinats[16][3]=0.01f;
    texturecoordinats[17][0]=.6f;
    texturecoordinats[17][1]=-0.3f;
    texturecoordinats[17][2]=1.0f;
    texturecoordinats[17][3]=0.01f;
    texturecoordinats[18][0]=.5f;
    texturecoordinats[18][1]=-0.49f;
    texturecoordinats[18][2]=0.991f;
    texturecoordinats[18][3]=0.01f;
    texturecoordinats[19][0]=.5f;
    texturecoordinats[19][1]=-0.45f;
    texturecoordinats[19][2]=1.0f;
    texturecoordinats[19][3]=0.01f;
    texturecoordinats[20][0]=.6f;
    texturecoordinats[20][1]=-0.3f;
    texturecoordinats[20][2]=1.0f;
    texturecoordinats[20][3]=0.01f;
    texturecoordinats[21][0]=.89f;
    texturecoordinats[21][1]=.25f;
    texturecoordinats[21][2]=.9f;
    texturecoordinats[21][3]=.1f;
    texturecoordinats[22][0]=.6f;
    texturecoordinats[22][1]=-0.3f;
    texturecoordinats[22][2]=1.0f;
    texturecoordinats[22][3]=0.01f;
    texturecoordinats[23][0]=.6f;
    texturecoordinats[23][1]=-0.5f;
    texturecoordinats[23][2]=1.0f;
    texturecoordinats[23][3]=0.01f;
    texturecoordinats[24][0]=.5f;
    texturecoordinats[24][1]=-0.5f;
    texturecoordinats[24][2]=1.0f;
    texturecoordinats[24][3]=0.01f;
    texturecoordinats[25][0]=.6f;
    texturecoordinats[25][1]=-0.3f;
    texturecoordinats[25][2]=1.0f;
    texturecoordinats[25][3]=0.01f;
    texturecoordinats[26][0]=.5f;
    texturecoordinats[26][1]=-0.45f;
    texturecoordinats[26][2]=0.98f;
    texturecoordinats[26][3]=0.01f;
    texturecoordinats[27][0]=.6f;
    texturecoordinats[27][1]=-0.3f;
    texturecoordinats[27][2]=1.0f;
    texturecoordinats[27][3]=0.01f;
    texturecoordinats[28][0]=.5f;
    texturecoordinats[28][1]=-0.4f;
    texturecoordinats[28][2]=1.0f;
    texturecoordinats[28][3]=0.01f;
    texturecoordinats[29][0]=.5f;
    texturecoordinats[29][1]=-0.4f;
    texturecoordinats[29][2]=1.0f;
    texturecoordinats[29][3]=0.01f;
    texturecoordinats[30][0]=.3f;
    texturecoordinats[30][1]=-0.6f;
    texturecoordinats[30][2]=1.0f;
    texturecoordinats[30][3]=0.01f;
    texturecoordinats[31][0]=.6f;
    texturecoordinats[31][1]=-0.3f;
    texturecoordinats[31][2]=1.0f;
    texturecoordinats[31][3]=0.01f;
    texturecoordinats[32][0]=.6f;
    texturecoordinats[32][1]=-0.3f;
    texturecoordinats[32][2]=0.9f;
    texturecoordinats[32][3]=0.8f;
    texturecoordinats[33][0]=.44f;
    texturecoordinats[33][1]=0.06f;
    texturecoordinats[33][2]=1.0f;
    texturecoordinats[33][3]=0.05f;
    texturecoordinats[34][0]=0.95f;
    texturecoordinats[34][1]=0.4f;
    texturecoordinats[34][2]=0.8f;
    texturecoordinats[34][3]=0.05f;
    float__ dc=0.0;
    for(int__ c=0;c<21;c++)
        for(int__ a=0;a<3;a++)
            for(int__ b=0;b<6;b++)
            {
                locatelinecoordinats[c][a][b][0]=-1.5f+(b+3)*0.3f;
                locatelinecoordinats[c][a][b][1]=-1.5f+(b+2)*0.3f;
                if(c==3||c==7)
                    dc=-0.05;
                if(c==5)
                    dc=-0.1;
                if(c==9)
                    dc=0.05;
                if(c==11)
                    dc=0.1;
                if(c==13)
                    dc=0.05;
                if(c==17)
                    dc=0.0;
                locatelinecoordinats[c][a][b][2]=1.f-.4f*(a+1)-0.17+dc;
                locatelinecoordinats[c][a][b][3]=1.f-.4f*(a+1)-0.21+dc;
                locatelinecoordinats[c][a][b][4]=1.f-.4f*(a+2)-0.17+dc;
                locatelinecoordinats[c][a][b][5]=1.f-.4f*(a+2)-0.21+dc;
                locatelinecoordinats[c][a][b][6]=1.f-.4f*a-0.17f+dc;
                locatelinecoordinats[c][a][b][7]=1.f-.4f*a-0.21f+dc;
            }
}
void__ Scene::ShowLine(int__ bet,bool__*lines,int__**ms)
{
    for(int__ iline=0;iline<bet;iline++)
    {
        if(lines[iline]||oldbet!=bet)
        {
            glBindTexture(GL_TEXTURE_2D,GetLineTexture(iline));
            int__ beg=ms[iline][0]-1;
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg,0),1.f,0);
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg-=0,1),1.f,ms[iline][0]-ms[iline][1]);
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg-=ms[iline][0]-ms[iline][1],2),1.f,ms[iline][1]-ms[iline][2]);
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg-=ms[iline][1]-ms[iline][2],3),1.f,ms[iline][2]-ms[iline][3]);
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg-=ms[iline][2]-ms[iline][3],4),1.f,ms[iline][3]-ms[iline][4]);
            EnableTexture(GetTextureLineCoordinats(),GetLocateLineCoordinats(iline,beg-=ms[iline][3]-ms[iline][4],5),1.f,0);
        }
    }
	if(oldbet!=bet&&clock()-time_visible/CLOCKS_PER_SEC>5)
	{
		oldbet=bet;
		time_visible=clock();
	}
}
void__ Scene::EnableTexture(float__*texcoor, float__*vercoor)
{
    glBegin(GL_QUADS);
    glTexCoord2f(texcoor[0],texcoor[2]);
    glVertex2f(vercoor[0],vercoor[2]);
    glTexCoord2f(texcoor[1],texcoor[2]);
    glVertex2f(vercoor[1],vercoor[2]);
    glTexCoord2f(texcoor[1],texcoor[3]);
    glVertex2f(vercoor[1],vercoor[3]);
    glTexCoord2f(texcoor[0],texcoor[3]);
    glVertex2f(vercoor[0],vercoor[3]);
    glEnd();
}
void__ Scene::EnableTexture(float__*texcoor,float__*vercoor,GLfloat third,int__ voshod)
{
    switch (voshod)
    {
        case -1:
        {
            glBegin(GL_POLYGON);
            glTexCoord2f(texcoor[0],texcoor[2]);
            glVertex3f(vercoor[0],vercoor[4],third);
            glTexCoord2f(texcoor[1],texcoor[2]);
            glVertex3f(vercoor[1],vercoor[2],third);
            glTexCoord2f(texcoor[1],texcoor[3]);
            glVertex3f(vercoor[1],vercoor[3],third);
            glTexCoord2f(texcoor[0],texcoor[3]);
            glVertex3f(vercoor[0],vercoor[5],third);
            glEnd();
            break;
        }
        case 0:
        {
            glBegin(GL_QUADS);
            glTexCoord2f(texcoor[0],texcoor[2]);
            glVertex3f(vercoor[0],vercoor[2],third);
            glTexCoord2f(texcoor[1],texcoor[2]);
            glVertex3f(vercoor[1],vercoor[2],third);
            glTexCoord2f(texcoor[1],texcoor[3]);
            glVertex3f(vercoor[1],vercoor[3],third);
            glTexCoord2f(texcoor[0],texcoor[3]);
            glVertex3f(vercoor[0],vercoor[3],third);
            glEnd();
            break;
        }
        case 1:
        {
            glBegin(GL_POLYGON);
            glTexCoord2f(texcoor[0],texcoor[2]);
            glVertex3f(vercoor[0],vercoor[6],third);
            glTexCoord2f(texcoor[1],texcoor[2]);
            glVertex3f(vercoor[1],vercoor[2],third);
            glTexCoord2f(texcoor[1],texcoor[3]);
            glVertex3f(vercoor[1],vercoor[3],third);
            glTexCoord2f(texcoor[0],texcoor[3]);
            glVertex3f(vercoor[0],vercoor[7],third);
            glEnd();
            break;
        }
    }
}
void__ Scene::EnableTexture(int__ n,int__ m)
{
    float__ _width_=0.188f;
    int__ k=5-n*2;
    switch (m)
    {
        case 0:
        {
            glBegin(GL_POLYGON);
            for(int__ i=1,j=3;i<10;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=9,j=11;i>0;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 1:
        {
            glBegin(GL_POLYGON);
            for(int__ i=9,j=3;i<18;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=17,j=11;i>8;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 2:
        {
            glBegin(GL_POLYGON);
            for(int__ i=17,j=0;i<20;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=19,j=2;i>16;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 3:
        {
            glBegin(GL_POLYGON);
            for(int__ i=19,j=3;i<28;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=27,j=11;i>18;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 4:
        {
            glBegin(GL_POLYGON);
            for(int__ i=27,j=3;i<36;i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=35,j=11;i>26;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
        case 5:
        {
            glBegin(GL_POLYGON);
            for(int__ i=35,j=0;i<(int__)listv.size();i++,j++)
            {
                glTexCoord2f(listt[j].a[1],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*k,listv[i].a[1],listv[i].a[2]);
            }
            for(int__ i=(int__)listv.size()-1,j=2;i>34;i--,j--)
            {
                glTexCoord2f(listt[j].a[0],listt[j].a[2]);
                glVertex3f(listv[i].a[0]+_width_*(k-2),listv[i].a[1],listv[i].a[2]);
            }
            glEnd();
            break;
        }
    }
}
void__ Scene::EnableTextureNum(float__*texcoor,int__ position,Coor*coor_,bool__ vert)
{
    glBegin(GL_QUADS);
    if(!vert){
        glTexCoord2f(texcoor[0],texcoor[2]);
        glVertex2f(coor_->a[position]+coor_->width,coor_->b+coor_->height);
        glTexCoord2f(texcoor[1],texcoor[2]);
        glVertex2f(coor_->a[position],coor_->b+coor_->height);
        glTexCoord2f(texcoor[1],texcoor[3]);
        glVertex2f(coor_->a[position],coor_->b);
        glTexCoord2f(texcoor[0],texcoor[3]);
        glVertex2f(coor_->a[position]+coor_->width,coor_->b);
    }
    else{
        glTexCoord2f(texcoor[0],texcoor[2]);
        glVertex2f(coor_->b+coor_->height,coor_->a[position]+coor_->width);
        glTexCoord2f(texcoor[0],texcoor[3]);
        glVertex2f(coor_->b+coor_->height,coor_->a[position]);
        glTexCoord2f(texcoor[1],texcoor[3]);
        glVertex2f(coor_->b,coor_->a[position]);
        glTexCoord2f(texcoor[1],texcoor[2]);
        glVertex2f(coor_->b,coor_->a[position]+coor_->width);
    }
    glEnd();
}
uint__ Scene::GetTexture(int__ num)
{
    return Texture[num];
}
float__*Scene::GetTextureCoordinats(int__ i)
{
    return texturecoordinats[i];
}
float__*Scene::GetVertexCoordinats(int__ i)
{
    return vertexcoordinats[i];
}
uint__ Scene::GetNumTexture(int__ num,int__ color)
{
    int__ off;
    switch(color)
    {
        case 0:
        {
            off=14;
            break;
        }
        case 1:
        {
            off=33;
            break;
        }
        case 2:
        {
            off=42;
            break;
        }
        default:
        {
            off=0;
            break;
        }
    }
    return GetTexture(off+num);
}
float__*Scene::GetTextureNumCoordinats(int__ num)
{
    return GetTextureCoordinats(num);
}
int__ LtoN(int__ l,bool__ inc_)
{
    int__ n,inc;
    switch(l)
    {
        case 0:
        {
            n=1;
            inc=2;
            break;
        }
        case 1:
        {
            n=1;
            inc=1;
            break;
        }
        case 2:
        {
            n=1;
            inc=0;
            break;
        }
        case 3:
        {
            n=2;
            inc=1;
            break;
        }
        case 4:
        {
            n=2;
            inc=0;
            break;
        }
        case 5:
        {
            n=3;
            inc=1;
            break;
        }
        case 6:
        {
            n=3;
            inc=0;
            break;
        }
        case 7:
        {
            n=4;
            inc=1;
            break;
        }
        case 8:
        {
            n=4;
            inc=0;
            break;
        }
        case 9:
        {
            n=5;
            inc=1;
            break;
        }
        case 10:
        {
            n=5;
            inc=0;
            break;
        }
        case 11:
        {
            n=6;
            inc=1;
            break;
        }
        case 12:
        {
            n=6;
            inc=0;
            break;
        }
        case 13:
        {
            n=7;
            inc=1;
            break;
        }
        case 14:
        {
            n=7;
            inc=0;
            break;
        }
        case 15:
        {
            n=8;
            inc=1;
            break;
        }
        case 16:
        {
            n=8;
            inc=0;
            break;
        }
        case 17:
        {
            n=9;
            inc=3;
            break;
        }
        case 18:
        {
            n=9;
            inc=2;
            break;
        }
        case 19:
        {
            n=9;
            inc=1;
            break;
        }
        case 20:
        {
            n=9;
            break;
        }
        default:
        {
            n=10;
            inc=0;
            break;
        }
    }
    if(!inc_)
        return n;
    else
        return inc;
}
uint__ Scene::GetLineTexture(int__ n)
{
    return GetTexture(24+LtoN(n,false)-1);
}
float__*Scene::GetTextureLineCoordinats()
{
    return texturecoordinats[33];
}
float__*Scene::GetLocateLineCoordinats(int__ a,int__ b,int__ c)
{
    return locatelinecoordinats[a][b][c];
}
//#define _CRT_SECURE_NO_WARNINGS
void__ Scene::DrawWord(int__ word_,Coor*coor_,int__ kaxb,bool__ vert){
#ifndef _WINDOWS_2
	sprintf(word,"%d",word_);
#else
	sprintf_s(word,25,"%d",word_);
#endif
	for(int__ i=0;i<strlen(word);i++)
        coor_->a.push_back(coor_->a[i]-coor_->width);
    for(int__ i=0,j=strlen(word)-1;i<strlen(word);i++,j--){
        glBindTexture(GL_TEXTURE_2D,GetSymbolTexture(word[j],kaxb));
        EnableTextureNum(GetTextureWordCoordinats(word[j]),i,coor_,vert);
    }
}
void__ Scene::DrawWord(const char__*word_,Coor*coor_,int__ kaxb,bool__ vert){
#ifndef _WINDOWS_2
	strcpy(word, word_);
#else
	strcpy_s(word,25, word_);
#endif
	for(int__ i=0;i<strlen(word);i++)
        coor_->a.push_back(coor_->a[i]+coor_->width);
    for(int__ i=0,j=strlen(word)-1;i<strlen(word);i++,j--){
            glBindTexture(GL_TEXTURE_2D,GetSymbolTexture(word[j],kaxb));
            EnableTextureNum(GetTextureWordCoordinats(word[j]),i,coor_,vert);
    }
}
void__ Scene::ShowReservedWords(int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet){
    std::vector<Coor*>coor;
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.4f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(credits,coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.15f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(win,coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.7f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(totalbet,coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.735f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("stiderc",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.19f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("niw",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.36f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("teb latot",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.51f);
    coor[coor.size()-1]->width=0.025f;
    coor[coor.size()-1]->b=-0.86f;
    coor[coor.size()-1]->height=0.06f;
    DrawWord("rur 1 = rc 1",coor[coor.size()-1],false,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.22f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=-0.825f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("enil ezirp",coor[coor.size()-1],false,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.2f);
    coor[coor.size()-1]->width=0.03f;
    coor[coor.size()-1]->b=-0.9f;
    coor[coor.size()-1]->height=0.07f;
    DrawWord(line,coor[coor.size()-1],false,false);
    int__ bet_;
    switch(bet)
    {
        case 3:
        {
            bet_=1;
            break;
        }
        case 5:
        {
            bet_=21;
            break;
        }
        case 7:
        {
            bet_=321;
            break;
        }
        case 9:
        {
            bet_=4321;
            break;
        }
        case 11:
        {
            bet_=54321;
            break;
        }
        case 13:
        {
            bet_=654321;
            break;
        }
        case 15:
        {
            bet_=7654321;
            break;
        }
        case 17:
        {
            bet_=87654321;
            break;
        }
        case 21:
        {
            bet_=987654321;
            break;
        }
    }
    coor.push_back(new Coor());
    coor[coor.size()-1]->b=-0.984f;
    coor[coor.size()-1]->height=0.03f;
    coor[coor.size()-1]->width=0.06f;
    coor[coor.size()-1]->a.push_back(-0.06f);
    coor[coor.size()-1]->a.push_back(0.5f);
    coor[coor.size()-1]->a.push_back(-0.61f);
    coor[coor.size()-1]->a.push_back(0.28f);
    coor[coor.size()-1]->a.push_back(-0.39f);
    coor[coor.size()-1]->a.push_back(0.39f);
    coor[coor.size()-1]->a.push_back(-0.5f);
    coor[coor.size()-1]->a.push_back(-0.17f);
    coor[coor.size()-1]->a.push_back(0.05f);
    DrawWord(bet_,coor[coor.size()-1],2,true);
    coor.push_back(new Coor());
    coor[coor.size()-1]->b=0.952f;
    coor[coor.size()-1]->height=0.03f;
    coor[coor.size()-1]->width=0.06f;
    coor[coor.size()-1]->a.push_back(-0.06f);
    coor[coor.size()-1]->a.push_back(0.5f);
    coor[coor.size()-1]->a.push_back(-0.61f);
    coor[coor.size()-1]->a.push_back(0.28f);
    coor[coor.size()-1]->a.push_back(-0.39f);
    coor[coor.size()-1]->a.push_back(0.39f);
    coor[coor.size()-1]->a.push_back(-0.5f);
    coor[coor.size()-1]->a.push_back(-0.17f);
    coor[coor.size()-1]->a.push_back(0.05f);
    DrawWord(bet_,coor[coor.size()-1],2,true);
	coor.clear();
    return;
}
uint__ Scene::GetButtonTexture(int__ num,int__ button)
{
    return GetTexture(77+num*3-button);
}
void__ Scene::ShowButtons(bool__*buttons)
{
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
	int__ n=0,j=0;
    for(int__ i=0;i<5;i++)
		if(buttons[i])
		{
			n=2;
			j=1;
		}
    for(int__ i=0;i<5;i++)
    {
	    glBindTexture(GL_TEXTURE_2D,GetButtonTexture(i,j-buttons[i]*n));
        EnableTexture(GetTextureCoordinats(11+i),GetVertexCoordinats(1+i));
    }
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
}
void__ Scene::ShowBoth()
{
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_BLEND);
    glBindTexture(GL_TEXTURE_2D,GetTexture(91));
    EnableTexture(GetTextureCoordinats(10),GetVertexCoordinats(0));
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
}
void__ Scene::Show(int__ countdrums,float__*rotate_,int__ counttextureondrums,int__**drum,int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet,bool__*lines,int__**ms,bool__*buttons)
{
    glPushMatrix();
    glRotatef(180,0,0,1);
    for(int__ i=0;i<countdrums;i++)
    {
        glPushMatrix();
        glRotatef(rotate_[i],1,0,0);
        for(int__ j=0;j<counttextureondrums;j++)
        {
            glBindTexture(GL_TEXTURE_2D,GetTexture(drum[i][j]-4));
            EnableTexture(i,j);
        }
        glPopMatrix();
    }
    glPopMatrix();
    ShowBoth();
    ShowButtons(buttons);
    ShowReservedWords(credits,win,totalbet,line,bet);
    ShowLine(bet,lines,ms);
}
void__ Scene::Show2(int__ credits,int__ win,int__ totalbet,bool__*buttons)
{
	ShowBackGround();
    ShowButtons(buttons);
    ShowReservedWords2(credits,win,totalbet);
}

void__ Scene::ShowBackGround()
{
	filereader->FileReader__("J:\\фукрпкявамчс\\content\\Загрузки\\table.bmp","r");
	filereader->ReadFile(960*495*4,NewData);
	for(float__ i=54;i<960*495;i++)
    {
        int__ index=i*4;
        uchar__ R,G,B,A;

		R=NewData[index];				//R
        A=NewData[index+1];//Green(B)	//G
        B=NewData[index+2];//Red(G)		//A
        G=NewData[index+3];//blue(R)	//B
        NewData[index]=R;
        NewData[index+1]=G;//(G)
        NewData[index+2]=B;//(B)
        NewData[index+3]=A;//(R)
        //GBR
        //BGsR
    }
    glBindTexture(GL_TEXTURE_2D,NewTexture[0]);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,960,495,GL_RGBA,GL_UNSIGNED_BYTE,NewData);
    NewTextureCoordinats[0]=0.955f;
    NewTextureCoordinats[1]=0.06f;
    NewTextureCoordinats[2]=1.f;
    NewTextureCoordinats[3]=0.08f;
	EnableTexture(NewTextureCoordinats,GetVertexCoordinats(0));
	return;
}
void__ Scene::ShowReservedWords2(int__ credits,int__ win,int__ totalbet){
    std::vector<Coor*>coor;
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.4f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(credits,coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.15f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(win,coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.7f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord(totalbet,coor[coor.size()-1],true,false);
	coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.735f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("stiderc",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.19f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("niw",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(0.36f);
    coor[coor.size()-1]->width=0.02f;
    coor[coor.size()-1]->b=0.88f;
    coor[coor.size()-1]->height=0.05f;
    DrawWord("teb latot",coor[coor.size()-1],true,false);
    coor.push_back(new Coor());
    coor[coor.size()-1]->a.push_back(-0.51f);
    coor[coor.size()-1]->width=0.025f;
    coor[coor.size()-1]->b=-0.86f;
    coor[coor.size()-1]->height=0.06f;
    DrawWord("rur 1 = rc 1",coor[coor.size()-1],false,false);
    coor.clear();
    return;
}
uint__ Scene::GetAlphabetTexture(int__ i,int__ color)
{
    int off;
    switch(color)
    {
        case 0:
        {
            off=51;
            break;
        }
        case 1:
        {
            off=65;
            break;
        }
        default:
        {
            off=0;
            break;
        }
    }
    return GetTexture(off+i);
}
uint__ Scene::GetSymbolTexture(char__ str,int__ black)
{
    if(black==2)
        switch(str)
        {
            case '1':
            {
                return GetNumTexture(0,2);
                break;
            }
            case '2':
            {
                return GetNumTexture(1,2);
                break;
            }
            case '3':
            {
                return GetNumTexture(2,2);
                break;
            }
            case '4':
            {
                return GetNumTexture(3,2);
                break;
            }
            case '5':
            {
                return GetNumTexture(4,2);
                break;
            }
            case '6':
            {
                return GetNumTexture(5,2);
                break;
            }
            case '7':
            {
                return GetNumTexture(6,2);
                break;
            }
            case '8':
            {
                return GetNumTexture(7,2);
                break;
            }
            case '9':
            {
                return GetNumTexture(8,2);
                break;
            }

        }
    if(black==1)
        switch(str)
        {
            case '1':
            {
                return GetNumTexture(1,0);
                break;
            }
            case '2':
            {
                return GetNumTexture(2,0);
                break;
            }
            case '3':
            {
                return GetNumTexture(3,0);
                break;
            }
            case '4':
            {
                return GetNumTexture(4,0);
                break;
            }
            case '5':
            {
                return GetNumTexture(5,0);
                break;
            }
            case '6':
            {
                return GetNumTexture(6,0);
                break;
            }
            case '7':
            {
                return GetNumTexture(7,0);
                break;
            }
            case '8':
            {
                return GetNumTexture(8,0);
                break;
            }
            case '9':
            {
                return GetNumTexture(9,0);
                break;
            }
            case '0':
            {
                return GetNumTexture(0,0);
                break;
            }
            case 'a':
            {
                return GetAlphabetTexture(0,0);
                break;
            }
            case 'b':
            {
                return GetAlphabetTexture(1,0);
                break;
            }
            case 'c':
            {
                return GetAlphabetTexture(2,0);
                break;
            }
            case 'd':
            {
                return GetAlphabetTexture(3,0);
                break;
            }
            case 'e':
            {
                return GetAlphabetTexture(4,0);
                break;
            }
            case 'i':
            {
                return GetAlphabetTexture(5,0);
                break;
            }
            case 'l':
            {
                return GetAlphabetTexture(6,0);
                break;
            }
            case 'n':
            {
                return GetAlphabetTexture(7,0);
                break;
            }
            case 'o':
            {
                return GetAlphabetTexture(8,0);
                break;
            }
            case 'r':
            {
                return GetAlphabetTexture(9,0);
                break;
            }
            case 's':
            {
                return GetAlphabetTexture(10,0);
                break;
            }
            case 't':
            {
                return GetAlphabetTexture(11,0);
                break;
            }
            case 'w':
            {
                return GetAlphabetTexture(12,0);
                break;
            }
            case ' ':
            {
                return GetAlphabetTexture(13,0);
            }
        }
    if(black==0)
        switch(str)
        {
            case '1':
            {
                return GetNumTexture(0,1);
                break;
            }
            case '2':
            {
                return GetNumTexture(1,1);
                break;
            }
            case '3':
            {
                return GetNumTexture(2,1);
                break;
            }
            case '4':
            {
                return GetNumTexture(3,1);
                break;
            }
            case '5':
            {
                return GetNumTexture(4,1);
                break;
            }
            case '6':
            {
                return GetNumTexture(5,1);
                break;
            }
            case '7':
            {
                return GetNumTexture(6,1);
                break;
            }
            case '8':
            {
                return GetNumTexture(7,1);
                break;
            }
            case '9':
            {
                return GetNumTexture(8,1);
                break;
            }
            case 'c':
            {
                return GetAlphabetTexture(0,1);
                break;
            }
            case 'e':
            {
                return GetAlphabetTexture(1,1);
                break;
            }
            case 'i':
            {
                return GetAlphabetTexture(2,1);
                break;
            }
            case 'l':
            {
                return GetAlphabetTexture(3,1);
                break;
            }
            case 'n':
            {
                return GetAlphabetTexture(4,1);
                break;
            }
            case 'p':
            {
                return GetAlphabetTexture(5,1);
                break;
            }
            case 'r':
            {
                return GetAlphabetTexture(6,1);
                break;
            }
            case 'u':
            {
                return GetAlphabetTexture(7,1);
                break;
            }
            case 'z':
            {
                return GetAlphabetTexture(8,1);
                break;
            }
            case '=':
            {
                return GetAlphabetTexture(9,1);
                break;
            }
            case ' ':
            {
                return GetAlphabetTexture(10,1);
                break;
            }
        }
    return 0;
}
float__*Scene::GetTextureWordCoordinats(char__ str)
{
    switch(str)
    {
        case'1':
        {
            return GetTextureNumCoordinats(1);
            break;
        }
        case'2':
        {
            return GetTextureNumCoordinats(2);
            break;
        }
        case'3':
        {
            return GetTextureNumCoordinats(3);
            break;
        }
        case'4':
        {
            return GetTextureNumCoordinats(4);
            break;
        }
        case'5':
        {
            return GetTextureNumCoordinats(5);
            break;
        }
        case'6':
        {
            return GetTextureNumCoordinats(6);
            break;
        }
        case'7':
        {
            return GetTextureNumCoordinats(7);
            break;
        }
        case'8':
        {
            return GetTextureNumCoordinats(8);
            break;
        }
        case'9':
        {
            return GetTextureNumCoordinats(9);
            break;
        }
        case'0':
        {
            return GetTextureNumCoordinats(0);
            break;
        }
        case 'a':
        {
            return GetTextureCoordinats(16);//7
            break;
        }
        case 'b':
        {
            return GetTextureCoordinats(17);
            break;
        }
        case 'c':
        {
            return GetTextureCoordinats(18);
            break;
        }
        case 'd':
        {
            return GetTextureCoordinats(19);
            break;
        }
        case 'e':
        {
            return GetTextureCoordinats(20);
            break;
        }
        case 'i':
        {
            return GetTextureCoordinats(21);
            break;
        }
        case 'l':
        {
            return GetTextureCoordinats(22);
            break;
        }
        case 'n':
        {
            return GetTextureCoordinats(23);
            break;
        }
        case 'o':
        {
            return GetTextureCoordinats(24);
            break;
        }
        case 'p':
        {
            return GetTextureCoordinats(25);
            break;
        }
        case 'r':
        {
            return GetTextureCoordinats(26);
            break;
        }
        case 's':
        {
            return GetTextureCoordinats(27);
            break;
        }
        case 't':
        {
            return GetTextureCoordinats(28);
            break;
        }
        case 'u':
        {
            return GetTextureCoordinats(29);
            break;
        }
        case 'w':
        {
            return GetTextureCoordinats(30);
            break;
        }
        case 'z':
        {
            return GetTextureCoordinats(31);
            break;
        }
        case ' ':
        {
            return GetTextureCoordinats(32);
            break;
        }
        case '=':
        {
            return GetTextureCoordinats(33);
            break;
        }
    }
    return new float__;
}
Scene::~Scene()
{
    glDeleteTextures(92,Texture);
    delete[] Texture;
    for(int__ i=0;i<counttexturecoor;i++)
        delete[] texturecoordinats[i];
    delete[] texturecoordinats;
    for(int__ i=0;i<countvertex;i++)
        delete[] vertexcoordinats[i];
    delete[] vertexcoordinats;
    listv.clear();
    listt.clear();
    for(int__ k=0;k<21;k++)
    {
        for(int__ i=0;i<3;i++)
        {
            for(int__ j=0;j<6;j++)
                delete[] locatelinecoordinats[k][i][j];
            delete[] locatelinecoordinats[k][i];
        }
        delete[] locatelinecoordinats[k];
    }
    delete[] locatelinecoordinats;
    delete[] Data2;
    delete[] word;
    delete filereader;
    vecaa->clear();
    veca->clear();
    ves->clear();
}
