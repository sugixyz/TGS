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
}

QuestionnaireScene::~QuestionnaireScene()
{}

void QuestionnaireScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::TITLE);
	}
}

void QuestionnaireScene::Draw()
{
	DrawString(100, 100, "QuestionnaireScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Title", 0xffffff);
}
