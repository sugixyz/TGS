#pragma once
#include"Enemy.h"
#include"../Engine/Tool/BehaviorTree.h"

enum class TestState
{
	ATTACK,
	CHASE,
	PATROL
};

class TestEnemy : public Enemy
{
public:
	TestEnemy(Vector2 pos);
	~TestEnemy();
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
	TestState state;
private:
	void DrawStateText();
};