#include "GameOver.h"
namespace {
	//画面遷移までの時間
	const float GAMEOVER_TIME = 60 * 5.0f;
}
/// <summary>
/// ゲームオーバー画面
/// </summary>
GameOver::GameOver()
{
	timer = 0;
}

GameOver::~GameOver()
{}

void GameOver::Update()
{
		timer++;
		if (timer > GAMEOVER_TIME||Input::IsKeepKeyDown(INPUT_KEYBOARD))
		{
			timer = 0;
			SceneManager::ChangeScene(SCENE_NAME::RESULT);
		}
}

void GameOver::Draw()
{
	int size = GetFontSize();
	SetFontSize(80);
	DrawString(100, 100, "Game Over",GetColor(255,0,0));
	SetFontSize(size);
}
