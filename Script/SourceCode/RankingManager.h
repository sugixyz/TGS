#pragma once
#include"RankData.h"
#include<vector>

class RankingManager
{
public:
	void AddRankData(const RankData& rank);
	int GetRank(const RankData& rank);
	std::vector<RankData> GetTop5();
private:
	std::vector<RankData> rankList;
};