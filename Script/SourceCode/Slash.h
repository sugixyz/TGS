#pragma once
#include"Attack.h"

class Slash : public Attack
{
public:
	Slash(GameObject* pl,Vector2 move, float rad, float sec);
	~Slash();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
private:
	//攻撃を発動したプレイヤーのポインタ
	GameObject* owner;
	//プレイヤーから発生位置がどれだけずれているか
	Vector2 moveVec;
	//消えるまでのタイマー
	Timer dethTimer;
	//消えるまでの時間
	float time;
};