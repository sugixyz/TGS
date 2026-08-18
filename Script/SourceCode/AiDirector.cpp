#include "AiDirector.h"
#include"../Engine/Tool/Event.h"
#include"Base.h"
#include"ObjectCreater.h"

AiDirector::AiDirector()
	:GameObject(Tag::SYSTEM)
{
	ObjectCreater creater;
	creater.CreateObject();

	Event::Instance().Get(Id::CRAFT_MELEE_WEAPON).Add([this] {CraftMelleWeapon(); });
	Event::Instance().Get(Id::CRAFT_LONG_RANGE_WEAPON).Add([this] {CraftLongRangeWeapon(); });
	Event::Instance().Get(Id::CRAFT_MELEE_WEAPON).Add([this] {CraftEnhancedWeapon(); });

	Event::Instance().Get(Id::DESTROY_MELEE_WEAPON).Add([this] {DestroyMeleeWeapon(); });
	Event::Instance().Get(Id::DESTROY_LONG_RANGE_WEAPON).Add([this] {DestroyLongRangeWeapon(); });
	Event::Instance().Get(Id::DESTROY_ENHANCED_WEAPON).Add([this] {DestroyEnhancedWeapon(); });

	Event::Instance().Get(Id::BASE_HIT_DAMAGE).Add([this] {BaseHitDamage(); });
	Event::Instance().Get(Id::END_WAVE).Add([this] {EndWave(); });
	Event::Instance().Get(Id::START_WAVE).Add([this] {StartWave(); });
}

AiDirector::~AiDirector()
{
	Event::Instance().Get(Id::CRAFT_MELEE_WEAPON).Remove((int)Id::CRAFT_MELEE_WEAPON);
	Event::Instance().Get(Id::CRAFT_LONG_RANGE_WEAPON).Remove((int)Id::CRAFT_LONG_RANGE_WEAPON);
	Event::Instance().Get(Id::CRAFT_ENHANCED_WEAPON).Remove((int)Id::DESTROY_ENHANCED_WEAPON);

	Event::Instance().Get(Id::DESTROY_MELEE_WEAPON).Remove((int)Id::DESTROY_MELEE_WEAPON);
	Event::Instance().Get(Id::DESTROY_LONG_RANGE_WEAPON).Remove((int)Id::DESTROY_LONG_RANGE_WEAPON);
	Event::Instance().Get(Id::DESTROY_ENHANCED_WEAPON).Remove((int)Id::DESTROY_ENHANCED_WEAPON);

	Event::Instance().Get(Id::BASE_HIT_DAMAGE).Remove((int)Id::BASE_HIT_DAMAGE);
	Event::Instance().Get(Id::END_WAVE).Remove((int)Id::END_WAVE);
	Event::Instance().Get(Id::START_WAVE).Remove((int)Id::START_WAVE);
}

void AiDirector::CraftMelleWeapon()
{
	gameState.meleeWeaponStock++;
	gameState.weaponStock++;
	gameState.craftCount++;
}

void AiDirector::CraftLongRangeWeapon()
{
	gameState.longRangeWeaponStock++;
	gameState.weaponStock++;
	gameState.craftCount++;
}

void AiDirector::CraftEnhancedWeapon()
{
	gameState.enhancedWeaponStock++;
	gameState.weaponStock++;
	gameState.craftCount++;
}

void AiDirector::DestroyMeleeWeapon()
{
	gameState.meleeWeaponStock--;
	gameState.weaponStock--;
}

void AiDirector::DestroyLongRangeWeapon()
{
	gameState.longRangeWeaponStock--;
	gameState.weaponStock--;
}

void AiDirector::DestroyEnhancedWeapon()
{
	gameState.enhancedWeaponStock--;
	gameState.weaponStock--;
}

void AiDirector::BaseHitDamage()
{
	Base* base = FindGameObject<Base>(Tag::STAGE);
	gameState.baseHp = base->GetHp();
}

void AiDirector::StartWave()
{
	gameState.waveStartTime = gGameTimer.timer;
}

void AiDirector::EndWave()
{
	gameState.waveEndTime = gGameTimer.timer;
	float clearTime = gameState.waveEndTime - gameState.waveStartTime;
	WaveParameters params;
	gameState.remainingTime = params.waveTimeLimit - clearTime;
}

WaveParameters AiDirector::CalculateNextWaveParameters()
{
	WaveParameters params;

	//ウェーブのクリア時間による評価
	EvaluateRemainingTime(params);
	//武器のストックによる評価
	EvaluateWeaponStock(params);
	//武器のクラフトによる評価
	EvaluateCraftWeapon(params);
	//拠点HPによる評価
	EvaluateBaseHp(params);

	return params;
}

void AiDirector::EvaluateRemainingTime(WaveParameters& params)
{
	float remainingTime = gameState.remainingTime;
	//余裕クリア
	if (remainingTime > 15.0f)
	{
		//ウェーブ開始までの間隔を短縮
		params.nextWaveInterval -= 3.0f;
		//敵の湧き数を増加
		params.totalSpawnCount += 3;
	}
	//適正クリア
	else if (remainingTime > 5.0f)
	{
		//ウェーブ開始までの間隔を短縮
		params.nextWaveInterval -= 2.0f;
	}
	//時間オーバー
	else if (remainingTime <= 0.0f)
	{
		//ウェーブ開始までの間隔を延長
		params.nextWaveInterval += 3.0f;
		//敵の湧き数を増加
		params.totalSpawnCount += 3;
	}
}

void AiDirector::EvaluateWeaponStock(WaveParameters & params)
{
	int weaponStock = gameState.weaponStock;
	//武器のストック十分
	if (weaponStock >= 5)
	{
		//敵の湧き数増加
		params.totalSpawnCount += 10;
	}
	//武器のストック不足
	else if (weaponStock <= 2)
	{
		//敵の湧き数減少
		params.totalSpawnCount -= 5;
	}

	int meleeStock = gameState.meleeWeaponStock;
	int longRangeStock = gameState.longRangeWeaponStock;
	//遠距離武器のほうが多い
	if (longRangeStock > meleeStock)
	{
		//アーチャーの出現比率上昇
		params.archerRatio += 2;
	}

	int enhancedStock = gameState.enhancedWeaponStock;
	//強化武器を持っている
	if (enhancedStock > 0)
	{
		//タイタンの出現比率上昇
		params.titanRatio += enhancedStock;
	}
}

void AiDirector::EvaluateCraftWeapon(WaveParameters & params)
{
	int craftCount = gameState.craftCount;
	//クラフト回数が1回以上
	if (craftCount > 0)
	{
		//敵の湧き数増加
		params.totalSpawnCount += craftCount;
	}
}

void AiDirector::EvaluateBaseHp(WaveParameters & params)
{
	int baseHp = gameState.baseHp;
	//ToDo : 拠点のマックスHPを設定して、割合を計算できるように
	float MAX_HP = 10000;
	float rate = baseHp / MAX_HP;
	//拠点HPが5割り以上残っている
	if (rate > 0.5)
	{
		//敵の湧き数増加
		params.totalSpawnCount += 5;
	}
	//拠点HPが残りわずか
	else if (rate < 0.2)
	{
		//敵の湧き数減少
		params.totalSpawnCount -= 8;
	}
}
