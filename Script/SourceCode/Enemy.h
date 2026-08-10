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
	/// モデル描画(共通処理)
	/// </summary>
	virtual void Draw() override
	{
		Convert2Dto3D();
		DrawModel();
	}
	/// <summary>
	/// ドロップ率計算
	/// </summary>
	virtual void DropRate(Vector2 pos)
	{
		int rnd = GetRand(99);
		if (rnd >= dropRate) return;

		Item* item = new Item(Tag::ITEM);
		item->SetItemType(MATERIAL_ENEMY);
		item->SetPos(pos);
	}
	/// <summary>
	/// 撃破時の共通処理(アイテムドロップ＋破棄)
	/// </summary>
	virtual void Die()
	{
		DropRate(position);
		DestroyMe();
	}
	/// <summary>
	/// 被弾処理(共通)
	/// </summary>
	virtual void OnCollision(Layer myLayer, GameObject* other, Layer otherLayer) override
	{
		if (other->GetTag() == Tag::ATTACK)
		{
			hp -= 1;
			if (hp <= 0) Die();
		}
	}
	/// <summary>
	/// 敵が追いかける目的地の設定(プレイヤー側から毎フレーム呼んでもらう)
	/// </summary>
	static void SetDestination(const Vector2& pos) { DESTINATION = pos; }
	/// <summary>
	/// 現在の目的地を取得(必要なら)
	/// </summary>
	static Vector2 GetDestination() { return DESTINATION; }
	void MoveToward(const Vector2& targetPos)
	{
		direction = Math2D::Normalize(targetPos - position);
		position += direction * speed * gDeltaTime;
	}
	
protected:
	int hp;//体力
	float speed;//移動速度
	float radius;//半径
	float attackRadius;//攻撃範囲
	float sensedRange;//感知範囲
	float coolTime;//クールタイム
	float coolTimeMax = 1.0f;
	int dropRate;//ドロップ率(%)
public:
	inline static Vector2 DESTINATION;
};