/// <summary>
/// すべてのオブジェクトを管理します
/// ここからすべてのGameObjectのUpdate()/Draw()を呼び出します
/// </summary>

#include "ObjectManager.h"
#include "GameObject.h"
#include"../Tool/ParamLoader.h"
#include <assert.h>
#include<array>
#include<vector>

namespace 
{
	std::array<std::vector<GameObject*>, static_cast<size_t>(Tag::SIZE)> objLists;
	bool needSortDraw;
	GameObject* running;
};

void ObjectManager::Initialize()
{
	for (auto& list : objLists)
	{
		for (GameObject* obj : list)
		{
			delete obj;
		}
		list.clear();
	}
	running = nullptr;
}

void ObjectManager::Update()
{
	for (auto& list : objLists)
	{
		for (auto itr = list.begin(); itr != list.end(); itr++)
		{
			GameObject* obj = *itr;
			if (obj == nullptr)
			{
				continue;
			}
			if (not obj->DestroyRequested())
			{
				running = obj;
				obj->Update();
				running = nullptr;
			}
			if (obj->DestroyRequested())
			{
				delete obj;
				*itr = nullptr;
			}
		}
		for (auto itr = list.begin(); itr != list.end();)
		{
			if (*itr == nullptr)
			{
				itr = list.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}

void ObjectManager::Draw()
{
	for (auto& list : objLists)
	{
		for (GameObject* obj : list)
		{
			if (obj == nullptr || obj->DestroyRequested())
			{
				continue;
			}
			obj->Draw();
		}
	}
}

void ObjectManager::Release()
{
	for (auto& list : objLists)
	{
		for (GameObject* obj : list)
		{
			delete obj;
		}
		list.clear();
	}
}

void ObjectManager::Push(GameObject* obj)
{
	Tag tag = obj->GetTag();
	objLists[static_cast<size_t>(tag)].push_back(obj);
}

void ObjectManager::Pop(GameObject* obj)
{
	assert(running != obj);

	Tag tag = obj->GetTag();
	std::vector<GameObject*>& list = objLists[static_cast<size_t>(tag)];
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		if (*itr == obj)
		{
			*itr = nullptr;
			return;
		}
	}
}

void ObjectManager::DeleteAllGameObject()
{
	assert(running == nullptr);

	for (auto& list : objLists)
	{
		for (auto itr = list.begin(); itr != list.end(); itr++)
		{
			GameObject* obj = *itr;
			if (not obj->IsDontDestroy())
			{
				delete obj;
				*itr = nullptr;
			}
		}
		for (auto itr = list.begin(); itr != list.end();)
		{
			if (*itr == nullptr)
			{
				itr = list.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}

const std::vector<GameObject*>& ObjectManager::GetTagObject(Tag tag)
{
	return objLists[static_cast<size_t>(tag)];
}
