#include "Logic.h"
Logic::Logic()
{
	CountPosition = 30;
	random = new int[CountPosition];
	dbconn = new DataBaseConnection();
	//dbconn->Connect();
	//dbconn->Query();
}
int *Logic::GetRandom()
{
	return random;
};
void Logic::SetRandom()
{
	int min = 0, max = 16;
	srand(time(0));
	for (int i = 0; i<CountPosition; i++)
		random[i] = min + rand() % (max - min + 1);
};
void Logic::SetDrum()
{
	dbconn->Query();
}
std::vector<std::string> Logic::GetDrum()
{
	//for (int i = 0; i < dbconn->vectordrum.size(); i++)
//		printf("%s ",dbconn->vectordrum[i]);
	//printf("\n");
	return dbconn->vectordrum;
}
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
	dbconn->Close();
	delete[] random;
	delete dbconn;
}
