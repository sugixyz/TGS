#pragma once
#include<vector>
#include"Questionnaire.h"

class QuestionnaireSave
{
public:
	QuestionnaireSave();
	~QuestionnaireSave();
	void SaveData(const std::vector<Questionnaire>& questions);
};