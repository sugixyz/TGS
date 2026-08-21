#pragma once
#include"../Engine/Object/GameObject.h"
#include"AiData.h"
#include"../Engine/Tool/Time.h"

enum class EnemyType;

enum class WaveState
{
	//ウェーブ開始前のインターバル
	INTERVAL	,
	//ウェーブ進行中
	IN_WAVE,
	//ウェーブ終了
	END_WAVE
};

class WaveSpawner : public GameObject
{
public:
	WaveSpawner();
	~WaveSpawner();
	void Update() override;
	/// <summary>
	/// パラメータを受け取ってウェーブを開始する関数
	/// </summary>
	/// <param name="parameters">今回のウェーブのパラメータ</param>
	void StartWave(const WaveParameters& parameters);
	/// <summary>
	/// ウェーブの状態を取得する
	/// </summary>
	/// <returns>ウェーブの状態</returns>
	WaveState GetWaveState() { return waveState; }
private:
	//現在のウェーブの状態
	WaveState waveState;
	//ウェーブに用いるパラメータ
	WaveParameters waveParameters;
	//ウェーブ中のタイマー
	Timer waveTimer;
	//インターバル中のタイマー
	Timer intervalTimer;
private:
	//各状態毎のアップデート
	void IntervalUpdate();
	void InWaveUpdate();
	void EndWaveUpdate();
	//ウェーブ中の処理
	void WaveProcess();
	//敵をスポーンさせる（1体）
	void SpawnEnemy(Vector2 pos);
	//敵の集団をスポーンさせる
	void SpawnArmy();
	//プレイヤーの位置からスポーンポイントを計算する関数
	Vector2 CalculateSpawnPointToPlayer();
	//ランダムなスポーンポイントを計算する関数
	Vector2 CalculateSpawnPointToRandom();
	//出現確率をもとに敵を選出する関数
	EnemyType SelectEnemyTypeByRatio();
};