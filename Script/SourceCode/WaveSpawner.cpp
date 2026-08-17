#include "WaveSpawner.h"
#include"Enemy.h"
#include"../Engine/Object/ObjectManager.h"

WaveSpawner::WaveSpawner()
	:GameObject(Tag::SYSTEM)
{
	state = State::EndWave;
	waveTimer.Reset();
	spawnTimer.Reset();
}

WaveSpawner::~WaveSpawner()
{}

void WaveSpawner::Update()
{}

void WaveSpawner::StartWave(const WaveParameters & parameters)
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
	else if(size == 1)
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
