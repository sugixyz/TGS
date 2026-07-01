#include "Weapon3.h"
#include"Player.h"
#include"Slash.h"

int Weapon3::SWORD_NUMBER;
float Weapon3::ATTACK_RADIUS;
float Weapon3::MOVE_DISTANCE;
float Weapon3::MOVE_TIME;

Weapon3::Weapon3()
	:Weapon(Tag::ITEM)
{
	type = ItemType::WEAPON3;
	life = SWORD_NUMBER;
	slash = nullptr;
}

Weapon3::~Weapon3()
{}

void Weapon3::Update()
{
	if (not isAttack && slash != nullptr)
	{
		slash->DestroyMe();
		slash = nullptr;
	}
}

void Weapon3::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float sizeHalf = 10;
		Vector2 p1 = Vector2(position.x - sizeHalf, position.y - sizeHalf);
		Vector2 p2 = Vector2(position.x + sizeHalf, position.y + sizeHalf);

		DrawBoxAA(p1.x, p1.y, p2.x, p2.y, COL_BLUE, TRUE);
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Weapon3::Attack(Player * owner)
{
	if (not isAttack)slash = new Slash(owner->GetPos(), ATTACK_RADIUS);

	//攻撃
	if (Input::IsPadDown(Pad::A, owner->GetId()))
	{
		if (slash->GetTarget())
		{
			slash->GetTarget()->DestroyMe();

			Vector2 move = Math2D::Normalize(slash->GetTarget()->GetPos() - owner->GetPos());
			owner->SetDir(move);

			move *= MOVE_DISTANCE;

			//プレイヤーを攻撃に合わせて移動
			owner->MoveAttack(move, MOVE_TIME);
			life--;
			if (life <= 0)
			{
				owner->BrokenHasWeapon();
			}
		}
	}

	owner->ItemMove();
	slash->SetPos(owner->GetPos());
}

void Weapon3::EnhanceWeapon()
{}
