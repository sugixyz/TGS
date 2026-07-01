#include "Normal.h"

int Normal::MAX_HP;
float Normal::SPEED;
float Normal::RADIUS;
float Normal::ATTACK_RADIUS;
float Normal::SENSED_RANGE;
float Normal::ATTACK_INTERVAL;

Normal::Normal(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	position = pos;
	hp = MAX_HP;
	radius = RADIUS;
	radius = 25;

	direction = Math2D::DOWN;
	hModel = MV1LoadModel("Assets/Enemy/Enemy.mv1");

	uint32_t mask = (uint32_t)Layer::PLAYER_ATTACK | (uint32_t)Layer::PLAYER;
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
}

void Normal::OnCollision(Layer myLayer, GameObject* other, Layer otherLayer)
{
}
