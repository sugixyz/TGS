#pragma once
#include "SceneBase.h"
/// <summary>
/// リザルト画面
/// </summary>
class QuestionnaireScene :
	public SceneBase
{
public:
	QuestionnaireScene();
	~QuestionnaireScene();
	void Update() override;
	void Draw() override;
};
