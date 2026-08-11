#pragma once
#include "SceneBase.h"
#include"../../SourceCode/QuestionnaireManager.h"

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
private:
	QuestionnaireManager questions;
};
