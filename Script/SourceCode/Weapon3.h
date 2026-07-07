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
	void OnCollision(Layer myLayer, GameObject* other, Layer otherLayer);
	void EnhanceWeapon() override;
private:
	GameObject* target = nullptr;
	int continuousNumber = 0;
	int attackCount = 0;
private:
	void SearchTarget();
	bool CheckDuringStage(GameObject* enemy);
public:
	static int SWORD_NUMBER;
	static int CONTINUOUS_NUMBER;
	static float ATTACK_RADIUS;
	static float MOVE_DISTANCE;
	static float MOVE_TIME;
	static float COOL_TIME;
	static int ENHANCE_SWORD_NUMBER;
	static int ENHANCE_CONTINUOUS_NUMBER;
	static float ENHANCE_COOL_TIME;
};