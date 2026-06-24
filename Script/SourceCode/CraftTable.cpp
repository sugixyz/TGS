#include "CraftTable.h"
#include"Material.h"
#include"Weapon1.h"
#include"Weapon2.h"
#include"Weapon3.h"

CraftTable::CraftTable(Vector2 pos)
	:Gimmick(Tag::GIMMICK)
{
	position = pos;
	char path[50] = "Assets/StageObject/CraftTable.mv1";
	hModel = MV1LoadModel(path);
	assert(hModel > 0);

	uint32_t mask = (uint32_t)Layer::PLAYER;
	SetCenterCircle(INTERACT_LENGHT, Layer::GIMMICK, mask);
}

CraftTable::~CraftTable()
{}

void CraftTable::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x - 64 / 2;
		float y = position.y - 64 / 2;
		DrawBoxAA(x, y, x + 64, y + 64, COL_CYAN, TRUE);
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

Item* CraftTable::Interact(Item* item)
{
	//もし台にアイテムがあったら
	if (hasItem != nullptr)
	{
		//プレイヤーがアイテムを持ってないなら台のアイテムを渡す
		if (item == nullptr)
		{
			Item* tmp = hasItem;
			hasItem = nullptr;
			return tmp;
		}

		//クラフト
		Item* craft = Craft(item);
		//もしクラフトに成功していればクラフト結果を台に、プレイヤーにnullptrを返す
		if (craft != nullptr)
		{
			hasItem->DestroyMe();
			item->DestroyMe();
			hasItem = craft;
			hasItem->SetPos(Vector2(position));
			return nullptr;
		}
		//クラフトに失敗していればそのまま返す
		return item;
	}
	//もし台にアイテムがなかったら
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

Item* CraftTable::Craft(Item* a)
{
	uint32_t craftKey = a->GetItemType() | hasItem->GetItemType();

	//クラフトレシピ
	if (craftKey == (ItemType::MATERIAL1 | ItemType::MATERIAL2))return new Weapon1();
	else if (craftKey == (ItemType::MATERIAL1 | ItemType::MATERIAL1))return new Weapon2();
	else if (craftKey == (ItemType::MATERIAL2 | ItemType::MATERIAL2))return new Weapon3();
	else if (craftKey == (ItemType::WEAPON1 | ItemType::MATERIAL_ENEMY))return nullptr;
	else if (craftKey == (ItemType::WEAPON2 | ItemType::MATERIAL_ENEMY))return nullptr;
	else if (craftKey == (ItemType::WEAPON3 | ItemType::MATERIAL_ENEMY))return nullptr;

	return nullptr;
}
