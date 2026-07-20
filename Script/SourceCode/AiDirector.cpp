#include "AiDirector.h"
#include"Player.h"
#include"NormalZombie.h"
#include"BowZombie.h"
#include"TitanZombie.h"
#include"StageObject.h"
#include"Base.h"
#include"MaterialWarehouse.h"
#include"CraftTable.h"
#include"Table.h"
#include<sstream>
#include<fstream>
#include"../Engine/Tool/CsvReader.h"

AiDirector::AiDirector()
	:GameObject(Tag::SYSTEM)
{
	new Player(0);
	new Player(1);

	waveTime.Reset();
	nextWaveTime = WAVE_INTERVAL;

	CreateStageObject();
	CreateBase();
}

AiDirector::~AiDirector()
{}

void AiDirector::Update()
{
	WaveProcess();
	SpawnLogic();
}

void AiDirector::CreateStageObject()
{
	char path[50] = "Assets/ObjectData.txt";
	std::ifstream file(path);
	//ファイルがなければスルー
	if (!file.is_open())return;

	std::string line;
	int objNum = 0;
	while (std::getline(file, line))
	{
		//もし空行か、コメントだったらスルー
		if (line.empty() || line.rfind("//", 0) == 0)continue;
		//文字が入っていればチェックをしてループを抜ける
		std::stringstream ss(line);
		std::string key, eq;
		if (ss >> key >> eq)
		{
			if (key == "OBJ_NUM") { ss >> objNum; }
			else if (key == "BASE_BLOCK") { ss >> BASE_BLOCK; }
			else if(key == "BASE_OFFSET_Y")
			{
				ss >> BASE_OFFSET_Y;
				break;
			}
		}
	}
	int id = 0;
	VECTOR pos;
	VECTOR rot;
	VECTOR sca;
	//オブジェクトの数分ループ
	for (int i = 0; i < objNum; i++)
	{
		if (file.eof())break;

		while (std::getline(file, line))
		{
			//もし空行か、コメントだったらスルー
			if (line.empty() || line.rfind("//", 0) == 0)continue;
			//文字が入っていればチェックをしてループを抜ける
			std::stringstream ss(line);
			std::string key, eq;
			if (ss >> key >> eq)
			{
				if (key == "ID") { ss >> id; }
				else if (key == "POS") { ss >> pos.x >> pos.y >> pos.z; }
				else if (key == "ROT") { ss >> rot.x >> rot.y >> rot.z; }
				else if (key == "SCA")
				{
					ss >> sca.x >> sca.y >> sca.z;
					new StageObject(pos, rot, sca, id);
					break;
				}
			}
		}
	}
}

void AiDirector::CreateBase()
{
	std::vector<std::vector<int>> map;
	char path[50] = "Assets/Base.csv";
	CsvReader* csv = new CsvReader(path);
	int lines = csv->GetLines(); //csvの行数
	map.resize(lines);
	for (int y = 0; y < lines; y++) { //1行ずつ読む
		int cols = csv->GetColumns(y);
		map[y].resize(cols);
		for (int x = 0; x < cols; x++) {
			map[y][x] = csv->GetInt(y, x);
		}
	}
	delete csv;

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			Vector2 pos = Vector2((float)x, (float)y) * (float)BASE_BLOCK;
			pos += Vector2(BASE_BLOCK / 2.0f, BASE_BLOCK / 2.0f);
			pos.y += BASE_OFFSET_Y;
			if (map[y][x] != -1)new Base(pos, BASE_BLOCK);
			if (map[y][x] == 1 || map[y][x] == 2)
			{
				new MaterialWarehouse(pos, map[y][x]);
			}
			else if (map[y][x] == 3)new CraftTable(pos);
			else if (map[y][x] == 4)new Table(pos);
		}
	}
}

void AiDirector::WaveProcess()
{
	waveTime.Update();

	//もし次のウェーブまでの時間を経過したら
	if (waveTime.isOverTime(nextWaveTime))
	{
		currentWave++;

		remainingSpawnCount = WAVE_ENEMY_COUNT + (currentWave * ENEMY_INCREASE_RATE);

		nextWaveTime = waveTime.timer + WAVE_INTERVAL;
	}
}

void AiDirector::SpawnLogic()
{
	if (remainingSpawnCount <= 0)return;

	auto enemies = FindTagObjects(Tag::ENEMY);
	if (enemies.size() >= MAX_ACTIVE_ENEMIES)return;

	spawnTimer.Update();

	if (spawnTimer.IsEvery(SPAWN_INTERVAL))
	{
		CreateEnemy();
		remainingSpawnCount--;
	}
}

void AiDirector::CreateEnemy()
{
	Vector2 pos = CalculateSpawnPoint();

	int randVal = GetRand(100);
	if (randVal < probability.normal)new NormalZombie(pos);
	else if (randVal < probability.normal + probability.archer)new BowZombie(pos);
	else new TitanZombie(pos);
}

Vector2 AiDirector::CalculateSpawnPoint()
{
	auto players = FindTagObjects(Tag::PLAYER);
	Vector2 playerSub = players[1]->GetPos() - players[0]->GetPos();
	Vector2 playerCenter = players[0]->GetPos() + (playerSub * 0.5f);
	playerCenter.x = (playerCenter.x - (WIN_WIDTH / 2.0f)) * -1.0f + (WIN_WIDTH / 2.0f);
	Vector2 vec = playerCenter - Enemy::DESTINATION;
	vec = Math2D::Normalize(vec);
	Vector2 pos = Enemy::DESTINATION + vec * 2500;
	int randVal = GetRand(50) - 25;
	pos.x += randVal;
	pos.y += randVal;
	return pos;
}