#include "Normal.h"

void Normal::Update()
{
}

void Normal::Draw()
{
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