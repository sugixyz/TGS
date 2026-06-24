#include "Base.h"
#include"../Engine/Tool/ParamLoader.h"

Base::Base(Vector2 pos, int blockSize)
	:GameObject(Tag::STAGE)
{
	position = pos;

	uint32_t mask = (uint32_t)Layer::PLAYER | (uint32_t)Layer::PLAYER_ATTACK | (uint32_t)Layer::ENEMY_ATTACK;
	SetCenterBox(blockSize / 2.0f, Layer::STAGE, mask);
}

Base::~Base()
{}

void Base::OnCollision(GameObject * other)
{
	if (other->GetTag() == Tag::ATTACK)
	{
	}
}
