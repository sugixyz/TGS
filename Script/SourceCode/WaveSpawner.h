#pragma once
#include"../Engine/Object/GameObject.h"
#include"AiData.h"
#include"../Engine/Tool/Time.h"

enum class State
{
	InWave,
	EndWave
};

class WaveSpawner : public GameObject
{
public:
	WaveSpawner();
	~WaveSpawner();
	void Update() override;
	void StartWave(const WaveParameters& parameters);
private:
	State state;
	WaveParameters waveParameters;
	Timer waveTimer;
	Timer spawnTimer;
private:
	//ウェーブ中の処理
	void WaveProcess();
private:
	//スポーンポイントを計算する関数
	Vector2 CalculateSpawnPoint();
};