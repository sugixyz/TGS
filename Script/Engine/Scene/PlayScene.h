#pragma once
#include "SceneBase.h"

/// <summary>
/// プレイ画面
/// </summary>

class WaveSpawner;
class AiDirector;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	void ChangeMode();
	int playScore;
	WaveSpawner* waveSpawner;
	AiDirector* aiDirector;
};