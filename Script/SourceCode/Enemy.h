#pragma once
#include"../Engine/Object/Character.h"
#include "Item.h"

class Enemy : public Character
{
public:
	Enemy(Tag tag) 
		:Character(tag),hp(-1)
	{}
	virtual ~Enemy() {}
	/// <summary>
	/// 攻撃用の共通仮想関数
	/// </summary>
	virtual void Attack() {}
	/// <summary>
	/// ウィンドウの範囲外に行っていないか
	/// </summary>
	virtual void CheckOutRange()
	{
		//if (position.x <= -radius * 2)DestroyMe();
		//else if (position.x >= WIN_WIDTH + radius * 2)DestroyMe();
		//else if (position.y <= -radius * 2)DestroyMe();
		//else if (position.y >= WIN_HEIGHT + radius * 2)DestroyMe();

		Vector2 sub = DESTINATION - position;
		float lenghtSq = Math2D::LengthSq(sub);
		if (lenghtSq >= 4000)DestroyMe();
	}
	/// <summary>
	/// ドロップ率計算
	/// </summary>
	virtual void DROP_RATE(Tag tag, Vector2 pos)
	{
		int rnd = GetRand(99);
		if (rnd >= dropRate_) return;

		Item* item = new Item(tag);
		item->SetItemType(MATERIAL_ENEMY);
		item->SetPos(pos);
	}
protected:
	int hp;
	int dropRate_ = 30;//ドロップ率(%)
public:
	inline static Vector2 DESTINATION;
};