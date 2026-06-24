#include "CollidManager.h"
#include"../Object/GameObject.h"
//#include"../Object/Character.h"
#include"../Tool/Math2D.h"
#include<algorithm>

namespace
{
	const unsigned int DEBUG_COL = GetColor(0, 255, 0);
}

void CollidManager::Update()
{
	//当たり判定を実行したいオブジェクト毎のリスト
	auto players = FindTagObjects(Tag::PLAYER);
	auto stages = FindTagObjects(Tag::STAGE);
	auto gimmicks = FindTagObjects(Tag::GIMMICK);
	auto attacks = FindTagObjects(Tag::ATTACK);
	auto enemys = FindTagObjects(Tag::ENEMY);

	//当たり判定
	//プレイヤーとステージ
	Collision(players, stages);
	//プレイヤーとギミック
	Collision(players, gimmicks);
	//プレイヤーとアタック
	Collision(players, attacks);
	//プレイヤーと敵
	Collision(players, enemys);
	//ステージとアタック
	Collision(stages, attacks);
	//敵とアタック
	Collision(enemys, attacks);
}

void CollidManager::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		//当たり判定を実行したいオブジェクト毎のリスト
		auto players = FindTagObjects(Tag::PLAYER);
		auto stages = FindTagObjects(Tag::STAGE);
		auto gimmicks = FindTagObjects(Tag::GIMMICK);
		auto attacks = FindTagObjects(Tag::ATTACK);
		auto enemys = FindTagObjects(Tag::ENEMY);

		for (auto p : players)DrawCollider(p);
		for (auto s : stages)DrawCollider(s);
		for (auto g : gimmicks)DrawCollider(g);
		for (auto a : attacks)DrawCollider(a);
		for (auto e : enemys)DrawCollider(e);
	}
}

void CollidManager::Collision(const std::vector<GameObject*> listA, const std::vector<GameObject*> listB)
{
	for (auto objA : listA)
	{
		//コライダーがなければスルー
		if (!objA->HasCollider() || objA->DestroyRequested())continue;
		Collider colA = objA->GetCollider();
		for (auto objB : listB)
		{
			//コライダーがなければスルー
			if (!objB->HasCollider() || objB->DestroyRequested())continue;
			Collider colB = objB->GetCollider();

			int pattern = CanHit(colA, colB);

			//相互の判定が不可能だったらスルー
			if (pattern == 0)continue;

			bool isHit = false;

			switch (pattern)
			{
			case 1:
				isHit = CheckCapsuleCollision(objA, objB);
				break;
			case 2:
				isHit = CheckBoxCollision(objA, objB);
				break;
			case 3:
				isHit = CheckCalsuleBoxCollision(objA, objB);
				break;
			case 4:
				isHit = CheckCalsuleBoxCollision(objB, objA);
				break;
			}

			if (isHit)
			{
				objA->OnCollision(objB);
				objB->OnCollision(objA);
			}
		}
	}
}

int CollidManager::CanHit(const Collider& colA, const Collider& colB)
{
	bool canAHitCap = colA.cLayerMask & static_cast<uint32_t>(colB.myLeyer);
	bool canBHitCap = colB.cLayerMask & static_cast<uint32_t>(colA.myLeyer);
	bool canAHitBox = colA.bLayerMask & static_cast<uint32_t>(colB.myLeyer);
	bool canBHitBox = colB.bLayerMask & static_cast<uint32_t>(colA.myLeyer);

	if (canAHitCap && canBHitCap)return 1;
	else if (canAHitBox && canBHitBox)return 2;
	else if (canAHitCap && canBHitBox)return 3;
	else if (canAHitBox && canBHitCap)return 4;
	else return 0;
}

bool CollidManager::CheckCapsuleCollision(GameObject* objA, GameObject* objB)
{
	Collider colA = objA->GetCollider();
	Vector2 aPos = objA->GetPos();
	Vector2 a1 = aPos + colA.cPosA;
	Vector2 a2 = aPos + colA.cPosB;

	Collider colB = objB->GetCollider();
	Vector2 bPos = objB->GetPos();
	Vector2 b1 = bPos + colB.cPosA;
	Vector2 b2 = bPos + colB.cPosB;

	//線分の最接近距離
	float sqDist = GetLineMinDist(a1, a2, b1, b2);

	float radius = colA.radius + colB.radius;
	float sqRadius = radius * radius;

	//最接近距離が判定サイズより小さいか
	return sqDist <= sqRadius;
}

bool CollidManager::CheckBoxCollision(GameObject* objA, GameObject* objB)
{
	Collider colA = objA->GetCollider();
	Vector2 aPos = objA->GetPos();
	Vector2 a1 = aPos + colA.bPosA;
	Vector2 a2 = aPos + colA.bPosB;

	Collider colB = objB->GetCollider();
	Vector2 bPos = objB->GetPos();
	Vector2 b1 = bPos + colB.bPosA;
	Vector2 b2 = bPos + colB.bPosB;

	bool inX = (a1.x <= b2.x) && (a2.x >= b1.x);
	bool inY = (a1.y <= b2.y) && (a2.y >= b1.y);

	return inX && inY;
}

bool CollidManager::CheckCalsuleBoxCollision(GameObject* objA, GameObject* objB)
{
	Collider colA = objA->GetCollider();
	Vector2 aPos = objA->GetPos();
	Vector2 a1 = aPos + colA.cPosA;
	Vector2 a2 = aPos + colA.cPosB;

	Collider colB = objB->GetCollider();
	Vector2 bPos = objB->GetPos();
	Vector2 b1 = bPos + colB.bPosA;
	Vector2 b2 = bPos + colB.bPosB;

	float sqDist = GetLineBoxDist(a1, a2, b1, b2);
	float sqRadius = colA.radius * colA.radius;

	//最接近距離が判定サイズより小さいか
	return sqDist <= sqRadius;
}

void CollidManager::DrawCollider(GameObject* obj)
{
	if (!obj->HasCollider())return;
	if (obj->HasCapsule())
	{
		Collider col = obj->GetCollider();
		Vector2 pos = obj->GetPos();

		Vector2 p1 = pos + col.cPosA;
		Vector2 p2 = pos + col.cPosB;

		//始点と終点が同じであれば円として表示
		//if (Math2D::LengthSq(p1 - p2) <= 0.000f)
		if (p1 == p2)
		{
			DrawCircleAA(p1.x, p1.y, col.radius, DEBUG_COL, FALSE);
		}
		//それ以外は2つの円と線分で
		else
		{
			DrawLineAA(p1.x, p1.y, p2.x, p2.y, DEBUG_COL);
			DrawCircleAA(p1.x, p1.y, col.radius, DEBUG_COL, FALSE);
			DrawCircleAA(p2.x, p2.y, col.radius, DEBUG_COL, FALSE);
		}
	}
	if (obj->HasBox())
	{
		Collider col = obj->GetCollider();
		Vector2 pos = obj->GetPos();

		Vector2 p1 = pos + col.bPosA;
		Vector2 p2 = pos + col.bPosB;

		DrawBox((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, DEBUG_COL, FALSE);
	}


}

float CollidManager::GetLineMinDist(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
{
	//線分Aのベクトル
	Vector2 dA = a2 - a1;
	//線分Aの長さの2乗
	float a = Math2D::LengthSq(dA);
	//線分Bのベクトル
	Vector2 dB = b2 - b1;
	//線分Bの長さの2乗
	float b = Math2D::LengthSq(dB);
	//それぞれの線分を始点を結ぶベクトル
	Vector2 r = a1 - b1;
	//float f = dB.x * r.x + dB.y + r.y;
	float f = Math2D::Dot(dB, r);

	float s = 0.0f;
	float t = 0.0f;

	//どちらの線分も点だった場合
	if (a <= 0.0001f && b <= 0.0001f)
	{
		s = 0.0f;
		t = 0.0f;
	}
	//線分Aのみ点だった場合
	else if (a <= 0.0001f)
	{
		s = 0.0f;
		t = std::clamp(f / b, 0.0f, 1.0f);
	}
	else
	{
		//float c = dA.x * r.x + dA.y * r.y;
		float c = Math2D::Dot(dA, r);
		//線分Bのみ点だった場合
		if (b <= 0.0001f)
		{
			s = std::clamp(-c / a, 0.0f, 1.0f);
			t = 0.0f;
		}
		//どちらも線分の時の場合
		else
		{
			//float e = dA.x * dB.x + dA.y * dB.y;
			float e = Math2D::Dot(dA, dB);
			float denom = a * b - e * e;

			//2つの線分が平行じゃなければ
			if (denom != 0.0f)
			{
				s = std::clamp((e * f - c * b) / denom, 0.0f, 1.0f);
			}
			else
			{
				s = 0.0f;
			}

			t = (e * s + f) / b;

			if (t < 0.0f)
			{
				t = 0.0f;
				s = std::clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t > 1.0f)
			{
				t = 1.0f;
				s = std::clamp((e - c) / a, 0.0f, 1.0f);
			}
		}
	}

	//線分A上の最接近点
	Vector2 closestA = a1 + (dA * s);

	//線分B上の最接近点
	Vector2 closestB = b1 + (dB * t);

	Vector2 distVec = closestA - closestB;

	return Math2D::LengthSq(distVec);
}

float CollidManager::GetLineBoxDist(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
{
	//ボックスの中心座標
	Vector2 center = b1 + (b2 - b1) * 0.5;
	//線分のベクトル
	Vector2 dA = a2 - a1;
	//線分の長さの2乗
	float a = Math2D::LengthSq(dA);
	//ボックスの中心から線分の始点へのベクトル
	Vector2 dC = center - a1;
	float c = Math2D::LengthSq(dC);

	//線分上の最接近点
	Vector2 closestLine;
	//線分が点だった場合
	if (a < 0.0001f)
	{
		closestLine = a1;
	}
	else
	{
		float t = Math2D::Dot(dC, dA) / a;
		t = std::clamp(t, 0.0f, 1.0f);

		closestLine = a1 + (dA * t);
	}

	//ボックス上の最接近点
	Vector2 closestBox;
	closestBox.x = std::clamp(closestLine.x, b1.x, b2.x);
	closestBox.y = std::clamp(closestLine.y, b1.y, b2.y);

	Vector2 distVec = closestLine - closestBox;
	return Math2D::LengthSq(distVec);
}