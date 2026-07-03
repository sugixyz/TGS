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
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x;
		float y = position.y;
		DrawCircle((int)x, (int)y, (int)radius, COL_BLACK, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Bullet::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	//何かに当たったら消える
	DestroyMe();

	if (other->GetTag() == Tag::ENEMY)other->DestroyMe();
}

void Bullet::Move()
{
	position += velocity;
}
