#include "PlayScene.h"
#include"../../SourceCode/Ui.h"
#include"../../SourceCode/AiDirector.h"
#include"../../SourceCode/Camera.h"
#include"../../SourceCode/DirectionalLight.h"
#include"../../SourceCode/PointLight.h"
/// <summary>
/// プレイ中の画面の遷移をする
/// </summary>

PlayScene::PlayScene()
{
	gGameTimer.timer = 0.0f;

	new Ui("タイマー", &gGameTimer.timer);
	new AiDirector();
	new Camera();
	new DirectionalLight();
	new PointLight(VGet(0, 0, 0), 5);
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

	if (Input::IsKeyDown(KEY_INPUT_F1))
	{
		ChangeMode();
	}
}

void PlayScene::Draw()
{
	DrawString(100, 0, "PlayScene", 0xffffff);
	DrawString(100, 20, "Push [N]Key To Title", 0xffffff);
}

void PlayScene::ChangeMode()
{
	if (mode == DEBUG)mode = NORMAL;
	else if (mode == NORMAL)mode = DOUBLE_MODE;
	else if (mode == DOUBLE_MODE)mode = DEBUG;
}