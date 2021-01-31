#include "Logic.h"
Logic::Logic()
{
	CountPosition = 30;
	dbconn = new DataBaseConnection();
	thirdline = secondline = firstline = false;
	checkwin = false;
}
void Logic::SetDrum()
{
	dbconn->Query();
}
std::vector<std::string> Logic::GetDrum()
{	
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
void Logic::SetCredits()
{
	Credits = dbconn->GetCredits();
}
void Logic::SetCredits(float credits,bool online)
{
	Credits = credits;
	if(online)
		dbconn->SetCredits(credits);
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
	dbconn->Close();
	delete dbconn;
}
