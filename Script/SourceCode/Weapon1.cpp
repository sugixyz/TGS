#include "Weapon1.h"
#include"Player.h"
#include"Bullet.h"

int Weapon1::BULLET_NUMBER;
float Weapon1::BULLET_SPEED;
float Weapon1::ATTACK_RADIUS;
float Weapon1::COOL_TIME;
int Weapon1::ENHANCE_BULLET_NUMBER;
float Weapon1::ENHANCE_COOL_TIME;

Weapon1::Weapon1()
	:Weapon(Tag::ITEM)
{
	type = ItemType::WEAPON1;
	life = BULLET_NUMBER;
	coolTime = COOL_TIME;
	attackRadius = ATTACK_RADIUS;
	isEnhanced = false;
}

Weapon1::~Weapon1()
{}

void Weapon1::Update()
{
	coolTime -= Time::GetDeltaTime();
	if (coolTime < 0.0f)coolTime = 0.0f;
}

void Weapon1::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float sizeHalf = 10;
		Vector2 p1 = Vector2(position.x - sizeHalf, position.y - sizeHalf);
		Vector2 p2 = Vector2(position.x + sizeHalf, position.y + sizeHalf);

		DrawBoxAA(p1.x, p1.y, p2.x, p2.y, COL_RED, TRUE);

		if (isAttack)
		{
			Vector2 start = position;
			Vector2 end = start + direction * Math2D::Length(Vector2(WIN_WIDTH, WIN_HEIGHT));
			DrawLineAA(start.x, start.y, end.x, end.y, COL_RED, attackRadius);
		}
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

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
	if (Input::IsPadDown(Pad::A, owner->GetId()) || 
		Input::IsKeepPadDown(Pad::A, owner->GetId()))
	{
		if (coolTime > 0.0f)return;
		//弾を生成
		new Bullet(position, direction * BULLET_SPEED * gDeltaTime, attackRadius);
		life--;
		if (life <= 0)
		{
			owner->BrokenHasWeapon();
		}

		if (isEnhanced)coolTime = ENHANCE_COOL_TIME;
		else coolTime = COOL_TIME;
	}
}

void Weapon1::EnhanceWeapon()
{
	isEnhanced = true;
	life = ENHANCE_BULLET_NUMBER;
}
