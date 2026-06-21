#pragma once
#include "SceneBase.h"
/// <summary>
/// ゲームオーバー画面
/// </summary>
class GameOver :
    public SceneBase
{
public:
	GameOver();
	~GameOver();
	void Update() override;
	void Draw() override;
private:
	//時間管理変数
	int timer;
};

