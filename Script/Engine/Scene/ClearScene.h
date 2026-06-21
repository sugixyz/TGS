#pragma once
#include "SceneBase.h"

/// <summary>
/// クリア画面
/// </summary>
class ClearScene :
    public SceneBase
{
public:
	ClearScene();
	~ClearScene();
	void Update() override;
	void Draw() override;
private:
	//時間管理変数
	int timer;
};

