#pragma once
#include "GameObject.h"
/// <summary>
/// ゲーム内のキャラクターの基底クラス
/// </summary>
class Character : public GameObject
{
public:
	Character(Tag tag)
	:GameObject(tag)
	{}
	~Character() {}
	/// <summary>
	/// 速度の設定
	/// </summary>
	/// <param name="vel">適応する速度</param>
	void SetVel(Vector2 vel) { velocity = vel; }
	/// <summary>
	/// 速度を取得する
	/// </summary>
	/// <returns>現在の速度</returns>
	Vector2 GetVel() { return velocity; }

	/// <summary>
	/// ポジションを中心とした円コライダーのセット
	/// </summary>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCenterCircle(Layer layer, uint32_t mask = 0x00000000)
	{
		GameObject::SetCenterCircle(radius, layer, mask);
	}

	/// <summary>
	/// ポジションを中心としたボックスコライダーのセット
	/// </summary>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCenterBox(Layer layer, uint32_t mask = 0x00000000)
	{
		GameObject::SetCenterBox(radius, layer, mask);
	}

	/// <summary>
	/// 移動用の共通仮想関数
	/// </summary>
	virtual void Move() {}
protected:
	//速度
	Vector2 velocity;
	//半径
	int radius;
};