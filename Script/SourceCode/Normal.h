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
	void OnCollision(Layer myLayer, GameObject* other, Layer otherLayer) override;
private:
	Selector root;
	GameObject* target;
	Base* stageTarget;
	State state;
	Vector2 lastKnownPos;
	bool hasLastKnownPos = false;
	bool isPlayerSensed = false;//感知範囲内にプレイヤーがいるか
	bool isPlayerInAttackRange = false;//攻撃感知範囲内にプレイヤーがいるか
};