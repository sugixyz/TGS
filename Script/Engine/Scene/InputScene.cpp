#include "InputScene.h"
#include"../Tool/DataHolder.h"
#include<string>

namespace {
	//画面遷移までの時間
	const float RESULT_TIME = 60 * 5.0f;
	static int num = 0;
}
/// <summary>
/// リザルト画面
/// </summary>
InputScene::InputScene()
{
	num++;
}

InputScene::~InputScene()
{}

void InputScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::PLAY);
		DataHolder* data = FindGameObject<DataHolder>(Tag::SYSTEM);
		char str[20];
		sprintf_s(str, sizeof(str), "Test%02d", num);
		data->rankData.name = str;
	}
}

void InputScene::Draw()
{
	DrawString(100, 100, "InputScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Play", 0xffffff);
	DrawFormatString(100, 200, 0xffffff, "Test%02d", num);
}
