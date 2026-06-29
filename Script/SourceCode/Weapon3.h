#pragma once
#include"Weapon.h"

class Weapon3 : public Weapon
{
public:
	Weapon3();
	~Weapon3();
	void Draw() override;
	void Attack(Player* owner) override;
	void EnhanceWeapon() override;
private:
	GameObject* target;
public:
	static int SWORD_NUMBER;
	static float ATTACK_RADIUS;
	static float MOVE_DISTANCE;
	static float MOVE_TIME;
};