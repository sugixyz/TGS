#include "PointLight.h"

PointLight::PointLight(VECTOR pos, float range)
	:Light(Tag::SYSTEM)
{
	position3 = pos;

	hLight = CreatePointLightHandle(position3, range, 0.0f, 0.005f, 0.0f);
	SetLightDifColorHandle(hLight, GetColorF(1.0f, 0.5f, 0.5f, 0.0f));
	SetLightSpcColorHandle(hLight, GetColorF(1.0f, 0.5f, 0.5f, 0.0f));
}

PointLight::~PointLight()
{
	if (hLight != -1)
	{
		DeleteLightHandle(hLight);
	}
}

void PointLight::Update()
{}
