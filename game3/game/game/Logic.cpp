#include "Logic.h"



Logic::Logic()
{
	countF = 5;
	random = new int[countF];
}
int *Logic::GetRandom()
{
	return random;
};
void Logic::SetRandom()
{
	int min = 3, max = 54;
	for (int i = 0; i<countF; i++)
		random[i] = min + rand() % (max - min + 1);
};
float Logic::GetCredits()
{
	return Credits;
}
float Logic::GetWin()
{
	return Win;
}
float Logic::GetTotalBet()
{
	return TotalBet;
}
void Logic::SetCredits(float credits)
{
	Credits = credits;
}
void Logic::SetWin(float win)
{
	Win = win;
}
void Logic::SetTotalBet(float totalbet)
{
	TotalBet = totalbet;
}
Logic::~Logic()
{
	delete[] random;
}
