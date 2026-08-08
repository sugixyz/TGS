#include "Wall.h"
#include"../Engine/Tool/Model.h"

Wall::Wall(Vector2 pos, int blockSize)
	:GameObject(Tag::STAGE)
{
	position = pos;
	block = blockSize;

	//uint32_t mask = (uint32_t)Layer::PLAYER | (uint32_t)Layer::PLAYER_ATTACK |
	//	(uint32_t)Layer::ENEMY_ATTACK | (uint32_t)Layer::ENEMY;
	//SetCenterBox(block / 2.0f, Layer::STAGE, mask);

	hModel = Model::Load("Wall.mv1");
}

Wall::~Wall()
{
	MV1DeleteModel(hModel);
}

void Wall::Draw()
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

//void Wall::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
//{
//	if (other->GetTag() == Tag::ATTACK)
//	{
//	}
//}
