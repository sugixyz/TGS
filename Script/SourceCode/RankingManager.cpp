#include "RankingManager.h"
#include<algorithm>

RankingManager::RankingManager()
{
    rankList.clear();
}

RankingManager::~RankingManager()
{}

void RankingManager::AddRankData(const RankData& rankData)
{
    //リストにデータを追加
    rankList.push_back(rankData);
    //ソート
    std::sort(rankList.begin(), rankList.end(),
        [](auto& a, auto& b) {return a.score > b.score;});
}

int RankingManager::GetRankToData(const RankData & data)
{
    //リストを全探索
    for (int rank = 0; rank < rankList.size(); rank++)
    {
        //その順位のランクデータを取得
        RankData rankData = rankList[rank];
        //名前が違うなら次のループへ
        if (rankData.name != data.name)continue;
        //スコアが違うなら次のループへ
        if (rankData.score != data.score)continue;

        //どちらもあっているならその順位を返す
        return rank + 1;
    }

    //見つからなかったら-1を返す
    return -1;
}

RankData RankingManager::GetDataToRank(const int& rank)
{
    //もし検索したい順位が0以下なら空データを返す
    if (rank <= 0)return { "-",0 };
    //もし検索したい順位よりデータ量が少なかったら空データを返す
    if (rank > rankList.size())return { "-",0 };

    //そうでなければその順位のデータを返す
    return rankList[rank - 1];
}
