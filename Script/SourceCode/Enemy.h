#pragma once
#include"../Engine/Object/Character.h"

class Enemy : public Character
{
public:
	Enemy(Vector2 pos);
	~Enemy();
	void Update() override;
	void Draw() override;
	void OnCollision(GameObject* other) override;
	void Move() override;
	/// <summary>
	/// ウィンドウの範囲外に行っていないか
	/// </summary>
	void CheckOutRange();
public:
	static float SPEED;
	static float RADIUS;
};