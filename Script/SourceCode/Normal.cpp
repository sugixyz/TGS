#include "Normal.h"
#include "../Engine/Collid/CollidManager.h"
#include"../Engine/Tool/Model.h"

Normal::Normal(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
    auto attackNode = new ActionNode<Normal>(this, &Normal::AttackAction);
    auto attackCheckNode = new ConditionNode<Normal>(this, &Normal::CanAttack);
    Sequence* attack = new Sequence();
    attack->AddChildren(attackCheckNode);
    attack->AddChildren(attackNode);

    auto chaseNode = new ActionNode<Normal>(this, &Normal::Chase);
    auto chaseCheckNode = new ConditionNode<Normal>(this, &Normal::CanChase);
    Sequence* chase = new Sequence();
    chase->AddChildren(chaseCheckNode);
    chase->AddChildren(chaseNode);

    auto searchNode = new ActionNode<Normal>(this, &Normal::Search);
    auto searchCheckNode = new ConditionNode<Normal>(this, &Normal::CanSearch);
    Sequence* search = new Sequence();
    search->AddChildren(searchCheckNode);
    search->AddChildren(searchNode);

    auto stageAttackNode = new ActionNode<Normal>(this, &Normal::StageAttack);
    auto stageAttackCheckNode = new ConditionNode<Normal>(this, &Normal::CanStageAttack);
    Sequence* stageAttack = new Sequence();
    stageAttack->AddChildren(stageAttackCheckNode);
    stageAttack->AddChildren(stageAttackNode);

	auto patrolNode = new ActionNode<Normal>(this, &Normal::Patrol);

	root.AddChildren(attack);
	root.AddChildren(chase);
    root.AddChildren(search);
    root.AddChildren(stageAttack);
	root.AddChildren(patrolNode);

    position = pos;
    hp = 1;
    speed = 100.0f;
    radius = 25.0f;
    attackRadius = 50.0f;
    sensedRange = 250.0f;
    coolTime = 0.0f;
    dropRate = 5;
    target = FindTagObject(Tag::PLAYER);
    stageTarget = FindGameObject<Base>(Tag::STAGE);
    state = State::PATROL;

	hModel = Model::Load("Enemy.mv1");
	assert(hModel > 0);
}

Normal::~Normal()
{
}

void Normal::Update()
{
    if (coolTime > 0.0f)
    {
        coolTime -= gDeltaTime;
    }

    root.Tick();
    CheckOutRange();
}

void Normal::Draw()
{
    if (mode == DEBUG || mode == DOUBLE_MODE)
    {
        float x = position.x;
        float y = position.y;

        DrawCircle((int)x, (int)y, (int)radius, COL_GREEN, TRUE);
    }
    if (mode == NORMAL || mode == DOUBLE_MODE)
    {
        Convert2Dto3D();
        scale3 = { 0.01f,0.01f,0.01f };
        DrawModel();
    }
}

NodeResult Normal::AttackAction()
{
    state = State::ATTACK;
    coolTime = coolTimeMax;//攻撃したらクールタイムをセット

    Collider col;
    Vector2 zero(0, 0);
    col.SetCapsule(zero, zero, radius, Layer::ENEMY_ATTACK, (uint32_t)Layer::PLAYER);
    CollidManager::CollisionRequest(this, col, Tag::PLAYER);
    return NodeResult::SUCCESS;
}

bool Normal::CanAttack()
{
    if (!target) return false;
    if (coolTime > 0.0f) return false;//クールタイム中は攻撃できない
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= attackRadius * attackRadius)return true;
    else return false;
}

NodeResult Normal::Chase()
{
    state = State::CHASE;
    Vector2 targetPos = target->GetPos();
    lastKnownPos = targetPos;//見えてる間は
    hasLastKnownPos = true;
    MoveToward(targetPos);
    return NodeResult::SUCCESS;
}

bool Normal::CanChase()
{
    if (!target) return false;
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= sensedRange * sensedRange)return true;
    else return false;
}

NodeResult Normal::Patrol()
{
    state = State::PATROL;
    return NodeResult::SUCCESS;
}

NodeResult Normal::Search()
{
    state = State::SEARCH;
    MoveToward(lastKnownPos);
    return NodeResult::SUCCESS;
}

bool Normal::CanSearch()
{
    if (!hasLastKnownPos) return false;
    const float arriveThresholdSq = 10.0f * 10.0f;//到着判定の誤差
    float lengthSq = Math2D::LengthSq(lastKnownPos - position);
    if (lengthSq <= arriveThresholdSq)
    {
        hasLastKnownPos = false;//到着したので索敵終了→次(StageAttack/Patrol)へ
        return false;
    }
    return true;
}

NodeResult Normal::StageAttack()
{
    state = State::STAGE_ATTACK;
    Vector2 stagePos = stageTarget->GetPos();
    float lengthSq = Math2D::LengthSq(stagePos - position);
    //攻撃範囲外なら近づく
    if (lengthSq > attackRadius * attackRadius)
    {
        MoveToward(stagePos);
        return NodeResult::SUCCESS;
    }
    //範囲内だがクールタイム中は何もしない
    if (coolTime > 0.0f) return NodeResult::SUCCESS;
    //攻撃
    coolTime = coolTimeMax;
    Collider col;
    Vector2 zero(0, 0);
    col.SetCapsule(zero, zero, radius, Layer::ENEMY_ATTACK, (uint32_t)Layer::STAGE);
    CollidManager::CollisionRequest(this, col, Tag::STAGE);
    return NodeResult::SUCCESS;
}

bool Normal::CanStageAttack()
{
    return stageTarget != nullptr;
}