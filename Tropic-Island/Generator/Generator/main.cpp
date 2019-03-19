#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <fstream>
int M = 0;//349;
int p = 0;//1003;
double U0 = 2;
const int N = 10000;
std::vector<int> min;
std::vector<std::pair<int, int>> minparam;
std::ofstream fout("result.txt");
std::ofstream foutR("resultR.txt");
std::vector<double> gen(double R0, int m, int p/*,std::ofstream fout*/)
{
	std::vector<double> R;
	std::vector<double> U;
	std::set<double> sR;
	std::pair<double,double> pair;
	std::vector<std::pair<double, double>> vectorpair;
	std::vector<int> vectorpairfind;
	U.push_back(R0);
	for (int i = 0; i < N; i++)
	{
		U.push_back(U.back() * M - p*int(U.back() * M / p));
		double r_ = U[i] / p;
		R.push_back(r_);
		foutR << r_<<'\n';
		sR.insert(r_);
		if (i == 0)
		{
			pair.first = r_;
		}
		else if (i == 1) 
		{
			pair.second = r_;
			vectorpair.push_back(pair);
			vectorpairfind.push_back(0);
			//std::cout << " " << vectorpair.back().first << " " << vectorpair.back().second << " ";
		}
		else
		{
			pair.first = pair.second;
			pair.second = r_;
			int counter = 0;
			for (int j = 0; j < vectorpair.size(); j++)
			{
				if (pair.first == vectorpair[j].first && pair.second == vectorpair[j].second)
				{
					counter++;
					break;
				}
			}
			if (counter == 0) 
			{
				vectorpair.push_back(pair);
				vectorpairfind.push_back(0);
			}
			//std::cout << " " << vectorpair.back().first << " " << vectorpair.back().second << " ";
		}
		//std::cout <<"R="<<R.back()<<" "<<std::endl;
	}
	if (sR.size() == R.size())
		std::cout << "lengths equal" << std::endl;
	//std::cout<<"R0="<<R0<<" sR="<<sR.size()<<" R="<<R.size()<<std::endl;
	//std::cout << "vectorpair.size() =" << vectorpair.size() << std::endl;
	//std::cout << "vectorpairfind.size() =" << vectorpairfind.size() << std::endl;
	fout<< "R0=" << R0 << " sR=" << sR.size() << " R=" << R.size() << std::endl;
	fout<< "vectorpair.size() =" << vectorpair.size() << std::endl;
	fout<< "vectorpairfind.size() =" << vectorpairfind.size() << std::endl;
	for (int i = 0; i < N-1; i++)
	{
		for(int j=0;j<vectorpair.size();j++)
		if (vectorpair[j].first == R[i] && vectorpair[j].second == R[i + 1])
			{
				vectorpairfind[j]++;
			}
	}
	int counter = 0;
	for (int j = 0; j<vectorpair.size(); j++)
		if (vectorpairfind[j] > 1)
		{
			counter++;
			//std::cout << "find" << vectorpair[j].first << " " << vectorpair[j].second << " count=" << vectorpairfind[j] << std::endl;
		}
	//std::cout << "Find " << counter << " matches" << std::endl; 
	fout<< "Find " << counter << " matches" << std::endl;
	if (counter == 0) 
	{
		std::cout << "M= " << M << " p=" << p << std::endl;
	}
	fout << "M= " << M << " p=" << p << std::endl;
	//if (vectorpair.size() == N - 1)
	//{
	min.push_back(vectorpair.size()/*counter*/);
	std::pair<int, int> pairmin;
	pairmin.first = m;
	pairmin.second = p;
	minparam.push_back(pairmin);
	//}
	return R;
}
int main()
{
	srand(time(0));
	double ii = 2;
	//for (int j = 1; j < 614657; j+=60000)
	{
		M =  2;
		U0 = ii;
		//for (int jj = 200; jj < 300; jj++)
		{
			p = 614657; //331777//160001;//655360001;
			gen(U0, M, p/*,fout*/);
		}
	}
	std::cout << "runtime = " << clock() / 1000.0 << std::endl;
	int max_ = 0;
	int ct = 0;
	for (int i = 0; i < min.size(); i++)
	{
		if (max_ < min[i]) 
		{
			max_ = min[i];
			ct = i;
		}
	}
	std::cout <<"ct="<<ct<<" max vector.size():" << min[ct] << " minparam: m=" << minparam[ct].first << " p=" << minparam[ct].second << std::endl;
	fout.close();
	foutR.close();
	std::cin.ignore();
	return 0;
}