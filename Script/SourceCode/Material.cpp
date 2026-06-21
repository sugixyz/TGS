#include "Material.h"

Material::Material(int id)
	:Item(Tag::ITEM)
{
	if (id == 1)type = ItemType::MATERIAL1;
	else if (id == 2)type = ItemType::MATERIAL2;
}

Material::~Material()
{
}

void Material::Draw()
{
	float x = position.x;
	float y = position.y;

	unsigned int col = COL_WHITE;
	if (type & ItemType::MATERIAL1)col = COL_BLACK;
	else if (type & ItemType::MATERIAL2)col = COL_RED;

	DrawCircle(x, y, 10, col, TRUE);
}
