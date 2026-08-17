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
	gameState.baseHP = base->GetHp();
}

void AiDirector::EndWave()
{
	gameState.waveEndTime = gGameTimer.timer;
}

WaveParameters AiDirector::CalculateNextWaveParameters()
{
	return WaveParameters();
}
