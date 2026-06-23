#include "Enemy.h"

float Enemy::SPEED;
float Enemy::RADIUS;

Enemy::Enemy(Vector2 pos)
	:Character(Tag::ENEMY)
{
	position = pos;
	radius = RADIUS;
	char path[50] = "Assets/Enemy/Enemy.mv1";
	hModel = MV1LoadModel(path);
	assert(hModel > 0);

	uint32_t mask = (uint32_t)Layer::PLAYER_ATTACK | (uint32_t)Layer::PLAYER;
	SetCenterCircle(Layer::ENEMY, mask);
}

Enemy::~Enemy()
{}

void Enemy::Update()
{
	Move();
	CheckOutRange();
}

void Enemy::Draw()
{
	float x = position.x;
	float y = position.y;
	DrawCircle(x, y, radius, COL_MAGENTA, TRUE);

	Convert2Dto3D();
	DrawModel();
}

void Enemy::OnCollision(GameObject * other)
{
	if (other->GetTag() == Tag::ATTACK)
	{
		DestroyMe();
	}
}

void Enemy::Move()
{}

void Enemy::CheckOutRange()
{
	if (position.x <= -radius * 2)DestroyMe();
	else if (position.x >= WIN_WIDTH + radius * 2)DestroyMe();
	else if (position.y <= -radius * 2)DestroyMe();
	else if (position.y >= WIN_HEIGHT + radius * 2)DestroyMe();
}
