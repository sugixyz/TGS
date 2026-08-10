#pragma once
#include"../Object/GameObject.h"
#include"../../SourceCode/RankingManager.h"

/// <summary>
/// 画面遷移後も変数の値を保持する
/// </summary>

class DataHolder : public GameObject
{
public:
	DataHolder();
	~DataHolder();

	//ここに保持しときたい変数を宣言
	//全体のランキング管理
	RankingManager ranking;
	//登録用のランキング変数
	RankData rankData;
};