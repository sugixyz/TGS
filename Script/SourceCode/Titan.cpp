#include "Titan.h"

void Titan::Initialize()
{
}

void Titan::Update()
{
}

void Titan::Draw()
{
}

void Titan::Move()
{
}

void Titan::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
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