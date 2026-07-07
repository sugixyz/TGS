#pragma once
#include"Attack.h"

class Slash : public Attack
{
public:
	Slash(Vector2 pos,float rad);
	~Slash();
	void Update() override;
	void Draw() override;
	void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;	
};