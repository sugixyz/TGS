#pragma once
#include"../Engine/Object/GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	void Update() override;
private:
	VECTOR target;
public:
	static VECTOR CAM_POS;
	static VECTOR CAM_TARGET;
};