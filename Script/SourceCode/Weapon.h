#pragma once
#include"Item.h"

class Player;

class Weapon : public Item
{
public:
	Weapon(Tag tag)
		:Item(tag)
	{
	}
	virtual ~Weapon() {}
	/// <summary>
	/// 攻撃用の仮想関数
	/// </summary>
	/// <param name="owner">所持しているプレイヤー</param>
	virtual void Attack(Player* owner) {}
	/// <summary>
	/// 攻撃中かどうかを更新
	/// </summary>
	/// <param name="attack">攻撃中ならtrue</param>
	void IsAttack(bool attack) { isAttack = attack; }
	/// <summary>
	/// 武器を強化する
	/// </summary>
	virtual void EnhanceWeapon() {}
protected:
	//アタック中かどうか
	bool isAttack = false;
	//残りの使用可能回数
	int life = 0;
	//クールタイム
	float coolTime = 0.0f;
	//攻撃範囲
	float attackRadius = 0.0f;
	//強化済みかどうか
	bool isEnhanced = false;
};