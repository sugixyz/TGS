#pragma once
#include "SceneBase.h"

/// <summary>
/// プレイ画面
/// </summary>

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	void ChangeMode();
};