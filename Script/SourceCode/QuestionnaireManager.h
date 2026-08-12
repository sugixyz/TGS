#pragma once
#include"Questionnaire.h"
#include<vector>

class QuestionnaireManager
{
public:
	QuestionnaireManager();
	~QuestionnaireManager();
	void Update();
	void Draw();
	/// <summary>
	/// アンケート結果の保存
	/// </summary>
	void SaveQuestionnaire();
	/// <summary>
	/// アンケートが終了しているかどうか
	/// </summary>
	/// <returns>終了していればtrue</returns>
	bool IsFinished() { return isFinished; }
private:
	//質問のリスト
	std::vector<Questionnaire> questions;
	//現在回答中の質問のインデックス
	int currentIndex;
	//アンケートが終了しているか
	bool isFinished;
};