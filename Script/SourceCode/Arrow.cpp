#include "Arrow.h"

Arrow::Arrow(Vector2 startPos, Vector2 targetPos, float flightTime)
	:Attack(Tag::ENEMY_ATTACK)
{
	startPos_ = startPos;
	targetPos_ = targetPos;
	flightTime_ = flightTime;
	position = startPos_;
	radius = 8.0f;

	uint32_t mask = (uint32_t)Layer::PLAYER | (uint32_t)Layer::STAGE;
	SetCenterCircle(Layer::ENEMY_ATTACK, mask);
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	elapsed_ += gDeltaTime;
	if (elapsed_ >= flightTime_)
	{
		DestroyMe();
		return;
	}

	float t = elapsed_ / flightTime_;//0.0〜1.0

	//XY平面は直進(補間)
	position = startPos_ + (targetPos_ - startPos_) * t;

	//放物線の高さ(将来のZ描画用):t=0.5で最大arcHeight_、t=0/1で0
	height_ = 4.0f * arcHeight_ * t * (1.0f - t);
}

void Arrow::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		DrawCircle((int)position.x, (int)position.y, (int)radius, COL_YELLOW, TRUE);
		//height_をデバッグ表示したければここに追記
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		//モデル導入時:Convert2Dto3D()の後、position3.z += height_ 的な処理を追加予定
	}
}

void Arrow::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	DestroyMe();//何かに当たったら消える(Bulletと同じ挙動)
}