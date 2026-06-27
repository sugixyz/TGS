#pragma once
#include"Light.h"

class PointLight : public Light
{
public:
	PointLight(VECTOR pos, float range);
	~PointLight();
	void Update() override;
};