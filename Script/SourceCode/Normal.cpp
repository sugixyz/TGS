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

	auto patrolNode = new ActionNode<Normal>(this, &Normal::Patrol);

	root.AddChildren(attack);
	root.AddChildren(chase);
	root.AddChildren(patrolNode);

	hModel = Model::Load("Enemy.mv1");
	assert(hModel > 0);
}

Normal::~Normal()
{
}

void Normal::Update()
{
    root.Tick();
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
    Collider col;
    Vector2 zero(0, 0);
    col.SetCapsule(zero, zero, radius, Layer::ENEMY_ATTACK, (uint32_t)Layer::PLAYER);
    CollidManager::CollisionRequest(this, col, Tag::PLAYER);
    return NodeResult::SUCCESS;
}

bool Normal::CanAttack()
{
    if (!target) return false;
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= 50 * 50)return true;
    else return false;
}

NodeResult Normal::Chase()
{
    state = State::CHASE;
    Vector2 targetPos = target->GetPos();
    direction = Math2D::Normalize(targetPos - position);
    position += direction * speed * gDeltaTime;
    return NodeResult::SUCCESS;
}

bool Normal::CanChase()
{
    return false;
}

NodeResult Normal::Patrol()
{
    return NodeResult();
}
