#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>
#if DBAPI_ == 1
	#include <DataBaseConnection.h>
#else
	#include <vector>
	#include <string>
#endif
#ifdef _POSIX_SOURCE
    #include <stdlib.h>
#endif // _UNIX_
class Logic
{
public:
	Logic();
	void SetDrum();
	std::vector<std::string> GetDrum();
	float GetCredits();
	float GetWin();
	float GetTotalBet();
	void SetCredits();
	void SetCredits(float credits,bool online);
	void SetWin(float win);
	void SetTotalBet(float totalbet);
	bool CheckWin();
	int* GetRandom();
	void SetRandom();
	void SetDrum(int line);
	~Logic();
	int CountPosition;
	float Credits, Win, TotalBet;
#if DBAPI_ == 1
	DataBaseConnection * dbconn;
#else
	std::vector<std::string> vectordrum, drum;
#endif
	//bool firstline, secondline, thirdline;
	bool checkwin;
	int* random;
	int MIN, MAX,WIN1,WIN2,WIN3,WIN4,WIN5,BONUS,WILD;
	void SetMinMax(int min, int max);
	void SetWin(int WIN1,int WIN2,int WIN3,int WIN4,int WIN5, int B, int W);
	std::vector<std::pair<std::vector<int>,bool>> lines;
	bool bonus;
	void SetDrum(std::vector<std::string> vecd);
};
#endif
