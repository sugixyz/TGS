#include "Weapon3.h"
#include"Player.h"
#include"Slash.h"
#include"../Engine/Collid/CollidManager.h"

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
	continuousNumber = CONTINUOUS_NUMBER;
	coolTime = COOL_TIME;
	attackRadius = ATTACK_RADIUS;
	isEnhanced = false;
	attackCount = 0;
	
	target = nullptr;
}

Weapon3::~Weapon3()
{}

void Weapon3::Update()
{
	coolTime -= Time::GetDeltaTime();
	if (coolTime < 0.0f)coolTime = 0.0f;

	target = nullptr;
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
			DrawCircle((int)position.x, (int)position.y, ATTACK_RADIUS, COL_RED, TRUE);
		}
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Weapon3::Attack(Player * owner)
{
	SearchTarget();
	if (target != nullptr && owner->IsEndMoveLerp())
	{
		if (Input::IsPadDown(Pad::A, owner->GetId()) ||
			Input::IsKeepPadDown(Pad::A, owner->GetId()))
		{
			if (coolTime <= 0.0f)
			{
				new Slash(target->GetPos(), 1);

				Vector2 move = Math2D::Normalize(target->GetPos() - owner->GetPos());
				owner->SetDir(move);

				move *= MOVE_DISTANCE;

				//プレイヤーを攻撃に合わせて移動
				owner->MoveAttack(move, MOVE_TIME);
				life--;
				if (life <= 0)
				{
					owner->BrokenHasWeapon();
				}

				attackCount++;
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
}

void Weapon3::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
{
	if (other->GetTag() == Tag::ENEMY)
	{
		if (CheckDuringStage(other))return;

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

void Weapon3::EnhanceWeapon()
{
	isEnhanced = true;
	life = ENHANCE_SWORD_NUMBER;
	continuousNumber = ENHANCE_CONTINUOUS_NUMBER;
}

void Weapon3::SearchTarget()
{
	Collider col;
	Vector2 start = Vector2();
	Vector2 end = start;
	uint32_t mask = (uint32_t)Layer::ENEMY;
	col.SetCapsule(start, end, ATTACK_RADIUS, Layer::PLAYER_ATTACK, mask);
	CollidManager::CollisionRequest(this, col, Tag::ENEMY);
}

bool Weapon3::CheckDuringStage(GameObject* enemy)
{
	Collider col;
	Vector2 start = Vector2();
	Vector2 end = start + (enemy->GetPos() - this->GetPos());
	col.SetCapsule(start, end, 0, Layer::PLAYER_ATTACK, (uint32_t)Layer::STAGE);
	return CollidManager::CollisionCheckRequest(this, col, Tag::STAGE);
}
