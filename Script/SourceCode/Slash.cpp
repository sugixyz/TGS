#include "Slash.h"

Slash::Slash(Vector2 pos,float rad)
	:Attack(Tag::ATTACK)
{
	position = pos;
	radius = rad;

	uint32_t mask = (uint32_t)Layer::ENEMY | (uint32_t)Layer::STAGE;
	SetCenterCircle(Layer::PLAYER_ATTACK, mask);
}

Slash::~Slash()
{}

void Slash::Update()
{
	dethTimer.Update();
	if (dethTimer.isExpired(time))
	{
		DestroyMe();
	}
}

void Slash::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		DrawCircle((int)position.x, (int)position.y, (int)radius, COL_BLACK, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Slash::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	if (other->GetTag() == Tag::ENEMY)
	{
		if (target == nullptr)
		{
			target = other;
			return;
		}

		//今インタラクト中のギミックとの距離を計算
		float iLenghtSq = Math2D::LengthSq(position - target->GetPos());
		float gLenghtSq = Math2D::LengthSq(position - other->GetPos());

		//距離が近いほうをインタラクトギミックとして保存
		if (iLenghtSq > gLenghtSq)target = other;
	}
}

