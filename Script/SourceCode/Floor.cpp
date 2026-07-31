#include "Floor.h"
#include"../Engine/Tool/Model.h"

Floor::Floor(Vector2 pos, int blockSize)
	:GameObject(Tag::STAGE)
{
	position = pos;
	block = blockSize;

	//uint32_t mask = (uint32_t)Layer::PLAYER | (uint32_t)Layer::PLAYER_ATTACK |
	//	(uint32_t)Layer::ENEMY_ATTACK | (uint32_t)Layer::ENEMY;
	//SetCenterBox(block / 2.0f, Layer::STAGE, mask);

	hModel = Model::Load("Floor.mv1");
}

Floor::~Floor()
{}

void Floor::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		float x = position.x - block / 2.0f;
		float y = position.y - block / 2.0f;
		DrawBoxAA(x, y, x + block, y + block, COL_GRAY, TRUE);
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		Convert2Dto3D();
		DrawModel();
	}
}

//void Floor::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
//{
//	if (other->GetTag() == Tag::ATTACK)
//	{
//	}
//}
