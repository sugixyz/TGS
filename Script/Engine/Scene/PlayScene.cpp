#include "PlayScene.h"
#include"../../SourceCode/Ui.h"
#include"../../SourceCode/AiDirector.h"
#include"../../SourceCode/Camera.h"
#include"../../SourceCode/DirectionalLight.h"
#include"../../SourceCode/PointLight.h"
#include"../Tool/Event.h"
#include"../Tool/DataHolder.h"
/// <summary>
/// プレイ中の画面の遷移をする
/// </summary>

PlayScene::PlayScene()
{
	gGameTimer.timer = 0.0f;
	playScore = 0;

	new Ui("タイマー", &gGameTimer.timer);
	new AiDirector();
	new Camera();
	new DirectionalLight();
	new PointLight(VGet(0, 0, 0), 5);

	Event::Instance().Get(Id::ADD_SCORE).Add([this] {AddScore(); });
}

PlayScene::~PlayScene()
{
	DataHolder* data = FindGameObject<DataHolder>(Tag::SYSTEM);
	data->rankData.score = playScore;
	data->ranking.AddRankData(data->rankData);

	Event::Instance().Get(Id::ADD_SCORE).Remove(static_cast<int>(Id::ADD_SCORE));
}

void PlayScene::Update()
{
	gGameTimer.Update();

	if (Input::IsKeyDown(KEY_INPUT_N))
	{
		SceneManager::ChangeScene(SCENE_NAME::RESULT);
	}
	if (Input::IsKeyDown(KEY_INPUT_RETURN))
	{
		gGameTimer.Switch();
	}

	if (Input::IsKeyDown(KEY_INPUT_F1))
	{
		ChangeMode();
	}
	if (Input::IsKeyDown(KEY_INPUT_F2))
	{
		AddScore();
	}
}

void PlayScene::Draw()
{
	DrawString(100, 100, "PlayScene", 0xffffff);
	DrawString(100, 150, "Push [N]Key To Result", 0xffffff);
}

void PlayScene::AddScore()
{
	playScore++;
}

void PlayScene::ChangeMode()
{
	if (mode == DEBUG)mode = NORMAL;
	else if (mode == NORMAL)mode = DOUBLE_MODE;
	else if (mode == DOUBLE_MODE)mode = DEBUG;
}