#pragma once
#include"RankData.h"
#include<vector>

class RankingManager
{
public:
	RankingManager();
	~RankingManager();
	/// <summary>
	/// ランキングに追加する関数
	/// </summary>
	/// <param name="rankData">追加したいランキングデータ</param>
	void AddRankData(const RankData& rankData);
	/// <summary>
	/// ランクデータから順位を取得する関数
	/// </summary>
	/// <param name="data">検索したい名前とスコア</param>
	/// <returns>順位</returns>
	int GetRankToData(const RankData& data);
	/// <summary>
	/// 順位からランクデータを取得する関数
	/// </summary>
	/// <param name="rank">検索したい順位</param>
	/// <returns>名前とスコア</returns>
	RankData GetDataToRank(const int& rank);
private:
	std::vector<RankData> rankList;
};