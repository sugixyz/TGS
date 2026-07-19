#pragma once
#include"../Engine/Object/GameObject.h"

class AiDirector : public GameObject
{
public:
	AiDirector();
	~AiDirector();
	static void LoadParam();
private:
	float waveTime;
	float waveEnemyCount;
private:
	//ステージオブジェクトを作成
	void CreateStageObject();
	//拠点の当たり判定の生成
	void CreateBase();
private:
	int BASE_BLOCK;
	int BASE_OFFSET_Y;
};