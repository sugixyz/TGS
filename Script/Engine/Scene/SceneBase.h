#pragma once

/// <summary>
/// シーンの基底クラス
/// </summary>
/// <author>H.suginunma</author>

#include<list>
#include"../Object/GameObject.h"
#include"../Tool/Input.h"
#include"../globals.h"
#include"SceneManager.h"

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Update() {}
	virtual void Draw() {}
};