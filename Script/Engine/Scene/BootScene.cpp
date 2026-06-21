#include "BootScene.h"
#include"../Tool/DataHolder.h"

/// <summary>
/// 起動時のシーン
/// 共通で必要なGameObjectを生成して、
/// シーンを変更する
/// </summary>

BootScene::BootScene()
{
	new DataHolder();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene(SCENE_NAME::TITLE); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
