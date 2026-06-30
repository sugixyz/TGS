#pragma once
#include"../Engine/Object/Character.h"

class Enemy : public Character
{
public:
	Enemy(Tag tag) 
		:Character(tag)
	{}
	virtual ~Enemy() {}
	/// <summary>
	/// ウィンドウの範囲外に行っていないか
	/// </summary>
	virtual void CheckOutRange()
	{
		if (position.x <= -radius * 2)DestroyMe();
		else if (position.x >= WIN_WIDTH + radius * 2)DestroyMe();
		else if (position.y <= -radius * 2)DestroyMe();
		else if (position.y >= WIN_HEIGHT + radius * 2)DestroyMe();
	}
};