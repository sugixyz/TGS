#include "Bullet.h"

Bullet::Bullet(Vector2 pos, Vector2 vel,float rad)
	:Attack(Tag::ATTACK)
{
	position = pos;
	velocity = vel;
	radius = rad;

	uint32_t mask = (uint32_t)Layer::ENEMY | (uint32_t)Layer::STAGE;
	SetCenterCircle(Layer::PLAYER_ATTACK, mask);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Move();
	CheckOutRange();
}

void Bullet::Draw()
{
	float x = position.x;
	float y = position.y;
	DrawCircle(x, y, radius, COL_BLACK, TRUE);
}

void Bullet::OnCollision(GameObject * other)
{
	//何かに当たったら消える
	DestroyMe();
}

void Bullet::Move()
{
	position += velocity;
}
