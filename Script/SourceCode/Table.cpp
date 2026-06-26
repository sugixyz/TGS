#include "Table.h"
#include"Item.h"

Table::Table(Vector2 pos)
	:Gimmick(Tag::GIMMICK)
{
	position = pos;
	char path[50] = "Assets/StageObject/Table.mv1";
	hModel = MV1LoadModel(path);
	assert(hModel > 0);

	uint32_t mask = (uint32_t)Layer::PLAYER;
	SetCenterCircle(INTERACT_LENGHT, Layer::GIMMICK, mask);
}

Table::~Table()
{
	MV1DeleteModel(hModel);
}

void Table::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x - 64 / 2;
		float y = position.y - 64 / 2;
		DrawBoxAA(x, y, x + 64, y + 64, COL_MAGENTA, TRUE);
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
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
