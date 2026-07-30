#include "Archer.h"

void Archer::Initialize()
{
}

void Archer::Update()
{
}

void Archer::Draw()
{
}

void Archer::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
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