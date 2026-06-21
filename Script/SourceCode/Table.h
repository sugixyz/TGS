#pragma once
#include"Gimmick.h"

class Table : public Gimmick
{
public:
	Table(Vector2 pos);
	~Table();
	void Draw() override;
	Item* Interact(Item* item) override;
};