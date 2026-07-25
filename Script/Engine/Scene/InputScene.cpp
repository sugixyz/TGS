#include "InputScene.h"
namespace {
	//画面遷移までの時間
	const float RESULT_TIME = 60 * 5.0f;
}
/// <summary>
/// リザルト画面
/// </summary>
InputScene::InputScene()
{
}

InputScene::~InputScene()
{}

void InputScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY);
	}
}

void InputScene::Draw()
{
	DrawString(100, 100, "InputScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Play", 0xffffff);
}
