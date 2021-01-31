#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <DataBaseConnection.h>
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
	DataBaseConnection * dbconn;
	bool firstline, secondline, thirdline;
	bool checkwin;
};
#endif
