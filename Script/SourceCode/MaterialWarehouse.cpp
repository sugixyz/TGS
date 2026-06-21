#include "MaterialWarehouse.h"
#include"Material.h"

MaterialWarehouse::MaterialWarehouse(Vector2 pos,int id)
	:Gimmick(Tag::GIMMICK)
{
	position = pos;
	materialId = id;

	uint32_t mask = (uint32_t)Layer::PLAYER;
	SetCenterCircle(INTERACT_LENGHT, Layer::GIMMICK, mask);
}

MaterialWarehouse::~MaterialWarehouse()
{}

void MaterialWarehouse::Draw()
{
	unsigned int col = COL_WHITE;
	if(materialId == 1)col = COL_YELLOW;
	if(materialId == 2)col = COL_BLUE;
	float x = position.x - 64 / 2;
	float y = position.y - 64 / 2;
	DrawBox(x, y, x + 64, y + 64, col, TRUE);
}

Item* MaterialWarehouse::Interact(Item* item)
{
	//何か持っているならそのまま返す
	if (item != nullptr)return item;

	//何も持っていないなら、IDに対応するアイテムを渡す
	return new Material(materialId);
}
