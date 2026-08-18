#include "TestEnemy.h"
#include"../Engine/Collid/CollidManager.h"
#include"../Engine/Tool/Model.h"

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
    state = TestState::PATROL;

    //char file[20];
    //sprintf_s(file, sizeof(file), "Enemy.fbx");
    hModel = Model::Load("Enemy.mv1");
    assert(hModel > 0);
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
        scale3 = { 0.01f,0.01f,0.01f };
        DrawModel();
    }
}

NodeResult TestEnemy::AttackAction()
{
    state = TestState::ATTACK;
    Collider col;
    Vector2 zero(0, 0);
    col.SetCapsule(zero, zero, radius, Layer::ENEMY_ATTACK, (uint32_t)Layer::PLAYER);
    CollidManager::CollisionRequest(this, col, Tag::PLAYER);
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
    state = TestState::CHASE;
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
    state = TestState::PATROL;
    return NodeResult::SUCCESS;
}

void TestEnemy::DrawStateText()
{
    switch (state)
    {
    case TestState::ATTACK:
        DrawString(100, 300, "ATTACK", 0xffff00);
        break;
    case TestState::CHASE:
        DrawString(100, 300, "CHASE", 0xffff00);
        break;
    default:
        DrawString(100, 300, "PATROL", 0xffff00);
        break;
    }
}
