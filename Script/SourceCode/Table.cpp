#include "Table.h"
#include"Item.h"

Table::Table(Vector2 pos)
	:Gimmick(Tag::GIMMICK)
{
	position = pos;

	uint32_t mask = (uint32_t)Layer::PLAYER;
	SetCenterCircle(INTERACT_LENGHT, Layer::GIMMICK, mask);
}

Table::~Table()
{}

void Table::Draw()
{
	float x = position.x - 64 / 2;
	float y = position.y - 64 / 2;
	DrawBox(x, y, x + 64, y + 64, COL_MAGENTA, TRUE);
}

Item* Table::Interact(Item* item)
{
	//もし机にアイテムがあったら
	if(hasItem != nullptr)
	{
		//プレイヤーがアイテムを持ってないなら机のアイテムを渡す
		if (item == nullptr)
		{
			Item* tmp = hasItem;
			hasItem = nullptr;
			return tmp;
		}
		//プレイヤーがアイテムを持っているならそのまま返す
		return item;
	}
	//もし机にアイテムがなかったら
	else
	{
		//プレイヤーがアイテムを持っているならアイテムを貰う
		if (item != nullptr)
		{
			hasItem = item;
			hasItem->SetPos(Vector2(position));
		}
		//プレイヤーからアイテムを貰うのでnullptrを返す
		return nullptr;
	}
}
