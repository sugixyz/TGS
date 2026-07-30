#pragma once
#include "Enemy.h"

class Archer : public Enemy
{
public:
	Archer(Tag tag) : Enemy(tag) {}
	~Archer() {}
	void Initialize();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
};