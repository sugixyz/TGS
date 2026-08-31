#include "Titan.h"

Titan::Titan(Vector2 pos)
	:Enemy(Tag::ENEMY)
{
	dropRate = 100;
	attackDamage = 5;
	float explosionRadius = attackRadius;
}

Titan::~Titan()
{
}

void Titan::Update()
{
}

void Titan::Draw()
{
}