#pragma once
#include"../Engine/Object/Character.h"
#include"../Engine/Tool/Lerp.h"

class Item;

class Player : public Character
{
public:
	Player(int index);
	~Player();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
	/// <summary>
	/// プレイヤーのIDを取得する関数
	/// </summary>
	/// <returns>1Pなら0、2Pなら1</returns>
	int GetId() { return id; }
	/// <summary>
	/// 所持しているアイテムに座標を適応する
	/// </summary>
	void ItemMove();
	/// <summary>
	/// 持っている武器が壊れた
	/// </summary>
	void BrokenHasWeapon();
	/// <summary>
	/// 攻撃時の移動関数（剣が呼ぶ）
	/// </summary>
	/// <param name="movePos">移動ベクトル</param>
	/// <param name="sec">移動時間</param>
	void MoveAttack(Vector2 move,float sec);
private:
	int hp;
	//１Pか２Pか
	int id;
	//持っているアイテム
	Item* hasItem = nullptr;
	//インタラクト可能なギミック
	GameObject* interactionGimmick = nullptr;
	//攻撃時移動のラープ
	Lerp<Vector2> moveLerp;
private:
	//壁と接触したときの処理
	void CollisionWall(GameObject* other);
	//ギミックと接触したときの処理
	void CollisionGimmick(GameObject* other);
	//ギミックのインタラクト
	void Interact();
	//攻撃（攻撃中ならtrueを返す）
	bool Attack();
public:
	static int MAX_HP;
	static float SPEED;
	static Vector2 SPAWN_POS[2];
	static float RADIUS;
	static float ITEM_OFFSET;
};