#include "NormalZombie.h"

int NormalZombie::MAX_HP;
float NormalZombie::SPEED;
float NormalZombie::RADIUS;
float NormalZombie::ATTACK_RADIUS;
float NormalZombie::SENSED_RANGE;
float NormalZombie::COOL_TIME;
float NormalZombie::DROP_RATE;

NormalZombie::NormalZombie(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	position = pos;
	hp = MAX_HP;
	radius = RADIUS;

	state = NORMAL;

	Vector2 toDestination = DESTINATION - position;
	toDestination = Math2D::NormalZombieize(toDestination);
	direction = toDestination;

	hModel = MV1LoadModel("Assets/Enemy/Enemy.mv1");

	uint32_t mask = (uint32_t)Layer::STAGE | (uint32_t)Layer::PLAYER_ATTACK;
	SetCenterCircle(Layer::ENEMY, mask);
}

NormalZombie::~NormalZombie()
{
	MV1DeleteModel(hModel);
}

void NormalZombie::Update()
{
	Move();
	Attack();
}

void NormalZombie::Draw()
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

void NormalZombie::Move()
{
	if (state == ATTACK)return;
	position += direction * SPEED * gDeltaTime;
}

void NormalZombie::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
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
