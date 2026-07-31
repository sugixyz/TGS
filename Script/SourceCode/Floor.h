#pragma once
#include"../Engine/Object/GameObject.h"

class Floor : public GameObject
{
public:
	Floor(Vector2 pos, int blockSize);
	~Floor();
	void Draw() override;
	//void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
private:
	int block;
};