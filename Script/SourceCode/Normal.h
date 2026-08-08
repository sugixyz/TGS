#pragma once
#include "Enemy.h"
#include "../Engine/Tool/BehaviorTree.h"

enum class State
{
	ATTACK,
	CHASE,
	PATROL
};

class Normal : public Enemy
{
public:
	Normal(Vector2 pos);
	~Normal();
	void Update() override;
	void Draw() override;
public:
	NodeResult AttackAction();
	bool CanAttack();
	NodeResult Chase();
	bool CanChase();
	NodeResult Patrol();
private:
	Selector root;
	GameObject* target;
	State state;
};