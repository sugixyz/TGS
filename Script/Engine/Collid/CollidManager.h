#pragma once
#include<vector>
#include"Collider.h"

class GameObject;
enum class Tag : int;

namespace CollidManager
{
	void Update(); // 更新
	void Draw(); // 描画

	/// <summary>
	/// オブジェクト同士の接触判定
	/// </summary>
	/// <param name="listA">判定するオブジェクトリストA</param>
	/// <param name="listB">判定するオブジェクトリストB</param>
	void Collision(const std::vector<GameObject*> listA, const std::vector<GameObject*> listB);

	/// <summary>
	/// 指定したタグのオブジェクトとの当たり判定を要求する関数
	/// </summary>
	/// <param name="obj">自分のインスタンス</param>
	/// <param name="col">自分のコライダー</param>
	/// <param name="tag">判定したい対象のタグ</param>
	/// <returns>当たっていればtrue</returns>
	bool CollisionCheckRequest(GameObject* obj, const Collider& col, Tag tag);

	/// <summary>
	/// 指定したタグのオブジェクトとの当たり判定を要求する関数
	/// </summary>
	/// <param name="obj">自分のインスタンス</param>
	/// <param name="col">自分のコライダー</param>
	/// <param name="tag">判定したい対象のタグ</param>
	void CollisionRequest(GameObject* obj, const Collider& col, Tag tag);

	/// <summary>
	/// 接触可能かどうか
	/// </summary>
	/// <param name="colA">判定するコライダーA</param>
	/// <param name="colB">判定するコライダーB</param>
	/// <returns>
	/// 接触不可:0
	/// CtoC:1
	/// BtoB:2
	/// CtoB:3
	/// BtoC;4</returns>
	int CanHit(const Collider& colA, const Collider& colB);

	/// <summary>
	/// カプセル同士の接触判定
	/// </summary>
	/// <param name="objA">判定するオブジェクトA</param>
	/// <param name="colA">判定するコライダーA</param>
	/// <param name="objB">判定するオブジェクトB</param>
	/// <param name="colB">判定するコライダーB</param>
	/// <returns>接触していればtrue</returns>
	bool CheckCapsuleCollision(GameObject* objA,Collider colA, GameObject* objB,Collider colB);

	/// <summary>
	/// ボックス同士の接触判定
	/// </summary>
	/// <param name="objA">判定するオブジェクトA</param>
	/// <param name="colA">判定するコライダーA</param>
	/// <param name="objB">判定するオブジェクトB</param>
	/// <param name="colB">判定するコライダーB</param>
	/// <returns>接触していればtrue</returns>
	bool CheckBoxCollision(GameObject* objA, Collider colA, GameObject* objB, Collider colB);

	/// <summary>
	/// カプセルとボックスの接触判定
	/// </summary>
	/// <param name="objA">判定するオブジェクトA</param>
	/// <param name="colA">判定するコライダーA</param>
	/// <param name="objB">判定するオブジェクトB</param>
	/// <param name="colB">判定するコライダーB</param>
	/// <returns>接触していればtrue</returns>
	bool CheckCalsuleBoxCollision(GameObject* objA, Collider colA, GameObject* objB, Collider colB);

	/// <summary>
	/// コライダーの描画
	/// </summary>
	/// <param name="obj">コライダーの描画をしたいオブジェクト</param>
	void DrawCollider(GameObject* obj);

	/// <summary>
	/// 線分同士の最短距離を求める
	/// </summary>
	/// <param name="a1">線分Aの始点</param>
	/// <param name="a2">線分Aの終点</param>
	/// <param name="b1">線分Bの始点</param>
	/// <param name="b2">線分Bの終点</param>
	/// <returns>最短距離の2乗</returns>
	float GetLineMinDist(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	/// <summary>
	/// 線分とボックスの最短距離を求める
	/// </summary>
	/// <param name="a1">線分の始点</param>
	/// <param name="a2">線分の終点</param>
	/// <param name="b1">ボックスの始点</param>
	/// <param name="b2">ボックスの終点</param>
	/// <returns>最短距離の2乗</returns>
	float GetLineBoxDist(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

}