#pragma once
#include"Item.h"

class Material : public Item
{
public:
	Material(int id);
	~Material();
	void Draw() override;
};