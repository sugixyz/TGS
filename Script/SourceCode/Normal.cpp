#include "Normal.h"
#include "../Engine/Tool/Model.h"

void Normal::Initialize()
{
	/*Model::Load("Enemy");
	Model::SetHandle("Enemy");
	assert(hModel_ > 0);

	position3 = { 0.0f, 0.0f, 0.0f };*/
}

void Normal::Update()
{
}

void Normal::Draw()
{
	//MV1SetPosition(hModel_, position3);
	//MV1DrawModel(hModel_);
}

void Normal::Move()
{
}

void Normal::OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer)
{
	if (other->GetTag() == Tag::STAGE)
	{
	}
	else if (other->GetTag() == Tag::PLAYER)
	{
	}
	else if (other->GetTag() == Tag::ATTACK)
	{
	}
}