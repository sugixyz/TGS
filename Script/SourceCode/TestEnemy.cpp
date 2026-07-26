#include "TestEnemy.h"

TestEnemy::TestEnemy(Vector2 pos)
    :Enemy(Tag::ENEMY)
{
    auto attackNode = new ActionNode<TestEnemy>(this, &TestEnemy::AttackAction);
    auto attackCheckNode = new ConditionNode<TestEnemy>(this, &TestEnemy::CanAttack);
    Sequence* attack = new Sequence();
    attack->AddChildren(attackCheckNode);
    attack->AddChildren(attackNode);

    auto chaseNode = new ActionNode<TestEnemy>(this, &TestEnemy::Chase);
    auto chaseCheckNode = new ConditionNode<TestEnemy>(this, &TestEnemy::CanChase);
    Sequence* chase = new Sequence();
    chase->AddChildren(chaseCheckNode);
    chase->AddChildren(chaseNode);

    auto patrolNode = new ActionNode<TestEnemy>(this, &TestEnemy::Patrol);

    root.AddChildren(attack);
    root.AddChildren(chase);
    root.AddChildren(patrolNode);

    position = pos;
    hp = 1;
    radius = 25;
    target = FindTagObject(Tag::PLAYER);
    state = State::PATROL;
}

TestEnemy::~TestEnemy()
{}

void TestEnemy::Update()
{
    root.Tick();
}

void TestEnemy::Draw()
{
    if (mode == DEBUG || mode == DOUBLE_MODE)
    {
        float x = position.x;
        float y = position.y;

        DrawCircle((int)x, (int)y, (int)radius, COL_GREEN, TRUE);
        DrawStateText();
    }
    if (mode == NORMAL || mode == DOUBLE_MODE)
    {
        Convert2Dto3D();
        DrawModel();
    }
}

NodeResult TestEnemy::AttackAction()
{
    state = State::ATTACK;
    return NodeResult::SUCCESS;
}

bool TestEnemy::CanAttack()
{
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= 50 * 50)return true;
    else return false;
}

NodeResult TestEnemy::Chase()
{
    state = State::CHASE;
    Vector2 targetPos = target->GetPos();
    direction = Math2D::Normalize(targetPos - position);
    position += direction * 20 * gDeltaTime;
    return NodeResult::SUCCESS;
}

bool TestEnemy::CanChase()
{
    Vector2 targetPos = target->GetPos();
    float lenghtSq = Math2D::LengthSq(targetPos - position);
    if (lenghtSq <= 300 * 300)return true;
    else return false;
}

NodeResult TestEnemy::Patrol()
{
    state = State::PATROL;
    return NodeResult::SUCCESS;
}

void TestEnemy::DrawStateText()
{
    switch (state)
    {
    case State::ATTACK:
        DrawString(100, 300, "ATTACK", 0xffff00);
        break;
    case State::CHASE:
        DrawString(100, 300, "CHASE", 0xffff00);
        break;
    default:
        DrawString(100, 300, "PATROL", 0xffff00);
        break;
    }
}
