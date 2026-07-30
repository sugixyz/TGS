#pragma once
#include "Enemy.h"

class Normal : public Enemy
{
public:
	Normal(Tag tag) : Enemy(tag), hp(-1), hModel_(-1) {}
	~Normal() {}
	void Initialize();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
private:
	int hp;
	int hModel_;
};