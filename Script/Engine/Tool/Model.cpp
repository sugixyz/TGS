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
	SetHandle("Player01");
	SetHandle("Player02");
	SetHandle("CraftTable");
	SetHandle("Material01");
	SetHandle("Material02");
	SetHandle("Table");
	SetHandle("StageObject01");
	SetHandle("StageObject02");
	SetHandle("Bomb");
	SetHandle("Bullet");
	SetHandle("Gun");
	SetHandle("GunPowder");
	SetHandle("Ingod");
	SetHandle("Sword");
	SetHandle("ToolBox");
	SetHandle("Enemy");

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

void Model::SetHandle(std::string file)
{
	std::string path;
	int handle = -1;
	path = "Assets/Models/" + file + "/" + file + ".mv1";
	handle = MV1LoadModel(path.c_str());
	assert(handle > 0);
	handles[file + ".mv1"] = handle;
}
