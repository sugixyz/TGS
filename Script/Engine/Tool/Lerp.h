#pragma once
#include"../globals.h"
#include<functional>
#include<algorithm>

template <typename T>
struct Lerp
{
	T start;
	T end;
	float duration = 0.0f;
	float elapSed = 0.0f;
	bool isActive = false;
	std::function<void(T)> onUpdate = nullptr;

	/// <summary>
	/// ラープを開始する
	/// 強制的に上書き
	/// </summary>
	/// <param name="st">初期値</param>
	/// <param name="ed">終了値</param>
	/// <param name="sec">何秒間で処理するか</param>
	/// <param name="func">毎フレーム実行する関数</param>
	void Start(T st, T ed, float sec, std::function<void(T)> func = nullptr)
	{
		start = st;
		end = ed;
		duration = sec;
		onUpdate = func;
		elapSed = 0.0f;
		isActive = true;
	}
	/// <summary>
	/// ラープを開始する
	/// 実行済みの場合は開始しない
	/// </summary>
	/// <param name="st">初期値</param>
	/// <param name="ed">終了値</param>
	/// <param name="sec">何秒間で処理するか</param>
	/// <param name="func">毎フレーム実行する関数</param>
	void Request(T st, T ed, float sec, std::function<void(T)> func = nullptr)
	{
		if (isActive)return;
		Start(st, ed, sec, func);
	}
	/// <summary>
	/// ラープの更新
	/// </summary>
	void Update()
	{
		if (!isActive)return;
		
		float dt = Time::GetDeltaTime();
		elapSed += dt;
		//経過割合を計算(1.0fを最大値に)
		float t = (std::min)(elapSed / duration, 1.0f);

		//線形保管の計算
		T current = start + (end - start) * t;

		if (onUpdate)onUpdate(current);
		if (t >= 1.0f)
		{
			isActive = false;
		}
	}
	/// <summary>
	/// 実行中か
	/// </summary>
	/// <returns>実行中ならtrue</returns>
	bool IsActive()
	{
		return isActive;
	}

	void Reset()
	{
		duration = 0.0f;
		elapSed = 0.0f;
		isActive = false;
		onUpdate = nullptr;
	}
};
