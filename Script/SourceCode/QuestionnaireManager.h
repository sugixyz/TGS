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
	void SaveQuestionnaire();
private:
	std::vector<Questionnaire> questions;
	int currentIndex;
	bool isFinished;
};