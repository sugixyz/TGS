#pragma once

//ゲーム、プレイヤーの状態の構造体
struct GameStateData
{
	GameStateData()
		:killTime(0.0f),
		weaponStock(0),
		meleeWeaponStock(0),
		longRangeWeaponStock(0),
		enhancedWeaponStock(0),
		craftCount(0),
		baseHp(0),
		remainingEnemies(0),
		waveStartTime(0.0f),
		waveEndTime(0.0f),
		remainingTime(0.0f)
	{}

	//殲滅までにかかった時間
	float killTime;
	//武器所持数
	int weaponStock;
	//近接武器の所持数
	int meleeWeaponStock;
	//遠距離武器の所持数
	int longRangeWeaponStock;
	//強化武器の数
	int enhancedWeaponStock;
	//クラフト回数
	int craftCount;
	//拠点HP
	int baseHp;
	//前ウェーブからの残存敵数
	int remainingEnemies;
	//ウェーブの開始した時間
	float waveStartTime;
	//ウェーブの終了した時間
	float waveEndTime;
	//ウェーブの継続時間
	float remainingTime;
};

//次のウェーブのパラメータ
struct WaveParameters
{
	//このウェーブで湧かせる数
	int totalSpawnCount = 20;
	//スポーン間隔
	float spawnInterval = 1.0f;
	//最大同時存在数（敵の上限）
	int maxConcurrentEnemies = 40;
	//ウェーブの制限時間
	float waveTimeLimit = 40.0f;
	//次のウェーブまでの間隔
	float nextWaveInterval = 15.0f;

	//敵の出現比率
	float normalRatio = 10;
	float archerRatio = 9;
	float titanRatio = 1;
};