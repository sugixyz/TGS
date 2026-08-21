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

    uint32_t mask = (uint32_t)Layer::PLAYER_ATTACK;
    SetCenterCircle(Layer::ENEMY, mask);
    uint32_t senseMask = (uint32_t)Layer::PLAYER;
    GameObject::SetCenterCircle(sensedRange, Layer::ENEMY_SENSE, senseMask);
    uint32_t attackSenseMask = (uint32_t)Layer::PLAYER;
    GameObject::SetCenterCircle(attackRadius, Layer::ENEMY_ATTACK_SENSE, attackSenseMask);

	hModel = Model::Load("Enemy.mv1");
	assert(hModel > 0);
}

Normal::~Normal()
{
    int a;
}

void Normal::Update()
{
    if (coolTime > 0.0f)
    {
        coolTime -= gDeltaTime;
    }

    root.Tick();
    CheckOutRange();

    //今フレームの判定結果はここでリセット(この直後CollidManagerが今フレーム分をセットし直す)
    isPlayerSensed = false;
    isPlayerInAttackRange = false;
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
    /*Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= attackRadius * attackRadius)return true;
    else return false;*/
    return isPlayerInAttackRange;
}

NodeResult Normal::Chase()
{
    state = State::CHASE;
    Vector2 targetPos = target->GetPos();
    MoveToward(targetPos);
    return NodeResult::SUCCESS;
}

bool Normal::CanChase()
{
    /*if (!target) return false;
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= sensedRange * sensedRange)return true;
    else return false;*/
    if (!target) return false;
    //if (coolTime > 0.0f) return false;
    return isPlayerSensed;
}

NodeResult Normal::Patrol()
{
    state = State::PATROL;
    return NodeResult::SUCCESS;
}

NodeResult Normal::Search()
{
    state = State::SEARCH;
    Vector2 stagePos = stageTarget->GetPos();
    MoveToward(stagePos);//拠点へ直接移動
    return NodeResult::SUCCESS;
}

bool Normal::CanSearch()
{
    if (!stageTarget) return false;
    Vector2 stagePos = stageTarget->GetPos();
    float lengthSq = Math2D::LengthSq(stagePos - position);
    if (lengthSq <= attackRadius * attackRadius) return false;//すでに攻撃範囲内StageAttackへ
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

void Normal::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
{
    Enemy::OnCollision(myLayer, other, otherLayer);//被弾処理は基底クラスに任せる
    if (other->GetTag() == Tag::PLAYER)
    {
        if (myLayer == Layer::ENEMY_SENSE)
        {
            isPlayerSensed = true;
        }
        else if (myLayer == Layer::ENEMY_ATTACK_SENSE)
        {
            isPlayerInAttackRange = true;
        }
    }
}