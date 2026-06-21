#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
};