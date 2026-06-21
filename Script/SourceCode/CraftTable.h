#pragma once
#include"Gimmick.h"

class CraftTable : public Gimmick
{
public:
	CraftTable(Vector2 pos);
	~CraftTable();
	void Draw() override;
	/// <summary>
	/// プレイヤーがインタラクトする関数
	/// </summary>
	/// <param name="item">プレイヤーの持っているアイテム</param>
	/// <returns>クラフト台を通した結果</returns>
	Item* Interact(Item* item) override;
private:
	Item* Craft(Item* a);
};