#include "MaterialWarehouse.h"
#include"Material.h"

MaterialWarehouse::MaterialWarehouse(Vector2 pos,int id)
	:Gimmick(Tag::GIMMICK)
{
	position = pos;
	materialId = id;

	char path[50];
	sprintf_s(path, sizeof(path), "Assets/StageObject/Material%d.mv1", id);
	hModel = MV1LoadModel(path);
	assert(hModel > 0);

	uint32_t mask = (uint32_t)Layer::PLAYER;
	SetCenterCircle(INTERACT_LENGHT, Layer::GIMMICK, mask);
}

MaterialWarehouse::~MaterialWarehouse()
{}

void MaterialWarehouse::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		unsigned int col = COL_WHITE;
		if (materialId == 1)col = COL_YELLOW;
		if (materialId == 2)col = COL_BLUE;
		float x = position.x - 64 / 2;
		float y = position.y - 64 / 2;
		DrawBoxAA(x, y, x + 64, y + 64, col, TRUE);
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

Item* MaterialWarehouse::Interact(Item* item)
{
	//何か持っているならそのまま返す
	if (item != nullptr)return item;

	//何も持っていないなら、IDに対応するアイテムを渡す
	return new Material(materialId);
}
