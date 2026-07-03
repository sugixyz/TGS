#pragma once
#include"Weapon.h"

//爆弾
class Weapon2 : public Weapon
{
public:
	Weapon2();
	~Weapon2();
	void Update() override;
	void Draw() override;
	void Attack(Player* owner) override;
	void EnhanceWeapon() override;
private:
	float range = 0.0f;
	Vector2 attackPos;
public:
	static int BOMB_NUMBER;
	static float ATTACK_RANGE;
	static float ATTACK_RADIUS;
	static float FALL_TIME;
	static float AIM_SPEED;
	static float COOL_TIME;
	static int ENHANCE_BOMB_NUMBER;
	static float ENHANCE_ATTACK_RADIUS;
};