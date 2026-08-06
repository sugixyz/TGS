#include "Normal.h"
#include"../Engine/Tool/Model.h"

Normal::Normal(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	hModel = Model::Load("Enemy.mv1");
	assert(hModel > 0);
}

Normal::~Normal()
{
}

void Normal::Update()
{
}

void Normal::Draw()
{
}