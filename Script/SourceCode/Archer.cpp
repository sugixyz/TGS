#include "Archer.h"
#include "../Engine/Collid/CollidManager.h"
#include "../Engine/Tool/Model.h"
#include "Arrow.h"

Archer::Archer(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	auto playerAttackNode = new ActionNode<Archer>(this, &Archer::PlayerAttackAction);
	auto playerAttackCheckNode = new ConditionNode<Archer>(this, &Archer::CanPlayerAttack);
	Sequence* playerAttack = new Sequence();
	playerAttack->AddChildren(playerAttackCheckNode);
	playerAttack->AddChildren(playerAttackNode);

	auto stageAttackNode = new ActionNode<Archer>(this, &Archer::StageAttackAction);
	auto stageAttackCheckNode = new ConditionNode<Archer>(this, &Archer::CanStageAttack);
	Sequence* stageAttack = new Sequence();
	stageAttack->AddChildren(stageAttackCheckNode);
	stageAttack->AddChildren(stageAttackNode);

	auto searchNode = new ActionNode<Archer>(this, &Archer::Search);
	auto searchCheckNode = new ConditionNode<Archer>(this, &Archer::CanSearch);
	Sequence* search = new Sequence();
	search->AddChildren(searchCheckNode);
	search->AddChildren(searchNode);

	auto patrolNode = new ActionNode<Archer>(this, &Archer::Patrol);

	//プレイヤー優先:PlayerAttack→StageAttack→Search→Patrol
	root.AddChildren(playerAttack);
	root.AddChildren(stageAttack);
	root.AddChildren(search);
	root.AddChildren(patrolNode);

	position = pos;
	hp = 2;
	speed = 80.0f;
	radius = 25.0f;
	attackRadius = 500.0f;//調整済み:遠方から立ち止まって攻撃するため
	sensedRange = 500.0f;
	coolTime = 0.0f;
	coolTimeMax = 2.0f;
	dropRate = 15;
	target = FindTagObject(Tag::PLAYER);
	stageTarget = FindGameObject<Base>(Tag::STAGE);
	state = ArcherState::PATROL;

	uint32_t mask = (uint32_t)Layer::PLAYER_ATTACK;
	SetCenterCircle(Layer::ENEMY, mask);
	uint32_t senseMask = (uint32_t)Layer::PLAYER;
	GameObject::SetCenterCircle(sensedRange, Layer::ENEMY_SENSE, senseMask);
	uint32_t attackSenseMask = (uint32_t)Layer::PLAYER | (uint32_t)Layer::STAGE;
	GameObject::SetCenterCircle(attackRadius, Layer::ENEMY_ATTACK_SENSE, attackSenseMask);

	hModel = Model::Load("Archer.mv1");
	assert(hModel > 0);
}

Archer::~Archer()
{
}

void Archer::Update()
{
	if (coolTime > 0.0f) coolTime -= gDeltaTime;

	root.Tick();
	CheckOutRange();

	isPlayerSensed = false;
	isPlayerInAttackRange = false;
	isStageInAttackRange = false;
}

void Archer::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		DrawCircle((int)position.x, (int)position.y, (int)radius, COL_BLUE, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

NodeResult Archer::PlayerAttackAction()
{
	state = ArcherState::PLAYER_ATTACK;
	coolTime = coolTimeMax;

	Vector2 targetPos = target->GetPos();
	new Arrow(position, targetPos, 0.6f);//0.6秒で着弾(仮の飛翔時間)
	return NodeResult::SUCCESS;
}

bool Archer::CanPlayerAttack()
{
	if (!target) return false;
	if (coolTime > 0.0f) return false;
	return isPlayerInAttackRange;
}

NodeResult Archer::StageAttackAction()
{
	state = ArcherState::STAGE_ATTACK;
	coolTime = coolTimeMax;

	Vector2 stagePos = stageTarget->GetPos();
	new Arrow(position, stagePos, 0.8f);//拠点は少し飛翔時間長め(仮)
	return NodeResult::SUCCESS;
}

bool Archer::CanStageAttack()
{
	if (!stageTarget) return false;
	if (coolTime > 0.0f) return false;
	return isStageInAttackRange;
}

NodeResult Archer::Search()
{
	state = ArcherState::SEARCH;
	Vector2 targetPos = target->GetPos();
	MoveToward(targetPos);
	return NodeResult::SUCCESS;
}

bool Archer::CanSearch()
{
	if (!target) return false;
	return isPlayerSensed;
}

NodeResult Archer::Patrol()
{
	state = ArcherState::PATROL;
	return NodeResult::SUCCESS;
}

void Archer::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
{
	Enemy::OnCollision(myLayer, other, otherLayer);

	if (myLayer == Layer::ENEMY_SENSE && other->GetTag() == Tag::PLAYER)
	{
		isPlayerSensed = true;
	}
	else if (myLayer == Layer::ENEMY_ATTACK_SENSE)
	{
		if (other->GetTag() == Tag::PLAYER) isPlayerInAttackRange = true;
		else if (other->GetTag() == Tag::STAGE) isStageInAttackRange = true;
	}
}