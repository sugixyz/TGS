#include "Normal.h"

int Normal::MAX_HP;
float Normal::SPEED;
float Normal::RADIUS;
float Normal::ATTACK_RADIUS;
float Normal::SENSED_RANGE;
float Normal::COOL_TIME;
float Normal::DROP_RATE;

Normal::Normal(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	position = pos;
	hp = MAX_HP;
	radius = RADIUS;

	state = NORMAL;

	Vector2 toDestination = DESTINATION - position;
	toDestination = Math2D::Normalize(toDestination);
	direction = toDestination;

	hModel = MV1LoadModel("Assets/Enemy/Enemy.mv1");

	uint32_t mask = (uint32_t)Layer::STAGE | (uint32_t)Layer::PLAYER_ATTACK;
	SetCenterCircle(Layer::ENEMY, mask);
}

Normal::~Normal()
{
	MV1DeleteModel(hModel);
}

void Normal::Update()
{
	Move();
	Attack();
}

void Normal::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x;
		float y = position.y;

		DrawCircle((int)x, (int)y, (int)radius, COL_GREEN, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

void Normal::Move()
{
	if (state == ATTACK)return;
	position += direction * SPEED * gDeltaTime;
}

void Normal::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
{
	if (other->GetTag() == Tag::STAGE)
	{
		state = ATTACK;
	}
	else if (other->GetTag() == Tag::PLAYER)
	{

	}
	else if (other->GetTag() == Tag::ATTACK)
	{
		hp--;
		if (hp <= 0)DestroyMe();
	}
}
