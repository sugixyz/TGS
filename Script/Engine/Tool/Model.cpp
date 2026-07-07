#include "Model.h"
#include<map>
#include<assert.h>
#include"DxLib.h"

namespace
{
	std::map<std::string, int> handles;
}

void Model::Initialize()
{	
	SetHandle("Player", "Player01.mv1");
	SetHandle("Player", "Player02.mv1");
	SetHandle("StageObject", "CraftTable.mv1");
	SetHandle("StageObject", "Material1.mv1");
	SetHandle("StageObject", "Material2.mv1");
	SetHandle("StageObject", "Table.mv1");
	SetHandle("StageObject", "StageObject01.mv1");
	SetHandle("StageObject", "StageObject02.mv1");
	SetHandle("Item", "bom.mv1");
	SetHandle("Item", "bullet.mv1");
	SetHandle("Item", "character.mv1");
	SetHandle("Item", "gun.mv1");
	SetHandle("Item", "gunpowder.mv1");
	SetHandle("Item", "ingod.mv1");
	SetHandle("Item", "sword.mv1");
	SetHandle("Item", "toulbox.mv1");
	SetHandle("Enemy", "Enemy.mv1");

}

void Model::Release()
{
	for (auto h : handles)
	{
		MV1DeleteModel(h.second);
	}
}

int Model::Load(std::string fileKey)
{
	int hModel = MV1DuplicateModel(handles[fileKey]);
	return hModel;
}

void Model::SetHandle(std::string folder, std::string file)
{
	char path[50];
	int handle = -1;
	sprintf_s(path, sizeof(path), "Assets/%s/%s", folder.c_str(), file.c_str());
	handle = MV1LoadModel(path);
	assert(handle > 0);
	handles[file] = handle;
}
