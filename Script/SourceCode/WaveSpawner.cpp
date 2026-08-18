#include "WaveSpawner.h"
#include"Normal.h"
#include"Archer.h"
#include"Titan.h"
#include"TestEnemy.h"
#include"../Engine/Object/ObjectManager.h"
#include"../Engine/Tool/Event.h"

WaveSpawner::WaveSpawner()
	:GameObject(Tag::SYSTEM)
{
	waveState = WaveState::END_WAVE;
	waveTimer.Reset();
	intervalTimer.Reset();
}

WaveSpawner::~WaveSpawner()
{}

void WaveSpawner::Update()
{
	switch (waveState)
	{
	case WaveState::INTERVAL:
		IntervalUpdate();
		break;
	case WaveState::IN_WAVE:
		InWaveUpdate();
		break;
	case WaveState::END_WAVE:
		EndWaveUpdate();
		break;
	}
}

void WaveSpawner::StartWave(const WaveParameters & parameters)
{
	waveParameters = parameters;
	waveTimer.Reset();
	intervalTimer.Reset();
	waveState = WaveState::INTERVAL;
}

void WaveSpawner::IntervalUpdate()
{
	intervalTimer.Update();
	//インターバルの時間が一定時間経過したら
	if (intervalTimer.isOverTime(waveParameters.nextWaveInterval))
	{
		waveState = WaveState::IN_WAVE;
		Event::Instance().Get(Id::START_WAVE).Invoke();
	}
}

void WaveSpawner::InWaveUpdate()
{
	waveTimer.Update();
	//ウェーブの処理
	WaveProcess();
}

void WaveSpawner::EndWaveUpdate()
{}

void WaveSpawner::WaveProcess()
{
	auto enemies = FindTagObjects(Tag::ENEMY);
	int enemiesCount = enemies.size();

	//一体ずつ生成する処理
	if (waveTimer.IsEvery(waveParameters.spawnInterval))
	{
		//まだ敵をスポーンさせられるか
		bool canSpawn = (waveParameters.totalSpawnCount > 0);
		//敵の数が上限より下か
		bool underLimit = (enemiesCount < waveParameters.maxConcurrentEnemies);

		if (canSpawn && underLimit)
		{
			//敵を生成
			SpawnEnemy();
			waveParameters.totalSpawnCount--;
		}
	}

	//ウェーブの終了判定
	//制限時間が切れているかどうか
	bool isTimeOut = waveTimer.isOverTime(waveParameters.waveTimeLimit);
	//敵が湧きつくしたかどうか
	bool isAllEnemyCleared = (waveParameters.totalSpawnCount <= 0 &&
		enemiesCount <= 0);
	if (isTimeOut || isAllEnemyCleared)
	{
		waveState = WaveState::END_WAVE;
		Event::Instance().Get(Id::END_WAVE).Invoke();
	}
}

void WaveSpawner::SpawnEnemy()
{
	new Normal(Vector2(0,0));
	//new TestEnemy(Vector2(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f));
}

void WaveSpawner::SpawnArmy()
{}

Vector2 WaveSpawner::CalculateSpawnPoint()
{
	auto players = FindTagObjects(Tag::PLAYER);
	int size = players.size();
	if (size == 0)return Vector2();
	Vector2 playerCenter;
	if (size == 2)
	{
		Vector2 playerSub = players[1]->GetPos() - players[0]->GetPos();
		playerCenter = players[0]->GetPos() + (playerSub * 0.5f);
	}
	else if (size == 1)
	{
		playerCenter = players[0]->GetPos();
	}
	playerCenter.x = (playerCenter.x - (WIN_WIDTH / 2.0f)) * -1.0f + (WIN_WIDTH / 2.0f);
	Vector2 vec = playerCenter - Enemy::DESTINATION;
	vec = Math2D::Normalize(vec);
	Vector2 pos = Enemy::DESTINATION + vec * 2500;
	int randVal = GetRand(50) - 25;
	pos.x += randVal;
	pos.y += randVal;
	return pos;
}

