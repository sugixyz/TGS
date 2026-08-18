#pragma once
#include "Enemy.h"

//enum class State
//{
//	ATTACK,
//	CHASE,
//	PATROL
//};

class Archer : public Enemy
{
public:
	Archer(Vector2 pos);
	~Archer();
	void Update() override;
	void Draw() override;
};