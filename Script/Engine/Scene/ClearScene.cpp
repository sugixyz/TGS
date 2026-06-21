#include "ClearScene.h"
namespace {
	//画面遷移までの時間
	const float CLEAR_TIME = 60 * 5.0f;
}
/// <summary>
/// クリア画面
/// </summary>
ClearScene::ClearScene()
{
	timer = 0;
}

ClearScene::~ClearScene()
{}

void ClearScene::Update()
{
	timer++;
	if (timer > CLEAR_TIME || Input::IsKeyDown(INPUT_KEYBOARD))
	{
		timer = 0;
		SceneManager::ChangeScene(SCENE_NAME::RESULT);
	}
}

void ClearScene::Draw()
{
	int size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Clear", GetColor(255, 255, 255));
	SetFontSize(size);
}
