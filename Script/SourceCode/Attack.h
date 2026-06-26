#pragma once
#include"../Engine/Object/Character.h"

class Attack : public Character
{
public:
	Attack(Tag tag)
		:Character(tag)
	{}
	virtual ~Attack() {}
	/// <summary>
	/// ウィンドウの範囲外に行っていないか
	/// </summary>
	void CheckOutRange()
	{
		if (position.x <= -radius * 2)DestroyMe();
		else if (position.x >= WIN_WIDTH + radius * 2)DestroyMe();
		else if (position.y <= -radius * 2)DestroyMe();
		else if (position.y >= WIN_HEIGHT + radius * 2)DestroyMe();
	}
};