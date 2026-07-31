#pragma once
#include"../Engine/Object/GameObject.h"

class Wall : public GameObject
{
public:
	Wall(Vector2 pos, int blockSize);
	~Wall();
	void Draw() override;
	//void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) override;
private:
	int block;
};