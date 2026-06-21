#pragma once
#include"../Engine/Object/GameObject.h"

class Base : public GameObject
{
public:
	Base(Vector2 pos,int blockSize);
	~Base();
	void OnCollision(GameObject* other) override;
};