#include "QuestionnaireSave.h"
#include<fstream>
#include<iostream>
#include<string>
#include<assert.h>

QuestionnaireSave::QuestionnaireSave()
{}

QuestionnaireSave::~QuestionnaireSave()
{}

void QuestionnaireSave::SaveData(const std::vector<Questionnaire>&questions)
{
	std::string path = "Assets/QuestionnaireData.csv";
	std::ofstream ofs(path, std::ios::app);

	//開けなかったら止める
	assert(ofs.is_open() == true);

	for (int i = 0; i < questions.size(); i++)
	{
		//評価の値を出力
		ofs << questions[i].rating;
		//最後の要素以外に,をつける
		if (i < questions.size() - 1)ofs << ",";
	}

	ofs << "\n";
	ofs.close();
}
