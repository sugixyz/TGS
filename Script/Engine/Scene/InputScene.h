#pragma once
#include "SceneBase.h"
/// <summary>
/// リザルト画面
/// </summary>
class InputScene :
	public SceneBase
{
public:
	InputScene();
	~InputScene();
	void Update() override;
	void Draw() override;
private:
	//時間管理変数
	int timer;
};
