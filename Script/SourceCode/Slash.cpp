#include "Slash.h"

Slash::Slash(GameObject* pl,Vector2 move, float rad, float sec)
	:Attack(Tag::ATTACK)
{
	owner = pl;
	moveVec = move;
	position = owner->GetPos() + moveVec;
	radius = rad;
	time = sec;

	uint32_t mask = (uint32_t)Layer::ENEMY | (uint32_t)Layer::STAGE;
	SetCenterCircle(Layer::PLAYER_ATTACK, mask);
}

Slash::~Slash()
{}

void Slash::Update()
{
	dethTimer.Update();
	Move();
	if (dethTimer.isExpired(time))
	{
		DestroyMe();
	}
}

void Slash::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		DrawCircle(position.x, position.y, radius, COL_BLACK, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Slash::Move()
{
	//位置をプレイヤーの武器分前に移動
	position = owner->GetPos() + moveVec;
	//前フレーム時にいた場所も判定を取りたい場合有効化
	//myCollider.cPosB = moveVec * -1;
}

void Slash::OnCollision(GameObject* other)
{
	//当たった相手が壁なら消える
	if (other->GetTag() == Tag::STAGE)
	{
		DestroyMe();
	}
}

