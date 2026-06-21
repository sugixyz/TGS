#pragma once
#include"../Engine/Object/GameObject.h"
#include<string>

class Ui : public GameObject
{
public:
	//int用コンストラクタ
	Ui(const std::string& str,const int* val,unsigned int col = COL_WHITE);
	//float用コンストラクタ
	Ui(const std::string& str,const float* val,unsigned int col = COL_WHITE);
	//文字だけ用のコンストラクタ
	Ui(const std::string& str, unsigned int col = COL_WHITE);
	~Ui();
	void Draw() override;
private:
	//表示する文字
	std::string title;
	//int用のポインタ
	const int* intVal = nullptr;
	//float用のポインタ
	const float* floatVal = nullptr;
	//表示する色
	unsigned int color;
	//場所を指定するためのID
	int id;
};