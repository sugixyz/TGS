#include "ResultScene.h"
namespace {
	//画面遷移までの時間
	const float RESULT_TIME = 60 * 5.0f;
}
/// <summary>
/// リザルト画面
/// </summary>
ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{}

void ResultScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::QUESTIONNAIRE);
	}
	if (Input::IsKeyDown(KEY_INPUT_M))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY);
	}
}

void ResultScene::Draw()
{
	DrawString(100, 100, "ResultScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Questionnaire", 0xffffff);
	DrawString(100, 200, "Push [M]Key To Play", 0xffffff);
}
