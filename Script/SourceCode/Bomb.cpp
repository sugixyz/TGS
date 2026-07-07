#include "Bomb.h"
#include"../Engine/Collid/CollidManager.h"

Bomb::Bomb(Vector2 start, Vector2 end, float rad,float time)
	:Attack(Tag::ATTACK)
{
	radius = rad;
	moveLerp.Start(start, end, time, [this](Vector2 pos) {SetPos(pos); });
}

Bomb::~Bomb()
{}

void Bomb::Update()
{
	Move();
	CheckOutRange();
}

void Bomb::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x;
		float y = position.y;
		DrawCircle((int)x, (int)y, (int)15, COL_BLACK, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Bomb::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
}

void Bomb::Move()
{
	moveLerp.Update();
	//移動が終了したら（ラープが終了していれば）判定生成
	if (not moveLerp.IsActive())
	{
		Collider col;
		Vector2 start = Vector2();
		Vector2 end = start;
		col.SetCapsule(start, end, radius, Layer::PLAYER_ATTACK, (uint32_t)Layer::ENEMY);
		CollidManager::CollisionRequest(this, col, Tag::ENEMY);
		DestroyMe();
	}
}