#pragma once
#include"Weapon.h"
#include "../Engine/Tool/Math2D.h"
#include "Player.h"

//銃器
class Weapon1 : public Weapon
{
public:
	Weapon1();
	~Weapon1();
	void Update() override;
	void Draw() override;
	void Attack(Player* owner) override;
	void EnhanceWeapon() override;
private:
	//予測線の終点を計算
	Vector2 CalculateLineEnd();
public:
	static int BULLET_NUMBER;
	static float BULLET_SPEED;
	static float ATTACK_RADIUS;
	static float COOL_TIME;
	static int ENHANCE_BULLET_NUMBER;
	static float ENHANCE_COOL_TIME;
};