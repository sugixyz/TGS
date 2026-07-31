#include "Normal.h"

void Normal::Initialize()
{
}

void Normal::Update()
{
}

void Normal::Draw()
{
}

void Normal::Move()
{
	Vector2 dir = DESTINATION - position;
	dir = Math2D::Normalize(dir);
	position += dir * speed_;
}

void Normal::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	if (other->GetTag() == Tag::STAGE)
	{
	}
	else if (other->GetTag() == Tag::PLAYER)
	{
	}
	else if (other->GetTag() == Tag::ATTACK)
	{
	}
}