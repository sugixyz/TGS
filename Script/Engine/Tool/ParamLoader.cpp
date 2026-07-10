#include "ParamLoader.h"
#include"../../SourceCode/Player.h"
#include"../../SourceCode/NormalZombie.h"
#include"../../SourceCode/BowZombie.h"
#include"../../SourceCode/TitanZombie.h"
#include"../../SourceCode/Gimmick.h"
#include"../../SourceCode/Weapon1.h"
#include"../../SourceCode/Weapon2.h"
#include"../../SourceCode/Weapon3.h"
#include"../../SourceCode/Camera.h"
#include"../../SourceCode/DirectionalLight.h"

void Loader::AllClassParamLoad()
{
	std::string path = "Assets/Param.txt";
	std::ifstream file(path);
	//ファイルがなければスルー
	if (!file.is_open())return;

	std::string line;
	//どのセクションのデータを呼んでいるか
	std::string currentSection = "";

	while (std::getline(file, line))
	{
		//もし空行か、コメントだったらスルー
		if (line.empty() || line.rfind("//", 0) == 0)continue;

		//セクションの変更
		if (line.front() == '[' && line.back() == ']')
		{
			//[]を削除したものを現在のセクションとして保存
			currentSection = line.substr(1, line.size() - 2);
			continue;
		}

		std::stringstream ss(line);
		std::string key, eq;
		if (ss >> key >> eq)
		{
			if (currentSection == "Player")
			{
				if		(key == "MAX_HP")		{ ss >> Player::MAX_HP; }
				else if (key == "SPEED")		{ ss >> Player::SPEED; }
				else if (key == "SPAWN_POS_1")	{ ss >> Player::SPAWN_POS[0].x >> Player::SPAWN_POS[0].y; }
				else if (key == "SPAWN_POS_2")	{ ss >> Player::SPAWN_POS[1].x >> Player::SPAWN_POS[1].y; }
				else if (key == "RADIUS")		{ ss >> Player::RADIUS; }
				else if (key == "ITEM_OFFSET")	{ ss >> Player::ITEM_OFFSET; }
			}
			else if (currentSection == "Enemy")
			{
				if (key == "DESTINATION") { ss >> Enemy::DESTINATION.x >> Enemy::DESTINATION.y; }
			}
			else if (currentSection == "NormalZombie")
			{
				if (key == "MAX_HP")				{ ss >> NormalZombie::MAX_HP; }
				else if (key == "SPEED")			{ ss >> NormalZombie::SPEED; }
				else if (key == "RADIUS")			{ ss >> NormalZombie::RADIUS; }
				else if (key == "ATTACK_RADIUS")	{ ss >> NormalZombie::ATTACK_RADIUS; }
				else if (key == "SENSED_RANGE")		{ ss >> NormalZombie::SENSED_RANGE; }
				else if (key == "COOL_TIME")		{ ss >> NormalZombie::COOL_TIME; }
				else if (key == "DROP_RATE")		{ ss >> NormalZombie::DROP_RATE; }
			}
			else if (currentSection == "BowZombie")
			{
				if (key == "MAX_HP") { ss >> BowZombie::MAX_HP; }
				else if (key == "SPEED") { ss >> BowZombie::SPEED; }
				else if (key == "RADIUS") { ss >> BowZombie::RADIUS; }
				else if (key == "ATTACK_RADIUS") { ss >> BowZombie::ATTACK_RADIUS; }
				else if (key == "SENSED_RANGE") { ss >> BowZombie::SENSED_RANGE; }
				else if (key == "COOL_TIME") { ss >> BowZombie::COOL_TIME; }
				else if (key == "DROP_RATE") { ss >> BowZombie::DROP_RATE; }
			}
			else if (currentSection == "TitanZombie")
			{
				if (key == "MAX_HP") { ss >> TitanZombie::MAX_HP; }
				else if (key == "SPEED") { ss >> TitanZombie::SPEED; }
				else if (key == "RADIUS") { ss >> TitanZombie::RADIUS; }
				else if (key == "ATTACK_RADIUS") { ss >> TitanZombie::ATTACK_RADIUS; }
				else if (key == "SENSED_RANGE") { ss >> TitanZombie::SENSED_RANGE; }
				else if (key == "COOL_TIME") { ss >> TitanZombie::COOL_TIME; }
				else if (key == "DROP_RATE") { ss >> TitanZombie::DROP_RATE; }
			}
			else if (currentSection == "Gimmick")
			{
				if (key == "INTERACT_LENGHT") { ss >> Gimmick::INTERACT_LENGHT; }
			}
			else if (currentSection == "Weapon1")
			{
				if		(key == "BULLET_NUMBER")		{ ss >> Weapon1::BULLET_NUMBER; }
				else if (key == "BULLET_SPEED")			{ ss >> Weapon1::BULLET_SPEED; }
				else if (key == "ATTACK_RADIUS")		{ ss >> Weapon1::ATTACK_RADIUS; }
				else if (key == "COOL_TIME")			{ ss >> Weapon1::COOL_TIME; }
				else if (key == "ENHANCE_BULLET_NUMBER"){ ss >> Weapon1::ENHANCE_BULLET_NUMBER; }
				else if (key == "ENHANCE_COOL_TIME")	{ ss >> Weapon1::ENHANCE_COOL_TIME; }
			}
			else if (currentSection == "Weapon2")
			{
				if		(key == "BOMB_NUMBER")			{ ss >> Weapon2::BOMB_NUMBER; }
				else if (key == "FALL_TIME")			{ ss >> Weapon2::FALL_TIME; }
				else if	(key == "ATTACK_RANGE")			{ ss >> Weapon2::ATTACK_RANGE; }
				else if (key == "ATTACK_RADIUS")		{ ss >> Weapon2::ATTACK_RADIUS; }
				else if (key == "AIM_SPEED")			{ ss >> Weapon2::AIM_SPEED; }
				else if (key == "COOL_TIME")			{ ss >> Weapon2::COOL_TIME; }
				else if (key == "ENHANCE_BOMB_NUMBER")	{ ss >> Weapon2::ENHANCE_BOMB_NUMBER; }
				else if (key == "ENHANCE_ATTACK_RADIUS") { ss >> Weapon2::ENHANCE_ATTACK_RADIUS; }
			}
			else if (currentSection == "Weapon3")
			{
				if		(key == "SWORD_NUMBER")					{ ss >> Weapon3::SWORD_NUMBER; }
				else if (key == "CONTINUOUS_NUMBER")			{ ss >> Weapon3::CONTINUOUS_NUMBER; }
				else if (key == "ATTACK_RADIUS")				{ ss >> Weapon3::ATTACK_RADIUS; }
				else if (key == "MOVE_DISTANCE")				{ ss >> Weapon3::MOVE_DISTANCE; }
				else if (key == "MOVE_TIME")					{ ss >> Weapon3::MOVE_TIME; }
				else if (key == "COOL_TIME")					{ ss >> Weapon3::COOL_TIME; }
				else if (key == "ENHANCE_SWORD_NUMBER")			{ ss >> Weapon3::ENHANCE_SWORD_NUMBER; }
				else if (key == "ENHANCE_CONTINUOUS_NUMBER")	{ ss >> Weapon3::ENHANCE_CONTINUOUS_NUMBER; }
				else if (key == "ENHANCE_COOL_TIME")			{ ss >> Weapon3::ENHANCE_COOL_TIME; }
			}
			else if (currentSection == "Camera")
			{
				if		(key == "CAM_POS")		{ ss >> Camera::CAM_POS.x >> Camera::CAM_POS.y >> Camera::CAM_POS.z; }
				else if (key == "CAM_TARGET")	{ ss >> Camera::CAM_TARGET.x >> Camera::CAM_TARGET.y >> Camera::CAM_TARGET.z; }
			}
			else if (currentSection == "DirectionalLight")
			{
				if		(key == "DIRECTION") {
					ss	>> DirectionalLight::DIRECTION.x
						>> DirectionalLight::DIRECTION.y
						>> DirectionalLight::DIRECTION.z;
				}
				else if (key == "COLOR") {
					ss	>> DirectionalLight::COLOR.x 
						>> DirectionalLight::COLOR.y
						>> DirectionalLight::COLOR.z;
				}
			}
		}
	}
}
