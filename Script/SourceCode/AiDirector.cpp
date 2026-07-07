#include "AiDirector.h"
#include"Player.h"
#include"Normal.h"
#include"StageObject.h"
#include"Base.h"
#include"MaterialWarehouse.h"
#include"CraftTable.h"
#include"Table.h"
#include"../Engine/Tool/ParamLoader.h"
#include"../Engine/Tool/CsvReader.h"

AiDirector::AiDirector()
	:GameObject(Tag::SYSTEM)
{
	new Player(0);
	new Player(1);
	new Normal(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 4));
	new Normal(Vector2(WIN_WIDTH / 2 - 50, WIN_HEIGHT / 4 - 50));
	new Normal(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 4 + 100));
	new Normal(Vector2(WIN_WIDTH / 2 + 50, WIN_HEIGHT / 4 - 100));

	CreateStageObject();
	CreateBase();
}

AiDirector::~AiDirector()
{}

void AiDirector::LoadParam()
{

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