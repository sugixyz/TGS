#include "DirectionalLight.h"

VECTOR DirectionalLight::DIRECTION;
VECTOR DirectionalLight::COLOR;

DirectionalLight::DirectionalLight()
	:Light(Tag::SYSTEM)
{
	color = GetColorF(COLOR.x, COLOR.y, COLOR.z, 0.0f);
}

DirectionalLight::~DirectionalLight()
{}

void DirectionalLight::Update()
{
	SetLightEnable(TRUE);
	SetLightDirection(DIRECTION);
	SetLightDifColor(color);
	SetLightSpcColor(color);
}
