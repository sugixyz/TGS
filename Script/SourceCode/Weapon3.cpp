#include "Weapon3.h"
#include"Player.h"
#include"Slash.h"

int Weapon3::SWORD_NUMBER;
int Weapon3::CONTINUOUS_NUMBER;
float Weapon3::ATTACK_RADIUS;
float Weapon3::MOVE_DISTANCE;
float Weapon3::MOVE_TIME;
float Weapon3::COOL_TIME;
int Weapon3::ENHANCE_SWORD_NUMBER;
int Weapon3::ENHANCE_CONTINUOUS_NUMBER;
float Weapon3::ENHANCE_COOL_TIME;

Weapon3::Weapon3()
	:Weapon(Tag::ITEM)
{
	type = ItemType::WEAPON3;
	life = SWORD_NUMBER;
	slash = nullptr;
	continuousNumber = CONTINUOUS_NUMBER;
	attackCount = 0;
	coolTime = COOL_TIME;
	attackRadius = ATTACK_RADIUS;
	isEnhanced = false;
}

Weapon3::~Weapon3()
{}

void Weapon3::Update()
{
	coolTime -= Time::GetDeltaTime();
	if (coolTime < 0.0f)coolTime = 0.0f;

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
	if (not isAttack)slash = new Slash(owner->GetPos(), attackRadius);

	//攻撃
	if (Input::IsPadDown(Pad::A, owner->GetId()) ||
		Input::IsKeepPadDown(Pad::A, owner->GetId()))
	{
		if (coolTime <= 0.0f)
		{
			if (slash->GetTarget() != nullptr)
			{
				slash->GetTarget()->DestroyMe();
				attackCount++;

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

				if (attackCount >= continuousNumber)
				{
					if (isEnhanced)coolTime = ENHANCE_COOL_TIME;
					else coolTime = COOL_TIME;

					attackCount = 0;
				}
			}
		}
	}

	owner->ItemMove();
	slash->SetPos(owner->GetPos());
}

void Weapon3::EnhanceWeapon()
{
	isEnhanced = true;
	life = ENHANCE_SWORD_NUMBER;
	continuousNumber = ENHANCE_CONTINUOUS_NUMBER;
}
