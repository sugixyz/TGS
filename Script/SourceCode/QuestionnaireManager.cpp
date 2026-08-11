#include "QuestionnaireManager.h"
#include"../Engine/Tool/Input.h"

namespace
{
	const int CENTER_Y = 400;
	const int LINE_SPACING = 100;
}

QuestionnaireManager::QuestionnaireManager()
{
	currentIndex = 0;
	isFinished = false;

	questions.clear();
	questions.push_back({ "1. ゲームの総合的な面白さ",3 });
	questions.push_back({ "2. 操作の分かりやすさ",3 });
	questions.push_back({ "3. グラフィック・エフェクト",3 });
	questions.push_back({ "4. 難易度のバランス",3 });
	questions.push_back({ "5. スクロール用テスト",3 });
	questions.push_back({ "6. スクロール用テスト",3 });
	questions.push_back({ "7. スクロール用テスト",3 });
	questions.push_back({ "8. スクロール用テスト",3 });
}

QuestionnaireManager::~QuestionnaireManager()
{}

void QuestionnaireManager::Update()
{
	//もしアンケートが終わってたらスルー
	if (isFinished)return;
	//もしアンケートが空だったらスルー
	if (questions.empty())return;

	//現在回答中のアンケート
	Questionnaire& question = questions[currentIndex];

	//左が入力されたら星を減らす
	if (Input::IsPadDown(Pad::LEFT, 0) || Input::IsPadDown(Pad::LEFT, 1))
	{
		question.rating--;
		if (question.rating < 1)question.rating = 1;
	}
	//右が入力されたら星を増やす
	if (Input::IsPadDown(Pad::RIGHT, 0) || Input::IsPadDown(Pad::RIGHT, 1))
	{
		question.rating++;
		if (question.rating > 5)question.rating = 5;
	}

	//Aボタンが入力されたら次の質問に
	if (Input::IsPadDown(Pad::A, 0) || Input::IsPadDown(Pad::A, 1))
	{
		currentIndex++;
		if (currentIndex >= questions.size())
		{
			isFinished = true;
			currentIndex = questions.size() - 1;
			SaveQuestionnaire();
		}
	}
}

void QuestionnaireManager::Draw()
{
	for (int i = 0; i < questions.size(); i++)
	{
		//現在の質問からどれくらい離れているか
		int relativeIndex = i - currentIndex;
		int y = CENTER_Y + (relativeIndex * LINE_SPACING);

		//アンケート
		Questionnaire question = questions[i];

		//現在回答中の質問かどうか
		bool isSelected = false;
		if (i == currentIndex)isSelected = true;

		unsigned int textColor = isSelected ? COL_YELLOW : COL_GRAY;
		std::string cursor = isSelected ? "≫" : "  ";

		//質問文
		DrawFormatString(180, y, textColor, "%s%s", cursor.c_str(), question.text.c_str());

		std::string star = "";
		for (int j = 1; j < 5 + 1; j++)
		{
			if (j <= question.rating)star += "★";
			else star += "☆";
		}
		//星
		DrawFormatString(180, y + 50, textColor, "%s", star.c_str());
	}

	DrawBox(0, 0, WIN_WIDTH, 160, COL_BLACK, TRUE);
	DrawString(350, 100, "【 試遊アンケート 】",COL_WHITE);

	DrawBox(0, WIN_HEIGHT - 160, WIN_WIDTH, WIN_HEIGHT, COL_BLACK, TRUE);
	DrawString(200, WIN_HEIGHT - 50, "≪≫：評価変更　　Aボタン：次の質問へ",COL_WHITE);
}

void QuestionnaireManager::SaveQuestionnaire()
{}
