#pragma once
#include"Weapon.h"

class Slash;

class Weapon3 : public Weapon
{
public:
	Weapon3();
	~Weapon3();
	void Update() override;
	void Draw() override;
	void Attack(Player* owner) override;
	void EnhanceWeapon() override;
private:
	Slash* slash;
public:
	static int SWORD_NUMBER;
	static float ATTACK_RADIUS;
	static float MOVE_DISTANCE;
	static float MOVE_TIME;
	static float COOL_TIME;
	static int ENHANCE_SWORD_NUMBER;
	static float ENHANCE_COOL_TIME;
};