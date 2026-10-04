#include "Arrow.h"
#include "../Engine/Collid/CollidManager.h"

Arrow::Arrow(Vector2 startPos, Vector2 targetPos, float flightTime, Tag targetTag)
	:Attack(Tag::ENEMY_ATTACK)
{
	startPos_ = startPos;
	targetPos_ = targetPos;
	flightTime_ = flightTime;
	targetTag_ = targetTag;
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
		//到達時に明示的な判定を生成
		Collider col;
		Vector2 zero(0, 0);
		col.SetCapsule(zero, zero, radius, Layer::ENEMY_ATTACK,
			(uint32_t)Layer::PLAYER | (uint32_t)Layer::STAGE);
		CollidManager::CollisionRequest(this, col, targetTag_);//必要ならTag::STAGEも追加でリクエスト

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
		//Y座標からheight_分だけ引いて浮いてるように見せる(2D見下ろし想定、上に浮くほどYが小さくなる向きで調整してください)
		float drawY = position.y - height_;
		DrawCircle((int)position.x, (int)drawY, (int)radius, COL_YELLOW, TRUE);
		//height_をデバッグ表示したければここに追記
	}
	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		//モデル導入時:Convert2Dto3D()の後、position3.z += height_ 的な処理を追加予定
		//モデル導入後:position3.z += height_; のような形でDrawModel()前に高さを反映
		DrawModel();
	}
}

void Arrow::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	DestroyMe();//何かに当たったら消える(Bulletと同じ挙動)
}