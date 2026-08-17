#pragma once

//ゲーム、プレイヤーの状態の構造体
struct GameStateData
{
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
	int baseHP;
	//前ウェーブからの残存敵数
	int remainingEnemies;
	//ウェーブの終了した時間
	float waveEndTime;
	//次のウェーブの開始時間
	float nextWaveTime;
};

//次のウェーブのパラメータ
struct WaveParameters
{
	//このウェーブで湧かせる数
	int totalSpawnCount = 10;
	//スポーン間隔
	float spawnInterval = 1.0f;
	//最大同時存在数（敵の上限）
	int maxConcurrentEnemies = 30;
	//ウェーブの制限時間
	float waveTimeLimit = 20.0f;
	//次のウェーブまでの間隔
	float nextWaveInterval = 20.0f;

	//敵の出現比率
	float normalRatio = 0.6f;
	float archerRatio = 0.35f;
	float titanRatio = 0.05f;
};