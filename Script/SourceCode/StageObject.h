#pragma once
#include"../Engine/Object/GameObject.h"

class StageObject : public GameObject
{
public:
	StageObject(Vector3 pos, Vector3 rot, Vector3 sca, int id);
	~StageObject();
	void Draw() override;
private:
	int objId = 0;
};