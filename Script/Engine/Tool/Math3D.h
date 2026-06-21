#pragma once
#include<cmath>
#include"../globals.h"

/// <summary>
/// 3Dベクトルの構造体
/// </summary>
struct Vector3
{
	float x;
	float y;
	float z;
	/// <summary>
	/// ベクトルの初期化
	/// </summary>
	Vector3()
		:x(0), y(0), z(0) {}
	/// <summary>
	/// ベクトルの初期化
	/// </summary>
	/// <param name="_x">X成分</param>
	/// <param name="_y">Y成分</param>
	/// <param name="_z">Z成分</param>
	Vector3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{}
};