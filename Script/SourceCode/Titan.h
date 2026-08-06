#pragma once
#include "Enemy.h"

enum class State
{
	ATTACK,
	CHASE,
	PATROL
};

class Titan : public Enemy
{
public:
	Titan(Vector2 pos);
	~Titan();
	void Update() override;
	void Draw() override;
};