#ifndef SCENE_H
#define SCENE_H
#include <string.h>
#include "Vector3.h"
#include "FileReader.h"
#include "Coor.h"
#include <time.h>
struct int_
{
    int__ a;
    int__ b;
};
class Scene
{
public:
    Scene();
    void__  LoadData();
    void__ SetData();
    void__ EnableTexture(float__*texcoor,float__* vercoor);
    uint__ GetTexture(int__ num);
    uint__ GetNumTexture(int__ num,int__ color);
    float__*GetTextureCoordinats(int__ i);
    float__*GetVertexCoordinats(int__ i);
    float__*GetTextureNumCoordinats(int__ num);
    void__ SetVerteces();
    void__ EnableTexture(int__ n,int__ m);
    void__ EnableTexture(float__*texcoor,float__*vercoor,float__ third,int__ voshod);
    void__ ShowLine(int__ bet,bool__*lines,int__**ms);
    float__*GetTextureLineCoordinats();
    float__*GetLocateLineCoordinats(int__ a,int__ b,int__ c);
    uint__ GetLineTexture(int__ n);
    void__ ShowReservedWords(int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet);
    void__ ShowBoth();
    void__ Show(int__ countdrums,float__*rotate_,int__ counttextureondrums,int__**drum,int__ credits,int__ win,int__ totalbet,const char__*line,int__ bet,bool__*lines,int__**ms,bool__*buttons);
    void__ EnableTextureNum(float__*texcoor,int__ position,Coor*coor_,bool__ vert);
    uint__ GetSymbolTexture(char__ str,int__ black);
    uint__ GetAlphabetTexture(int__ i,int__ color);
    float__*GetTextureWordCoordinats(char__ str);
    void__ LoadData2();
    void__ ShowButtons(bool__*buttons);
    void__ SetButtons(int__ state,int__ n);
    int__ GetButtons(int__ n);
    uint__ GetButtonTexture(int__ numbutton,int__ button);
    void__ DrawWord(int__ word_,Coor*coor_,int__ color,bool__ vert);
    void__ DrawWord(const char__*word_,Coor*coor_,int__ color,bool__ vert);
	void__ Show2(int__ credits,int__ win,int__ totalbet,bool__*buttons);
	void__ ShowReservedWords2(int__ credits,int__ win,int__ totalbet);
	void__ ShowBackGround();
    virtual ~Scene();
protected:
    uchar__*Data2;
    uint__*Texture,counttexture;
    float__**texturecoordinats;
    int__ counttexturecoor;
    float__**vertexcoordinats;
    int__ countvertex,oldbet;
    float__****locatelinecoordinats;
    std::vector<Vector3>listv;
    std::vector<Vector3>listt;
    std::vector<int_>*veca,*vecaa;
    std::vector<int__>*ves;
    FileReader*filereader;
    char__*word;
	clock_t time_visible;
    uchar__*NewData;
    uint__*NewTexture;
	float__*NewTextureCoordinats;
};
#endif
