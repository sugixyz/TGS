#pragma once
/// <summary>
/// すべてのオブジェクトを管理します
/// ここからすべてのGameObjectのUpdate()/Draw()を呼び出します
/// </summary>

#include <list>
#include <string>
#include<vector>
class GameObject;

enum class Tag
{
	SYSTEM,
	STAGE,
	GIMMICK,
	PLAYER,
	ENEMY,
	ITEM,
	ATTACK,
	UI,
	SIZE
};

namespace ObjectManager
{
	void Initialize(); // 初期化
	void Update(); // 更新
	void Draw(); // 描画
	void Release(); // 開放

	/// <summary>
	/// GameObjectを追加します
	/// これを呼ぶと、GameObjectのUpdateとDrawが呼ばれるようになります
	/// </summary>
	/// <param name="obj">GameObjectのインスタンス</param>
	void Push(GameObject* obj);

	/// <summary>
	/// GameObjectを削除する
	/// </summary>
	/// <param name="obj">GameObjectのインスタンス</param>
	void Pop(GameObject* obj);

	/// <summary>
	/// 全てのGameObjectを削除する
	/// </summary>
	void DeleteAllGameObject();

	/// <summary>
	/// 全てのGameObjectを取得します
	/// この関数は、テンプレートで使っています
	/// </summary>
	const std::vector<GameObject*>& GetTagObject(Tag tag);

	/// <summary>
	/// クラス名でオブジェクトを探す
	/// </summary>
	/// <typeparam name="C">クラス</typeparam>
	/// <returns>オブジェクトの実態（存在しなければnullptr）</returns>
	template<class C> C* FindGameObject(Tag tag)
	{
		const std::vector<GameObject*>& objs = GetTagObject(tag);
		for (GameObject* obj : objs)
		{
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
				return inst;
		}
		return nullptr;
	}
	/// <summary>
	/// クラスのオブジェクトをすべて探す
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	/// <returns>オブジェクトの実態list</returns>
	template<class C> std::vector<C*> FindGameObjects(Tag tag)
	{
		std::vector<C*> out;
		out.clear();

		const std::vector<GameObject*>& objs = GetTagObject(tag);

		for (GameObject* obj : objs)
		{
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
			{
				out.push_back(inst);
			}
		}
		return out;
	}
}

/// <summary>
	/// クラス名でオブジェクトを探す
	/// </summary>
	/// <typeparam name="C">クラス</typeparam>
	/// <returns>オブジェクトの実態（存在しなければnullptr）</returns>
template<class C> C* FindGameObject(Tag tag)
{
	return ObjectManager::FindGameObject<C>(tag);
}

/// <summary>
/// クラスのオブジェクトをすべて探す
/// </summary>
/// <typeparam name="C">クラス名</typeparam>
/// <returns>オブジェクトの実態list</returns>
template<class C> std::vector<C*> FindGameObjects(Tag tag)
{
	return ObjectManager::FindGameObjects<C>(tag);
}

/// <summary>
/// タグを指定してオブジェクトをすべて探す
/// </summary>
/// <param name="tag">タグ名</param>
/// <returns>オブジェクトのポインタ</returns>
inline std::vector<GameObject*> FindTagObjects(Tag tag)
{
	return ObjectManager::GetTagObject(tag);
}

/// <summary>
/// タブを指定してオブジェクトを返す
/// </summary>
/// <param name="tag">タグ名</param>
/// <returns>オブジェクトのポインタ</returns>
inline GameObject* FindTagObject(Tag tag)
{
	return ObjectManager::GetTagObject(tag)[0];
}