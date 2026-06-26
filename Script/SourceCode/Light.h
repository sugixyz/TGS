#pragma once
#include"../Engine/Object/GameObject.h"

class Light : public GameObject
{
public:
	Light(Tag tag)
		:GameObject(tag)
	{}
	virtual ~Light() {}
protected:
	int hLight = -1;
};