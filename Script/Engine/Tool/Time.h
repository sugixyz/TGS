#pragma once
#include"DxLib.h"
#include<functional>

//フレーム間時間
extern float gDeltaTime;

/// <summary>
/// 全体の時間を管理する
/// </summary>
namespace Time
{
	/// <summary>
	/// フレーム間時間を取得
	/// </summary>
	/// <returns>フレーム間時間</returns>
	inline float GetDeltaTime()
	{
		if (gDeltaTime < 0.1f)
		{
			return gDeltaTime;
		}
		else
		{
			return 1 / 60;
		}
	}
}

/// <summary>
/// 時間を管理する構造体
/// </summary>
struct Timer
{
	int counter = 0;
	float timer = 0.0f;
	bool isStop = false;
	/// <summary>
	/// タイマーの値を取得する
	/// </summary>
	/// <returns>現在の経過時間</returns>
	float GetTimer() { return timer; }
	/// <summary>
	/// タイマーの更新
	/// </summary>
	void Update() {
		if (isStop)return;
		counter++;
		timer += Time::GetDeltaTime();
	}
	/// <summary>
	/// 指定した時間間隔ごとにtrueを返す
	/// </summary>
	/// <param name="interval">時間間隔</param>
	/// <returns>時間間隔を超えた瞬間にtrue</returns>
	bool IsEvery(float interval = 1.0f)
	{
		float dt = Time::GetDeltaTime();
		float prevTime = timer - dt;

		//前回の時間と今回の時間でintervalを跨いでいるか
		int currentCount = static_cast<int>(timer / interval);
		int prevCount = static_cast<int>(prevTime / interval);
		return currentCount > prevCount;
	}
	/// <summary>
	/// 指定したフレーム間隔ごとにtrueを返す
	/// </summary>
	/// <param name="interval">フレーム間隔</param>
	/// <returns>フレーム間隔を超えた瞬間にtrue</returns>
	bool IsEvery(int interval = 1)
	{
		//int prevCount = counter--;

		////前回の時間と今回の時間でintervalを跨いでいるか
		//int currentCount = static_cast<int>(counter / interval);
		//int prevCount = static_cast<int>(prevCount / interval);
		//return currentCount > prevCount;

		return (counter % interval == 0);
	}
	/// <summary>
	/// 指定した時間を超えた瞬間にtrueを返す
	/// </summary>
	/// <param name="sec">指定時間</param>
	/// <returns>時間を超えた瞬間にtrue</returns>
	bool isExpired(float sec)
	{
		float dt = Time::GetDeltaTime();
		float prevTime = timer - dt;

		//前回の時間と今回の時間でtimeを跨いでいるか
		return (prevTime < sec) && (sec <= timer);
	}
	/// <summary>
	/// 指定したフレームを超えた瞬間にtrueを返す
	/// </summary>
	/// <param name="frame">フレーム時間</param>
	/// <returns>フレーム時間を超えた瞬間にtrue</returns>
	bool isExpired(int frame)
	{
		float prevCount = counter - 1;

		//前回の時間と今回の時間でtimeを跨いでいるか
		return (prevCount < frame) && (frame <= counter);
	}
	/// <summary>
	/// タイマーを停止
	/// </summary>
	void Stop()
	{
		isStop = true;
	}
	/// <summary>
	/// タイマーを開始
	/// </summary>
	void Start()
	{
		isStop = false;
	}
	/// <summary>
	/// 開始、停止を切り替え
	/// </summary>
	void Switch()
	{
		if (isStop)isStop = false;
		else isStop = true;
	}
	/// <summary>
	/// 停止しているか
	/// </summary>
	/// <returns>停止していればtrue</returns>
	bool IsStop()
	{
		return isStop;
	}

	/// <summary>
	/// タイマーのリセット
	/// </summary>
	void Reset()
	{
		counter = 0;
		timer = 0.0f;
		isStop = false;
	}
};

//ゲーム全体のタイマー
extern Timer gGameTimer;

//１フレームを指定するときの定数
const float YIELD_FRAME = -1.0f;

/// <summary>
/// コルーチンの構造体
/// </summary>
struct Coroutine
{
	Timer timer;
	float sec = 0.0f;
	std::function<void()> callback = nullptr;
	bool isActive = false;

	/// <summary>
	/// コルーチンの更新処理
	/// タイマーが0になれば関数実行
	/// </summary>
	void Update()
	{
		//アクティブじゃないなら更新しない
		if (!isActive)return;

		//secが初期値のままなら１フレーム後に実行
		if (timer.timer == YIELD_FRAME)
		{
			sec = 0.0f;
			return;
		}

		timer.Update();
		if (callback)callback();

		if (timer.isExpired(sec))
		{
			Reset();
		}
	}
	/// <summary>
	/// コルーチンの開始
	/// 強制的に上書き
	/// </summary>
	/// <param name="func">実行する関数</param>
	/// <param name="sec">待つ時間（指定しなければ次のフレームで実行）</param>
	void Start(std::function<void()> func,float second = YIELD_FRAME)
	{
		sec = second;
		callback = func;
		isActive = true;
	}
	/// <summary>
	/// コルーチンの開始
	/// 実行済みの場合は開始しない
	/// </summary>
	/// <param name="func"></param>
	/// <param name="sec"></param>
	void Request(std::function<void()> func, float sec = YIELD_FRAME)
	{
		if (isActive)return;
		Start(func, sec);
	}
	/// <summary>
	/// 現在実行中か
	/// </summary>
	/// <returns>実行中ならtrue</returns>
	bool IsActive()
	{
		return isActive;
	}

	/// <summary>
	/// コルーチンの最後かどうか
	/// </summary>
	/// <returns>最後ならtrue</returns>
	bool IsEnd()
	{
		return timer.isExpired(sec);
	}

	/// <summary>
	/// リセット用関数
	/// </summary>
	void Reset()
	{
		timer.Reset();
		sec = 0.0f;
		callback = nullptr;
		isActive = false;
	}
};