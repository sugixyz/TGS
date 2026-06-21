#pragma once
#include"Attack.h"
#include"../Engine/Tool/Lerp.h"

class Bomb : public Attack
{
public:
	Bomb(Vector2 start, Vector2 end, float rad,float time);
	~Bomb();
	void Update() override;
	void Draw() override;
	//void OnCollision(GameObject* other) override;
	void Move() override;
	void IEDestroy();
private:
	Lerp<Vector2> moveLerp;
	Coroutine coroutine;
};