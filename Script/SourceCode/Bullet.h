#pragma once
#include"Attack.h"

class Bullet : public Attack
{
public:
	Bullet(Vector2 pos, Vector2 vel,float rad);
	~Bullet();
	void Update() override;
	void Draw() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
	void Move() override;
};