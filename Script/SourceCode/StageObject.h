#pragma once
#include"../Engine/Object/GameObject.h"

class StageObject : public GameObject
{
public:
	StageObject(VECTOR pos, VECTOR rot, VECTOR sca, int id);
	~StageObject();
	void Draw() override;
private:
	int objId = 0;
};