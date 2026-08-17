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
	/// ウェーブが終了したときに呼ぶ関数
	/// </summary>
	void EndWave();
private:
	GameStateData gameState;
	//WaveParameters waveParameters;
private:
	//次のウェーブのパラメータを計算する
	WaveParameters CalculateNextWaveParameters();	
};