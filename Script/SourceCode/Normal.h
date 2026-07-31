#pragma once
#include "Enemy.h"
#include "../Engine/Tool/Model.h"

class Normal : public Enemy
{
public:
	Normal(Tag tag) : Enemy(tag) 
	{
		speed_ = 150.0f;
		hp = 1;
		hModel = Model::Load("Enemy.mv1");
	}
	~Normal() {}
	void Initialize();
	void Update() override;
	void Draw() override;
	void Move() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
};