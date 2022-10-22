#include "Logic.h"
Logic::Logic()
{
	CountPosition = 30;
#if DBAPI_ == 1
	dbconn = new DataBaseConnection();
#endif
	thirdline = secondline = firstline = false;
	checkwin = false;
	drum.push_back("auto1");
	drum.push_back("auto2");
	drum.push_back("auto3");
	drum.push_back("auto4");
	drum.push_back("auto5");
	drum.push_back("bonus");
	drum.push_back("wild");
	SetDrum();
}
void Logic::SetDrum()
{
#if DBAPI_ == 1
	dbconn->Query();
#else
	vectordrum.clear();
	int max_ = 6, min_ = 0;
	srand(time(NULL));
	int num = -1;
	for (int i = 0; i < 30; i++)
	{
		num = min_ + rand() % (max_ - min_ + 1);
		vectordrum.push_back(drum[num]);
		//std::cout<<num<<" ";
	}
	//std::cout<<std::endl;
#endif
}
std::vector<std::string> Logic::GetDrum()
{
#if DBAPI_ == 1
	return dbconn->vectordrum;
#else
	return vectordrum;//new
#endif
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
void Logic::SetCredits()
{
#if DBAPI_ == 1
	Credits = dbconn->GetCredits();
#endif
}
void Logic::SetCredits(float credits,bool online)
{
	Credits = credits;
#if DBAPI_ == 1
	if(online)
		dbconn->SetCredits(credits);
#endif
}
void Logic::SetWin(float win)
{
	Win = win;
}
void Logic::SetTotalBet(float totalbet)
{
	TotalBet = totalbet;
}
bool Logic::CheckWin()
{
	if (checkwin)
		return 0;

#if DBAPI_ == 1
	if (dbconn->vectordrum[0] == dbconn->vectordrum[6] &&
		dbconn->vectordrum[6] == dbconn->vectordrum[12] &&
		dbconn->vectordrum[12] == dbconn->vectordrum[18] &&
		dbconn->vectordrum[18] == dbconn->vectordrum[24]
		)
		firstline = true;
	if (dbconn->vectordrum[1] == dbconn->vectordrum[7] &&
		dbconn->vectordrum[7] == dbconn->vectordrum[13] &&
		dbconn->vectordrum[13] == dbconn->vectordrum[19] &&
		dbconn->vectordrum[19] == dbconn->vectordrum[25]
		)
		secondline = true;

	if (dbconn->vectordrum[2] == dbconn->vectordrum[8] &&
		dbconn->vectordrum[8] == dbconn->vectordrum[14] &&
		dbconn->vectordrum[14] == dbconn->vectordrum[20] &&
		dbconn->vectordrum[20] == dbconn->vectordrum[26]
		)
		thirdline = true;
	if (firstline)
	{
		if (dbconn->vectordrum[0] == "auto1")
			Win += 5;
		if (dbconn->vectordrum[0] == "auto2")
			Win += 10;
		if (dbconn->vectordrum[0] == "auto3")
			Win += 15;
		if (dbconn->vectordrum[0] == "auto4")
			Win += 20;
		if (dbconn->vectordrum[0] == "auto5")
			Win += 25;
	}
	if (secondline)
	{
		if (dbconn->vectordrum[1] == "auto1")
			Win += 5;
		if (dbconn->vectordrum[1] == "auto2")
			Win += 10;
		if (dbconn->vectordrum[1] == "auto3")
			Win += 15;
		if (dbconn->vectordrum[1] == "auto4")
			Win += 20;
		if (dbconn->vectordrum[1] == "auto5")
			Win += 25;
	}
	if (thirdline)
	{
		if (dbconn->vectordrum[2] == "auto1")
			Win += 5;
		if (dbconn->vectordrum[2] == "auto2")
			Win += 10;
		if (dbconn->vectordrum[2] == "auto3")
			Win += 15;
		if (dbconn->vectordrum[2] == "auto4")
			Win += 20;
		if (dbconn->vectordrum[2] == "auto5")
			Win += 25;
	}
#else
	if (vectordrum[0] == vectordrum[6] &&
		vectordrum[6] == vectordrum[12] &&
		vectordrum[12] == vectordrum[18] &&
		vectordrum[18] == vectordrum[24]
		)
		firstline = true;
	if (vectordrum[1] == vectordrum[7] &&
		vectordrum[7] == vectordrum[13] &&
		vectordrum[13] == vectordrum[19] &&
		vectordrum[19] == vectordrum[25]
		)
		secondline = true;

	if (vectordrum[2] == vectordrum[8] &&
		vectordrum[8] == vectordrum[14] &&
		vectordrum[14] == vectordrum[20] &&
		vectordrum[20] == vectordrum[26]
		)
		thirdline = true;
	if (firstline)
	{
		if (vectordrum[0] == "auto1")
			Win += 5;
		if (vectordrum[0] == "auto2")
			Win += 10;
		if (vectordrum[0] == "auto3")
			Win += 15;
		if (vectordrum[0] == "auto4")
			Win += 20;
		if (vectordrum[0] == "auto5")
			Win += 25;
	}
	if (secondline)
	{
		if (vectordrum[1] == "auto1")
			Win += 5;
		if (vectordrum[1] == "auto2")
			Win += 10;
		if (vectordrum[1] == "auto3")
			Win += 15;
		if (vectordrum[1] == "auto4")
			Win += 20;
		if (vectordrum[1] == "auto5")
			Win += 25;
	}
	if (thirdline)
	{
		if (vectordrum[2] == "auto1")
			Win += 5;
		if (vectordrum[2] == "auto2")
			Win += 10;
		if (vectordrum[2] == "auto3")
			Win += 15;
		if (vectordrum[2] == "auto4")
			Win += 20;
		if (vectordrum[2] == "auto5")
			Win += 25;
	}
#endif
	if(firstline || secondline || thirdline)
	{
		checkwin = true;
		return 1;
	}
	else
		return 0;
}
Logic::~Logic()
{
#if DBAPI_ == 1
	dbconn->Close();
	delete dbconn;
#else
	drum.clear();
#endif
}
