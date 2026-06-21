#pragma once
#include"Weapon.h"

//銃器
class Weapon1 : public Weapon
{
public:
	Weapon1();
	~Weapon1();
	void Draw() override;
	void Attack(Player* owner) override;
	void EnhanceWeapon() override;
public:
	static int BULLET_NUMBER;
	static float BULLET_SPEED;
	static float ATTACK_RADIUS;
};