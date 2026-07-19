#pragma once
#include"../Engine/Object/GameObject.h"
#include"../Engine/Tool/Time.h"

class AiDirector : public GameObject
{
public:
	AiDirector();
	~AiDirector();
	void Update() override;
private:
	Timer waveTime;
	float waveEnemyCount;
private:
	//ステージオブジェクトを作成
	void CreateStageObject();
	//拠点の当たり判定の生成
	void CreateBase();
	//ウェーブの処理
	void WaveProcess();
	//敵軍隊の生成
	void CreateArmy();
private:
	int BASE_BLOCK;
	int BASE_OFFSET_Y;
};