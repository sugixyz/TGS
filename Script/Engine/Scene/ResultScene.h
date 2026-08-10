#pragma once
#include "SceneBase.h"
#include<string>
/// <summary>
/// リザルト画面
/// </summary>
class ResultScene :
	public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	void Update() override;
	void Draw() override;
private:
	//ランキングを表示
	void DrawRanking();
	//文字をアンダースコアで右寄せ
	std::string PadLeftWithUnderscore(std::string str, size_t lenght = 4);
};
