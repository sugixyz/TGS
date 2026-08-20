#pragma once
#include "Enemy.h"
#include "../Engine/Tool/BehaviorTree.h"
#include "Base.h"

enum class ArcherState
{
	PLAYER_ATTACK,
	STAGE_ATTACK,
	SEARCH,
	PATROL
};

class Archer : public Enemy
{
public:
	Archer(Vector2 pos);
	~Archer();
	void Update() override;
	void Draw() override;
public:
	NodeResult PlayerAttackAction();
	bool CanPlayerAttack();
	NodeResult StageAttackAction();
	bool CanStageAttack();
	NodeResult Search();
	bool CanSearch();
	NodeResult Patrol();
	void OnCollision(Layer myLayer, GameObject* other, Layer otherLayer) override;
private:
	Selector root;
	GameObject* target;
	Base* stageTarget;
	ArcherState state;
	bool isPlayerSensed = false;
	bool isPlayerInAttackRange = false;
	bool isStageInAttackRange = false;
};