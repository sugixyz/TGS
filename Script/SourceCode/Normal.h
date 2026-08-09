#pragma once　
#include "Enemy.h"
#include "../Engine/Tool/BehaviorTree.h"
#include "Base.h"

enum class State
{
	ATTACK,//攻撃
	CHASE,//プレイヤー追跡
	SEARCH,//探索
	STAGE_ATTACK,//ステージ攻撃
	PATROL//巡回ポイント移動
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
	NodeResult Search();
	bool CanSearch();
	NodeResult StageAttack();
	bool CanStageAttack();
private:
	Selector root;
	GameObject* target;
	Base* stageTarget;
	State state;
	Vector2 lastKnownPos;
	bool hasLastKnownPos = false;
};