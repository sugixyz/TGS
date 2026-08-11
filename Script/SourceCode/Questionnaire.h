#pragma once
#include<string>

struct Questionnaire
{
	//質問文
	std::string text;
	//回答（5段階）
	int rating;
};