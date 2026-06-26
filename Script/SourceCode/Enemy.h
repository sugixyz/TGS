#pragma once
#include"../Engine/Object/Character.h"

class Enemy : public Character
{
public:
	Enemy(Vector2 pos,Tag tag) 
		:Character(tag)
	{}
	virtual ~Enemy() {}
	/// <summary>
	/// ウィンドウの範囲外に行っていないか
	/// </summary>
	virtual void CheckOutRange() {}
};