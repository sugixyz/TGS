#include "Weapon2.h"
#include"Player.h"
#include"Bomb.h"

int Weapon2::BOMB_NUMBER;
float Weapon2::ATTACK_RANGE;
float Weapon2::ATTACK_RADIUS;
float Weapon2::FALL_TIME;
float Weapon2::AIM_SPEED;

Weapon2::Weapon2()
	:Weapon(Tag::ITEM)
{
	type = ItemType::WEAPON2;
	life = BOMB_NUMBER;
}

Weapon2::~Weapon2()
{}

void Weapon2::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float sizeHalf = 10;
		Vector2 p1 = Vector2(position.x - sizeHalf, position.y - sizeHalf);
		Vector2 p2 = Vector2(position.x + sizeHalf, position.y + sizeHalf);

		DrawBox(p1.x, p1.y, p2.x, p2.y, COL_GREEN, TRUE);

		if (isAttack)
		{
			float x = attackPos.x;
			float y = attackPos.y;
			DrawCircle(x, y, ATTACK_RADIUS, COL_RED, TRUE);
		}
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Weapon2::Attack(Player * owner)
{
	//最初に攻撃位置を初期化
	if (!isAttack)
	{
		range = ATTACK_RANGE / 2;
		attackPos = position + owner->GetDir() * range;
	}

	Vector2 stick = Input::GetStick(owner->GetId());
	if (stick != Vector2(0, 0))
	{
		//スティックの方向に攻撃位置を変化させる
		attackPos += Math2D::Normalize(stick) * AIM_SPEED * gDeltaTime;
		range = Math2D::Length(attackPos - position);
		Vector2 dir = Math2D::Normalize(attackPos - position);
		if (range > ATTACK_RANGE)
		{
			range = ATTACK_RANGE;
			attackPos = position + dir * range;
		}
		owner->SetDir(dir);
		owner->ItemMove();
	}
	SetDir(owner->GetDir());

	if (Input::IsPadDown(Pad::A, owner->GetId()))
	{
		//爆弾を生成
		new Bomb(position, attackPos, ATTACK_RADIUS, FALL_TIME);
		life--;
		if (life <= 0)
		{
			owner->BrokenHasWeapon();
		}
	}
}

void Weapon2::EnhanceWeapon()
{}
