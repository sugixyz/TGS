#include "QuestionnaireScene.h"
namespace {
	//画面遷移までの時間
	const float RESULT_TIME = 60 * 5.0f;
}
/// <summary>
/// リザルト画面
/// </summary>
QuestionnaireScene::QuestionnaireScene()
{
	timer = 0;
}

QuestionnaireScene::~QuestionnaireScene()
{}

void QuestionnaireScene::Update()
{
	timer++;
	if (timer > RESULT_TIME || Input::IsKeyDown(INPUT_KEYBOARD))
	{
		timer = 0;
		SceneManager::ChangeScene(SCENE_NAME::TITLE);
	}
}

void QuestionnaireScene::Draw()
{
	int size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Questionnaire", GetColor(255, 255, 255));
	SetFontSize(size);
}
