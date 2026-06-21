#include "PlayScene.h"
#include"../../SourceCode/Ui.h"
#include"../../SourceCode/AiDirector.h"
/// <summary>
/// プレイ中の画面の遷移をする
/// </summary>

PlayScene::PlayScene()
{
	gGameTimer.timer = 0.0f;

	new Ui("タイマー", &gGameTimer.timer);
	new AiDirector();
}

PlayScene::~PlayScene()
{}

void PlayScene::Update()
{
	gGameTimer.Update();

	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::TITLE);
	}
	if (Input::IsKeyDown(KEY_INPUT_RETURN))
	{
		gGameTimer.Switch();
	}
}

void PlayScene::Draw()
{
	DrawString(100, 0, "PlayScene", 0xffffff);
	DrawString(100, 20, "Push [N]Key To Title", 0xffffff);
}

