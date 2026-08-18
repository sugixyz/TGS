#pragma once
#include"../Engine/Object/GameObject.h"
#include"AiData.h"

class AiDirector : public GameObject
{
public:
	AiDirector();
	~AiDirector();
	/// <summary>
	/// 近接武器をクラフトしたときに呼ぶ関数
	/// </summary>
	void CraftMelleWeapon();
	/// <summary>
	/// 遠距離武器をクラフトしたときに呼ぶ関数
	/// </summary>
	void CraftLongRangeWeapon();
	/// <summary>
	/// 強化武器をクラフトしたときに呼ぶ関数
	/// </summary>
	void CraftEnhancedWeapon();
	/// <summary>
	/// 近接武器が壊れたときに呼ぶ関数
	/// </summary>
	void DestroyMeleeWeapon();
	/// <summary>
	/// 遠距離武器が壊れたときに呼ぶ関数
	/// </summary>
	void DestroyLongRangeWeapon();
	/// <summary>
	/// 強化武器が壊れたときに呼ぶ関数
	/// </summary>
	void DestroyEnhancedWeapon();
	/// <summary>
	/// 拠点がダメージを受けた時に呼ぶ関数
	/// </summary>
	void BaseHitDamage();
	/// <summary>
	/// ウェーブが開始したときに呼ぶ関数
	/// </summary>
	void StartWave();
	/// <summary>
	/// ウェーブが終了したときに呼ぶ関数
	/// </summary>
	void EndWave();
	/// <summary>
	/// 次のウェーブのパラメータを計算する
	/// </summary>
	/// <returns>ウェーブの情報パラメータ</returns>
	WaveParameters CalculateNextWaveParameters();
	/// <summary>
	/// 現在のゲームの状況を取得する
	/// </summary>
	/// <returns>現在のゲームの状況</returns>
	GameStateData GetGameStateData() { return gameState; }
private:
	GameStateData gameState;
	//WaveParameters waveParameters;
private:
	//残りタイムによる評価
	void EvaluateRemainingTime(WaveParameters& params);
	//武器のストックによる評価
	void EvaluateWeaponStock(WaveParameters& params);
	//武器のクラフトによる評価
	void EvaluateCraftWeapon(WaveParameters& params);
	//拠点のHPによる評価
	void EvaluateBaseHp(WaveParameters& params);
};