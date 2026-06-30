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
}

Weapon3::~Weapon3()
{}

void Weapon3::Update()
{
	//攻撃中じゃないならコライダーをリセット
	if (!isAttack)myColliders.clear();
}

void Weapon3::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float sizeHalf = 10;
		Vector2 p1 = Vector2(position.x - sizeHalf, position.y - sizeHalf);
		Vector2 p2 = Vector2(position.x + sizeHalf, position.y + sizeHalf);

		DrawBoxAA(p1.x, p1.y, p2.x, p2.y, COL_BLUE, TRUE);

		if (isAttack)
		{
			float x = position.x;
			float y = position.y;
			DrawCircle((int)x, (int)y, (int)ATTACK_RADIUS, COL_RED, TRUE);
			Vector2 move = position + direction * MOVE_DISTANCE;
			x = move.x;
			y = move.y;
			DrawCircle((int)x, (int)y, (int)ATTACK_RADIUS, COL_RED, TRUE);
			Vector2 p1 = position;
			Vector2 p2 = move;
			DrawLineAA(p1.x, p1.y, p2.x, p2.y, COL_RED, ATTACK_RADIUS * 2);
		}
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Weapon3::Attack(Player * owner)
{
	if (myColliders.size() == 0)
	{
		uint32_t mask = (uint32_t)Layer::ENEMY;
		SetCenterCircle(ATTACK_RADIUS, Layer::PLAYER_ATTACK, mask);
	}

	//攻撃
	if (Input::IsPadDown(Pad::A, owner->GetId()))
	{
		//移動ベクトル
		Vector2 move = owner->GetDir() * MOVE_DISTANCE;
		//プレイヤーを攻撃に合わせて移動
		owner->MoveAttack(move, MOVE_TIME);
		//斬撃の生成
		new Slash(owner,position - owner->GetPos(), ATTACK_RADIUS, MOVE_TIME);
		life--;
		if (life <= 0)
		{
			owner->BrokenHasWeapon();
		}
	}

	owner->ItemMove();
}

void Weapon3::EnhanceWeapon()
{}
