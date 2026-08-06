#pragma once
#include "Enemy.h"

enum class State
{
	ATTACK,
	CHASE,
	PATROL
};

class Normal : public Enemy
{
public:
	Normal(Vector2 pos);
	~Normal();
	void Update() override;
	void Draw() override;
};