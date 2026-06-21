#pragma once
#include"../Engine/Object/GameObject.h"

class Item;

class Gimmick : public GameObject
{
public:
	Gimmick(Tag tag)
		:GameObject(tag)
	{}
	~Gimmick() {}
	virtual Item* Interact(Item* item) 
	{
		return nullptr;
	}
protected:
	Item* hasItem = nullptr;
public:
	inline static float INTERACT_LENGHT;
};