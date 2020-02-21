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
	int *GetRandom();
	void SetRandom();
	void SetDrum();
	std::vector<std::string> GetDrum();
	float GetCredits();
	float GetWin();
	float GetTotalBet();
	void SetCredits();
	void SetWin(float win);
	void SetTotalBet(float totalbet);
	~Logic();
	int *random;
	int CountPosition;
	float Credits, Win, TotalBet;
	DataBaseConnection * dbconn;
};
#endif
