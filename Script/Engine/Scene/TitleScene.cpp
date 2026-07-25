#include "TitleScene.h"

/// <summary>
/// タイトル画面
/// </summary>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::INPUT);
	}
}

void TitleScene::Draw()
{
	SetFontSize(40);
	DrawString(100,100,"TitleScene", 0xffffff );
	DrawString(100, 150, "Push [N]Key To Input", 0xffffff);
}
