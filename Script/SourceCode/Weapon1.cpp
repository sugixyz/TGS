#include "Weapon1.h"
#include"Player.h"
#include"Bullet.h"

int Weapon1::BULLET_NUMBER;
float Weapon1::BULLET_SPEED;
float Weapon1::ATTACK_RADIUS;

Weapon1::Weapon1()
	:Weapon(Tag::ITEM)
{
	type = ItemType::WEAPON1;
	life = BULLET_NUMBER;
	BULLET_SPEED *= gDeltaTime;
}

Weapon1::~Weapon1()
{}

void Weapon1::Draw()
{
	float sizeHalf = 10;
	Vector2 p1 = Vector2(position.x - sizeHalf, position.y - sizeHalf);
	Vector2 p2 = Vector2(position.x + sizeHalf, position.y + sizeHalf);

	DrawBox(p1.x, p1.y, p2.x, p2.y, COL_RED, TRUE);
	
	if (isAttack)
	{
		Vector2 start = position;
		Vector2 end = start + direction * Math2D::Length(Vector2(WIN_WIDTH, WIN_HEIGHT));
		DrawLine(start.x, start.y, end.x, end.y, COL_RED, ATTACK_RADIUS);
	}
}

void Weapon1::Attack(Player* owner)
{
	//スティックの方向を取得
	Vector2 stick = Input::GetStick(owner->GetId());
	if (stick != Vector2(0, 0))
	{
		owner->SetDir(Math2D::Normalize(stick));
		owner->ItemMove();
	}
	SetDir(owner->GetDir());

	//攻撃
	if (Input::IsPadDown(Pad::A, owner->GetId()))
	{
		//弾を生成
		new Bullet(position, direction * BULLET_SPEED, ATTACK_RADIUS);
		life--;
		if (life <= 0)
		{
			owner->BrokenHasWeapon();
		}
	}
}

void Weapon1::EnhanceWeapon()
{
	//ToDo : ここで武器強化（パラメータを上昇させる）
}
