#pragma once
#include"../Engine/Object/GameObject.h"
#include"../Engine/Tool/Time.h"

struct Probability
{
	int normal = 80;
	int archer = 18;
	int titan = 2;
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
	//ウェーブを管理するタイマー
	Timer waveTimer;
	//次のウェーブの開始時間
	float nextWaveTime;

	//現在何ウェーブ目か
	int currentWave;
	//あと何体出すか
	int remainingSpawnCount;
	//スポーン間隔を管理するタイマー
	Timer spawnTimer;
	//ウェーブの経過時間（殲滅までの時間）
	float waveElapsedTime;

	//敵それぞれの出現確立を管理する
	Probability probability;
private:
	//ステージオブジェクトを作成
	void CreateStageObject();
	//拠点の当たり判定の生成
	void CreateBase();
	//ウェーブの処理
	void WaveProcess();
	//スポーンのロジック関数
	void SpawnLogic();
	//敵の生成
	void CreateEnemy();
	//スポーンポイントを計算する関数
	Vector2 CalculateSpawnPoint();
private:
	int BASE_BLOCK;
	int BASE_OFFSET_Y;

	float WAVE_INTERVAL = 15.0f;
	int WAVE_ENEMY_COUNT = 30;
	int ENEMY_INCREASE_RATE = 5;
	float SPAWN_INTERVAL = 0.5f;
	int MAX_ACTIVE_ENEMIES = 50;
};