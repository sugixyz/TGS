#pragma once
#include"Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	void Update() override;
private:
	COLOR_F color = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
public:
	static VECTOR DIRECTION;
	static VECTOR COLOR;
};