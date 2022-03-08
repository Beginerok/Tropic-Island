#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <cmath>
#include <cstdlib>
#include <time.h>
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
	~Logic();
	int CountPosition;
	float Credits, Win, TotalBet;
#if DBAPI_ == 1
	DataBaseConnection * dbconn; 
#else
	std::vector<std::string> vectordrum, drum;
#endif
	bool firstline, secondline, thirdline;
	bool checkwin;
};
#endif
