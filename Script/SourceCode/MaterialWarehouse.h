#pragma once
#include"Gimmick.h"

class MaterialWarehouse : public Gimmick
{
public:
	MaterialWarehouse(Vector2 pos,int id);
	~MaterialWarehouse();
	void Draw() override;
	Item* Interact(Item* item) override;
private:
	int materialId;
};