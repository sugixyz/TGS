#pragma once
#include "SceneBase.h"
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
};
