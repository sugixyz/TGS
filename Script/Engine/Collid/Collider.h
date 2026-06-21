#pragma once
#include"../Tool/Math2D.h"
#include<cstdint>

//レイヤーマスク
enum class Layer : uint32_t
{
	NONE = 0,
	PLAYER = 1 << 0,
	ENEMY = 1 << 1,
	STAGE = 1 << 2,
	GIMMICK = 1 << 3,
	PLAYER_ATTACK = 1 << 4,
	ENEMY_ATTACK = 1 << 5
};

//コライダーの構造体
struct Collider
{
	//カプセル用
	Vector2 cPosA;
	Vector2 cPosB;
	float radius = 0.0f;
	//判定をしたい対象のレイヤーマスク
	uint32_t cLayerMask = 0x000000;
	bool hasCapsule = false;

	//ボックス用
	Vector2 bPosA;
	Vector2 bPosB;
	float width;
	float height;
	//判定をしたい対象のレイヤーマスク
	uint32_t bLayerMask = 0x000000;
	bool hasBox = false;

	//オブジェクトに設定されているか
	bool hasObject = false;
	//自分を識別するレイヤー
	Layer myLeyer = Layer::NONE;

	/// <summary>
	/// カプセルコライダーのセット
	/// </summary>
	/// <param name="startPos">始点</param>
	/// <param name="endPos">終点</param>
	/// <param name="rad">半径</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCapsule(Vector2 startPos, Vector2 endPos, float rad, Layer layer, uint32_t mask = 0x00000000)
	{
		cPosA = startPos;
		cPosB = endPos;
		radius = rad;
		myLeyer = layer;
		cLayerMask = mask;
		hasObject = true;
		hasCapsule = true;
	}

	/// <summary>
	/// ボックスコライダーのセット
	/// </summary>
	/// <param name="startPos">始点</param>
	/// <param name="endPos">終点</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetBox(Vector2 startPos, Vector2 endPos, Layer layer, uint32_t mask = 0x00000000)
	{
		bPosA = startPos;
		bPosB = endPos;
		myLeyer = layer;
		width = bPosB.x - bPosA.x;
		height = bPosB.y - bPosA.y;
		bLayerMask = mask;
		hasObject = true;
		hasBox = true;
	}
};