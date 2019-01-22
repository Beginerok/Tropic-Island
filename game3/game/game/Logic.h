#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <cmath>
#ifdef _POSIX_SOURCE
    #include <stdlib.h>
#endif // _UNIX_
class Logic
{
public:
	Logic();
	int *GetRandom();
	void SetRandom();
	float GetCredits();
	float GetWin();
	float GetTotalBet();
	void SetCredits(float credits);
	void SetWin(float win);
	void SetTotalBet(float totalbet);
	~Logic();
	int *random;
	int countF;
	float Credits, Win, TotalBet;
};
#endif
