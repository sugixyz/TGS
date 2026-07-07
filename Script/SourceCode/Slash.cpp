#include "Slash.h"
#include"../Engine/Collid/CollidManager.h"

Slash::Slash(Vector2 pos,float rad)
	:Attack(Tag::ATTACK)
{
	position = pos;
	radius = rad;
}

Slash::~Slash()
{}

void Slash::Update()
{
	Collider col;
	Vector2 start = Vector2();
	Vector2 end = start;
	col.SetCapsule(start, end, radius, Layer::PLAYER_ATTACK, (uint32_t)Layer::ENEMY);
	CollidManager::CollisionRequest(this, col, Tag::ENEMY);
	DestroyMe();
}

void Slash::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		DrawCircle((int)position.x, (int)position.y, (int)radius, COL_RED, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Slash::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	DestroyMe();
}
