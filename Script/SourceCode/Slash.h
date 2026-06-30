#pragma once
#include"Attack.h"

class Slash : public Attack
{
public:
	Slash(Vector2 pos,float rad);
	~Slash();
	void Update() override;
	void Draw() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
	GameObject* GetTarget() { return target; }
private:
	//ターゲットのポインタ
	GameObject* target;
	//消えるまでのタイマー
	Timer dethTimer;
	//消えるまでの時間
	float time;
};