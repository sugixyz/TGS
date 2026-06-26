#include "Player.h"
#include"../Engine/Tool/ParamLoader.h"
#include"Weapon.h"
#include"Gimmick.h"

int Player::MAX_HP;
float Player::SPEED;
Vector2 Player::SPAWN_POS[2];
float Player::RADIUS;
float Player::ITEM_OFFSET;

Player::Player(int index)
	:Character(Tag::PLAYER)
{
	id = index;
	position = SPAWN_POS[id];
	hp = MAX_HP;
	radius = RADIUS;
	direction = Math2D::UP;

	char path[50];
	sprintf_s(path, sizeof(path), "Assets/Player/Player%02d.mv1", id + 1);
	hModel = MV1LoadModel(path);
	assert(hModel > 0);

	uint32_t mask = (uint32_t)Layer::STAGE |
		(uint32_t)Layer::GIMMICK |
		(uint32_t)Layer::ENEMY |
		(uint32_t)Layer::ENEMY_ATTACK;
	SetCenterCircle(Layer::PLAYER, mask);
}

Player::~Player()
{}

void Player::Update()
{
	moveLerp.Update();

	if (Attack())return;
	Move();
	Interact();
}

void Player::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x;
		float y = position.y;

		DrawCircle((int)x, (int)y, (int)radius, COL_WHITE, TRUE);

		Vector2 dirPos = { x + direction.x * radius,y + direction.y * radius };
		DrawLineAA(x, y, dirPos.x, dirPos.y, COL_RED);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

void Player::Move()
{
	//スティックの方向を取得	
	Vector2 stick = Input::GetStick(id);
	if (stick != Vector2(0, 0))
	{
		//スティックの方向に速度分の移動ベクトルを設定
		direction = Math2D::Normalize(stick);
		if (Math2D::Length(stick) >= 0.5f)
		{
			velocity = direction * SPEED * gDeltaTime;
		}
	}
	else
	{
		velocity = { 0,0 };
	}

	position += velocity;
	ItemMove();
}

void Player::OnCollision(GameObject * other)
{
	if (other->GetTag() == Tag::STAGE)
	{
		CollisionWall(other);
	}
	if (other->GetTag() == Tag::GIMMICK)
	{
		CollisionGimmick(other);
	}
}

void Player::ItemMove()
{
	if (hasItem != nullptr)
	{
		hasItem->SetPos(Vector2(position + direction * ITEM_OFFSET));
	}
}

void Player::BrokenHasWeapon()
{
	//持っている武器を破棄、破壊
	hasItem->DestroyMe();
	hasItem = nullptr;
}

void Player::MoveAttack(Vector2 move,float sec)
{
	moveLerp.Start(position, position + move, sec, [this](Vector2 pos) {SetPos(pos);});
}

void Player::CollisionWall(GameObject* wall)
{
	Collider wallCol = wall->GetCollider();
	Vector2 wPos = wall->GetPos();
	//壁の高さ、幅
	float wallW = wallCol.bPosB.x - wallCol.bPosA.x;
	float wallH = wallCol.bPosB.y - wallCol.bPosA.y;

	float overlapX = (this->radius + wallW / 2.0f) - abs(this->position.x - wPos.x);
	float overlapY = (this->radius + wallH / 2.0f) - abs(this->position.y - wPos.y);

	//当たったのが左右の壁なら
	if (overlapX < overlapY)
	{
		//壁が右にあるなら
		if (this->position.x < wPos.x)
		{
			this->position.x -= overlapX;
		}
		//壁が左にあるなら
		else
		{
			this->position.x += overlapX;
		}
	}
	//当たったのが上下の壁なら
	else
	{
		//壁が上にあるなら
		if (this->position.y < wPos.y)
		{
			this->position.y -= overlapY;
		}
		//壁が下にあるなら
		else
		{
			this->position.y += overlapY;
		}
	}

	moveLerp.Reset();
}

void Player::CollisionGimmick(GameObject* other)
{
	if (interactionGimmick == nullptr)
	{
		interactionGimmick = other;
		return;
	}

	//今インタラクト中のギミックとの距離を計算
	float iLenghtSq = Math2D::LengthSq(position - interactionGimmick->GetPos());
	float gLenghtSq = Math2D::LengthSq(position - other->GetPos());

	//距離が近いほうをインタラクトギミックとして保存
	if (iLenghtSq > gLenghtSq)interactionGimmick = other;
}

void Player::Interact()
{
	if (Input::IsPadDown(Pad::A, id))
	{
		//もし適応可能なギミックがなければスルー
		if (interactionGimmick == nullptr)return;

		Gimmick* g = dynamic_cast<Gimmick*>(interactionGimmick);
		hasItem = g->Interact(hasItem);
	}
	//毎フレーム初期化
	interactionGimmick = nullptr;
}

bool Player::Attack()
{
	//何も持っていないならスルー
	if (hasItem == nullptr)return false;

	Weapon* wpn = dynamic_cast<Weapon*>(hasItem);
	//もし持っているアイテムが武器じゃないならスルー
	if (wpn == nullptr)return false;

	//RBを押していれば攻撃
	if (Input::IsKeepPadDown(Pad::RB, id))
	{
		wpn->Attack(this);
		wpn->IsAttack(true);
		return true;
	}
	wpn->IsAttack(false);
	return false;
}
