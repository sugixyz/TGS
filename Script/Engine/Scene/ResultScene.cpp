#include "ResultScene.h"
#include"../Tool/DataHolder.h"
#include<string>

namespace {
	//画面遷移までの時間
	const float RESULT_TIME = 60 * 5.0f;
}
/// <summary>
/// リザルト画面
/// </summary>
ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{}

void ResultScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::QUESTIONNAIRE);
	}
	if (Input::IsKeyDown(KEY_INPUT_M))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY);
	}
}

void ResultScene::Draw()
{
	DrawString(100, 100, "ResultScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Questionnaire", 0xffffff);
	DrawString(100, 200, "Push [M]Key To Play", 0xffffff);
	
	DrawRanking();
}

void ResultScene::DrawRanking()
{
	int x, y;
	x = 400;
	y = 250;
	DrawString(x, y, "|_____RANK__|_____NAME__|____SCORE__|", 0xffffff);
	y += 50;

	DataHolder* data = FindGameObject<DataHolder>(Tag::SYSTEM);
	RankingManager ranking = data->ranking;

	for (int i = 1; i < 5 + 1; i++)
	{
		RankData rankData = ranking.GetDataToRank(i);
		std::string name = rankData.name;
		std::string displayName = PadLeftWithUnderscore(name, 9);

		DrawFormatString(x, y, 0xffff00, "|_______%02d__|%s__|____%05d__|",i, displayName.c_str(), rankData.score);
		y += 50;
	}

	RankData myRankData = data->rankData;
	std::string name = myRankData.name;
	std::string displayName = PadLeftWithUnderscore(name, 9);
	int rank = ranking.GetRankToData(myRankData);

	DrawFormatString(x, y, 0xffffff, "|_______%02d__|%s__|____%05d__|", rank, displayName.c_str(), myRankData.score);
}

std::string ResultScene::PadLeftWithUnderscore(std::string str, size_t lenght)
{
	if (str.length(), lenght)
	{
		//先頭から_を挿入
		str.insert(0, lenght - str.length(), '_');
	}

	return str;
}
