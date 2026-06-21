#pragma once
#include<functional>
#include<vector>
#include<unordered_map>
#include<array>

/// <summary>
/// イベントのID
/// </summary>
enum class Id
{
	ADD_SCORE,
	SIZE
};

/// <summary>
/// 登録されたイベントの処理
/// </summary>
class EventFill
{
public:
	/// <summary>
	/// イベントを登録する
	/// </summary>
	/// <param name="func">登録する関数</param>
	/// <returns>イベント番号</returns>
	unsigned int Add(std::function<void()> func)
	{
		unsigned int currentId = funcId++;
		funcVoids.push_back({ currentId,func });
		return currentId;
	}
	/// <summary>
	/// イベントを登録する（int引数あり）
	/// </summary>
	/// <param name="func">登録する関数</param>
	/// <returns>イベント番号</returns>
	unsigned int Add(std::function<void(int)> func)
	{
		unsigned int currentId = funcId++;
		funcInts.push_back({ currentId,func });
		return currentId;
	}

	/// <summary>
	/// イベントの削除
	/// </summary>
	/// <param name="id">削除したいイベント番号</param>
	void Remove(unsigned int id)
	{
		for (auto itr = funcVoids.begin(); itr != funcVoids.end();)
		{
			if (itr->id == id)
			{
				itr = funcVoids.erase(itr);
				return;
			}
			else
			{
				itr++;
			}
		}
		for (auto itr = funcInts.begin(); itr != funcInts.end();)
		{
			if (itr->id == id)
			{
				itr = funcInts.erase(itr);
				return;
			}
			else
			{
				itr++;
			}
		}
	}
	/// <summary>
	/// 登録されている関数の実行
	/// </summary>
	void Invoke()
	{
		for (const auto& func : funcVoids)
		{
			if (func.callback)func.callback();
		}
	}
	/// <summary>
	/// 登録されている関数の実行（int引数あり）
	/// </summary>
	/// <param name="arg">intの引数</param>
	void Invoke(int arg)
	{
		for (const auto& func : funcInts)
		{
			if (func.callback)func.callback(arg);
		}
	}
	/// <summary>
	/// 登録された関数を全部削除
	/// </summary>
	void RemoveAll()
	{
		funcVoids.clear();
		funcInts.clear();
	}
private:
	//IDと実行する関数を保持する構造体
	struct FuncListVoid
	{
		unsigned int id;
		std::function<void()> callback;
	};
	struct FuncListInt
	{
		unsigned int id;
		std::function<void(int)> callback;
	};
	//登録するイベント
	//引数なし
	std::vector<FuncListVoid> funcVoids;
	//引数あり int
	std::vector<FuncListInt> funcInts;
	//イベント番号管理ようの整数
	unsigned int funcId = 0;
};

/// <summary>
/// イベントを管理するクラス
/// </summary>
class Event
{
public:
	/// <summary>
	/// インスタンスを静的に作成
	/// </summary>
	/// <returns>インスタンスのポインタ</returns>
	static Event& Instance()
	{
		static Event instance;
		return instance;
	}
	/// <summary>
	/// 指定したIDのイベントを取得
	/// </summary>
	/// <param name="id">イベントのID</param>
	/// <returns>イベントのポインタ</returns>
	EventFill& Get(Id id)
	{
		return channels[static_cast<size_t>(id)];
	}
	/// <summary>
	/// イベントの登録を削除
	/// </summary>
	void ClearAll()
	{
		for (auto& ch : channels)
		{
			ch.RemoveAll();
		}
	}
private:
	Event() {}
	~Event() {}
	//コピーの禁止
	Event(const Event&) = delete;
	Event& operator=(const Event&) = delete;
private:
	//IDとイベントを一意に管理
	std::array<EventFill, static_cast<size_t>(Id::SIZE)> channels;
};

