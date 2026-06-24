#include "Bomb.h"

Bomb::Bomb(Vector2 start, Vector2 end, float rad,float time)
	:Attack(Tag::ATTACK)
{
	radius = rad;
	moveLerp.Start(start, end, time, [this](Vector2 pos) {SetPos(pos); });
}

Bomb::~Bomb()
{}

void Bomb::Update()
{
	coroutine.Update();
	Move();
	CheckOutRange();
}

void Bomb::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x;
		float y = position.y;
		DrawCircleAA(x, y, 15, COL_BLACK, TRUE);
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{

	}
}

void Bomb::Move()
{
	moveLerp.Update();
	//移動が終了したら（ラープが終了していれば）判定生成
	if (not moveLerp.IsActive())
	{
		uint32_t mask = (uint32_t)Layer::ENEMY;
		SetCenterCircle(Layer::PLAYER_ATTACK, mask);
		//1フレーム後に削除
		coroutine.Start([this] {IEDestroy(); });
	}
}

void Bomb::IEDestroy()
{
	DestroyMe();
}
