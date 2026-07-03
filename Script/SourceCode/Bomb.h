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
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
	void Move() override;
private:
	Lerp<Vector2> moveLerp;
};