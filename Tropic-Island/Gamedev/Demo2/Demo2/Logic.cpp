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
	SetMinMax(0, 6);
	SetDrum();
	random = new int[5];
}

void Logic::SetMinMax(int min, int max)
{
	MIN = min;
	MAX = max;
}

void Logic::SetWin(int W1, int W2, int W3, int W4, int W5)
{
	WIN1 = W1;
	WIN2 = W2;
	WIN3 = W3;
	WIN4 = W4;
	WIN5 = W5;
}
void Logic::SetDrum(int line)
{
#if DBAPI_ == 1
	dbconn->Query();
#else
	int max_ = MAX, min_ = MIN;//6
	int num = -1;
	for (int i = line; i < 30; i+=6)
	{
		num = min_ + rand() % (max_ - min_ + 1);
		auto iter = vectordrum.cbegin();
		vectordrum.erase(iter + i);
		iter = vectordrum.cbegin();
		vectordrum.insert(iter + i, drum[num]);
	}
//	std::cout << vectordrum.size() << std::endl;
#endif
}
void Logic::SetDrum()
{
#if DBAPI_ == 1
	dbconn->Query();
#else
	vectordrum.clear();
	int max_ = MAX, min_ = MIN;//6
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
int* Logic::GetRandom()
{
	return random;
}
void Logic::SetRandom()
{
	int min = 3, max = 54;
	srand(time(0));
	for (int i = 0; i < 5; i++)
		random[i] = min + rand() % (max - min + 1);
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
	/*
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
	*/
	std::pair<std::vector<int>,bool> tmp;
	std::vector<int> tmptmp;
	for (int i = 0; i < 3; i++)
		for (int j = 6; j < 9; j++)
			for (int k = 12; k < 15; k++)
				for (int s = 18; s < 21; s++)
					for (int t = 24; t < 27; t++)
					{
						tmptmp.push_back(i);
						tmptmp.push_back(j);
						tmptmp.push_back(k);
						tmptmp.push_back(s);
						tmptmp.push_back(t);
						tmp.second = false;
						tmp.first=tmptmp;
						lines.push_back(tmp);
						tmptmp.clear();
					}
	
	for(int i=0;i<lines.size();i++)
		if (vectordrum[lines[i].first[0]] == vectordrum[lines[i].first[1]] && vectordrum[lines[i].first[1]] == vectordrum[lines[i].first[2]] &&
			vectordrum[lines[i].first[2]] == vectordrum[lines[i].first[3]] && vectordrum[lines[i].first[3]] == vectordrum[lines[i].first[4]])
		{
			lines[i].second = true;
			if (lines[i].second)
			{
				if (vectordrum[lines[i].first[0]] == "auto1")
					Win += WIN1;
				if (vectordrum[lines[i].first[0]] == "auto2")
					Win += WIN2;
				if (vectordrum[lines[i].first[0]] == "auto3")
					Win += WIN3;
				if (vectordrum[lines[i].first[0]] == "auto4")
					Win += WIN4;
				if (vectordrum[lines[i].first[0]] == "auto5")
					Win += WIN5;
				checkwin = true;
			}

		}
	lines.clear();
	if (checkwin)
	{
		return 1;
	}
	else
		return 0;

	/*
	if (firstline)
	{
		if (vectordrum[0] == "auto1")
			Win += WIN1;
		if (vectordrum[0] == "auto2")
			Win += WIN2;
		if (vectordrum[0] == "auto3")
			Win += WIN3;
		if (vectordrum[0] == "auto4")
			Win += WIN4;
		if (vectordrum[0] == "auto5")
			Win += WIN5;
	}
	if (secondline)
	{
		if (vectordrum[1] == "auto1")
			Win += WIN1;
		if (vectordrum[1] == "auto2")
			Win += WIN2;
		if (vectordrum[1] == "auto3")
			Win += WIN3;
		if (vectordrum[1] == "auto4")
			Win += WIN4;
		if (vectordrum[1] == "auto5")
			Win += WIN5;
	}
	if (thirdline)
	{
		if (vectordrum[2] == "auto1")
			Win += WIN1;
		if (vectordrum[2] == "auto2")
			Win += WIN2;
		if (vectordrum[2] == "auto3")
			Win += WIN3;
		if (vectordrum[2] == "auto4")
			Win += WIN4;
		if (vectordrum[2] == "auto5")
			Win += WIN5;
	}
	*/
#endif
	/*
	if(firstline || secondline || thirdline)
	{
		checkwin = true;
		return 1;
	}
	else
		return 0;
	*/
}
Logic::~Logic()
{
#if DBAPI_ == 1
	dbconn->Close();
	delete dbconn;
#else
	drum.clear();
#endif
	delete[] random;
}
