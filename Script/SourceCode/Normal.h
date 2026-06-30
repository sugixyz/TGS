#pragma once
#include"Enemy.h"

class Normal : public Enemy
{
public:
	Normal();
	~Normal();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLayer, GameObject* other, Layer otherLayer) override;
public:
	static int MAX_HP;
	static float  SPEED;
	static float RADIUS;
	static float ATTACK_RADIUS;
	static float SENSED_RANGE;
	static float ATTACK_INTERVAL;
};