#pragma once
#include "Attack.h"

class Arrow : public Attack
{
public:
	Arrow(Vector2 startPos, Vector2 targetPos, float flightTime, Tag targetTag);
	~Arrow();
	void Update() override;
	void Draw() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
private:
	Vector2 startPos_;
	Vector2 targetPos_;
	float flightTime_;
	float elapsed_ = 0.0f;
	float arcHeight_ = 80.0f;//弧の頂点の高さ(仮、モデル用)
	float height_ = 0.0f;//現在の高さ(将来的にDraw/Convert2Dto3Dで使う)
	Tag targetTag_;//狙ってる対象のタグ(Tag::PLAYER or Tag::STAGE)
};