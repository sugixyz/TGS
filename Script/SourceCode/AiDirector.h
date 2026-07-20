#pragma once
#include"../Engine/Object/GameObject.h"
#include"../Engine/Tool/Time.h"

struct Probability
{
	int normal;
	int archer;
	int titan;
	int Rate(int target)
	{
		int sum = normal + archer + titan;
		float result = (float)target / sum;
		return result;
	}
};

class AiDirector : public GameObject
{
public:
	AiDirector();
	~AiDirector();
	void Update() override;
private:
	Timer waveTime;
	float nextWave;
	int currentCount;
	int nextCount;
	Coroutine waveCoroutine;
	Coroutine armyCoroutine;
	Probability probability;
private:
	//ステージオブジェクトを作成
	void CreateStageObject();
	//拠点の当たり判定の生成
	void CreateBase();
	//ウェーブの処理
	void WaveProcess();
	//一定時間ごとに軍隊を生成する関数
	void IEWave(int enemyCount);
	void IEArmy();
	//敵の生成
	void CreateEnemy();
	//スポーンポイントを計算する関数
	Vector2 CalculateSpawnPoint();
private:
	int BASE_BLOCK;
	int BASE_OFFSET_Y;
	float WAVE_INTERVAL = 10.0f;
	int WAVE_ENEMY_COUNT = 5;
	float ARMY_INTERVAL = 1.5f;
	int ARMY_COUNT = 3;
};