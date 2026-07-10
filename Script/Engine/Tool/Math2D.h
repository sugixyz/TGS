#pragma once
#include <cmath>
#include"../globals.h"

/// <summary>
/// 2Dベクトルの構造体
/// </summary>
struct Vector2
{
	float x;
	float y;
	/// <summary>
	/// ベクトルの初期化(0,0)
	/// </summary>
	Vector2()
		:x(0), y(0) {}
	/// <summary>
	/// ベクトルの初期化(数値指定)
	/// </summary>
	/// <param name="_x">X成分</param>
	/// <param name="_y">Y成分</param>
	Vector2(float _x, float _y)
		:x(_x), y(_y)
	{
	}
	/// <summary>
	/// ベクトルの加算
	/// </summary>
	/// <param name="other">加算するベクトル</param>
	/// <returns>加算結果</returns>
	Vector2& Add(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	/// <summary>
	/// 特殊演算子オーバーロード：ベクトルの加算
	/// </summary>
	/// <param name="v">加算するベクトル</param>
	/// <returns>加算結果</returns>
	Vector2& operator+=(const Vector2& v)
	{
		return Add(v);
	}
	/// <summary>
	/// 演算子オーバーロード：ベクトルの加算
	/// </summary>
	/// <param name="v">加算するベクトル</param>
	/// <returns>加算結果</returns>
	Vector2 operator+(const Vector2& v)const
	{
		//コピーを作成し自分を返す
		Vector2 result = *this;
		result.Add(v);
		return result;
	}
	/// <summary>
	/// ベクトルの減算
	/// </summary>
	/// <param name="other">減算するベクトル</param>
	/// <returns>減算結果</returns>
	Vector2& Sub(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	/// <summary>
	/// 特殊演算子オーバーロード：ベクトルの減算
	/// </summary>
	/// <param name="v">減算するベクトル</param>
	/// <returns>減算結果</returns>
	Vector2& operator-=(const Vector2& v)
	{
		return Sub(v);
	}
	/// <summary>
	/// 演算子オーバーロード：ベクトルの減算
	/// </summary>
	/// <param name="v">減算するベクトル</param>
	/// <returns>減算結果</returns>
	Vector2 operator-(const Vector2& v)const
	{
		//コピーを作成し自分を返す
		Vector2 result = *this;
		result.Sub(v);
		return result;
	}
	/// <summary>
	/// ベクトルのスカラー倍
	/// </summary>
	/// <param name="s">倍率</param>
	/// <returns>スカラー倍結果</returns>
	Vector2& Mul(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	/// <summary>
	/// 特殊演算子オーバーロード：ベクトルのスカラー倍
	/// </summary>
	/// <param name="s">倍率</param>
	/// <returns>スカラー倍結果</returns>
	Vector2& operator*=(float s)
	{
		return Mul(s);
	}
	/// <summary>
	/// 演算子オーバーロード：ベクトルのスカラー倍
	/// </summary>
	/// <param name="s">倍率</param>
	/// <returns>スカラー倍結果</returns>
	Vector2 operator*(float s)const
	{
		//コピーを作成し自分を返す
		Vector2 result = *this;
		result.Mul(s);
		return result;
	}
	/// <summary>
	/// 演算子オーバーロード：比較
	/// </summary>
	/// <param name="v">比較ベクトル</param>
	/// <returns>同じであればtrue</returns>
	bool operator==(Vector2 v)const
	{
		if (x == v.x && y == v.y)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// 演算子オーバーロード：比較
	/// </summary>
	/// <param name="v">比較ベクトル</param>
	/// <returns>違うならtrue</returns>
	bool operator!=(Vector2 v)const
	{
		if (x != v.x || y != v.y)
		{
			return true;
		}
		return false;
	}
};


/// <summary>
/// 2Dアフィン変換行列
/// </summary>
struct Mat2
{
	float m00, m01, tx;
	float m10, m11, ty;
	//    0    0    1
};


namespace Math2D
{
	// ---- 定数 ----
	const float PI = 3.14159265359f;
	const float PI2 = 6.2831853072f;
	//右ベクトル
	const Vector2 RIGHT = { 1,0 };
	//左ベクトル
	const Vector2 LEFT = { -1,0 };
	//上ベクトル
	const Vector2 UP = { 0,-1 };
	//下ベクトル
	const Vector2 DOWN = { 0,1 };

	/// <summary>
	/// ワールド座標をスクリーン座標に変換します（Y軸をWIN_HEIGHT基準で反転）。
	/// </summary>
	/// <param name="wpos">変換元のワールド座標</param>
	/// <returns>スクリーン座標としてのVector2</returns>
	inline Vector2 World2Screen(const Vector2& wpos)
	{
		Vector2 tmp; //temporary = 作業用領域
		tmp = { wpos.x,WIN_HEIGHT - wpos.y };
		return tmp;
	}

	// ---- 長さ ----

	/// <summary>
	/// ベクトルの長さの2乗(sqrtを使用しないので高速)
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>( v.x )2乗 + ( v.y )2乗</returns>
	inline float LengthSq(const Vector2& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	/// <summary>
	/// ベクトルの長さ(ノルム)
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>√( ( v.x )2乗 + ( v.y )2乗 )/returns>
	inline float Length(const Vector2& v)
	{
		return sqrt(LengthSq(v));
	}

	/// <summary>
	/// ベクトルの正規化(長さを1に)
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>( v.x / len , v.y / len )</returns>
	inline Vector2 NormalZombieize(const Vector2& v)
	{
		float len = Length(v);
		if (len < 0.000001f) return { 1.0f, 0.0f }; //エラー ごまかす
		return { v.x / len,v.y / len };
	}
	/// <summary>
	/// ベクトル２つの距離
	/// </summary>
	/// <param name="a">ベクトルa</param>
	/// <param name="b">ベクトルb</param>
	/// <returns>ベクトルaとベクトルbの距離</returns>
	inline float Distance(const Vector2& a, const Vector2& b)
	{
		return Length(a - b);
	}

	// ---- 内積・外積 ----

	/// <summary>
	/// ベクトルの内積(2つのベクトルの向きの近さを表す)
	/// </summary>
	/// <param name="a">ベクトルa</param>
	/// <param name="b">ベクトルb</param>
	/// <returns>( a.x * b.x + a.y * b.y )</returns>
	inline float Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/// <summary>
	/// 2次元ベクトルの外積（スカラー）(正負で左右関係を判定可能)
	/// </summary>
	/// <param name="a">ベクトルa</param>
	/// <param name="b">ベクトルb</param>
	/// <returns>( a.x * b.y - a.y * b.x )</returns>
	inline float Cross(const Vector2& a, const Vector2& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	// ---- 角度 ----

	/// <summary>
	/// ベクトルから角度を取得
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>ベクトルのラジアン角</returns>
	inline float Angle(const Vector2& v)
	{
		return atan2(v.y, v.x);
	}

	/// <summary>
	/// ラジアンから単位ベクトルを取得
	/// </summary>
	/// <param name="rad">角度(ラジアン)</param>
	/// <returns>ラジアンθの方向ベクトル</returns>
	inline Vector2 FromAngle(float rad)
	{
		return { cos(rad),sin(rad) };
	}

	// ---- 行列生成 ----

	/// <summary>
	/// 単位行列の取得
	/// </summary>
	inline Mat2 Identity()
	{
		// 1  0  0
		// 0  1  0
		// 0  0  1
		return {
			1,0,0,
			0,1,0
		};
	}

	/// <summary>
	/// ラジアンから回転行列を取得
	/// </summary>
	/// <param name="rad">角度(ラジアン)</param>
	/// <returns>回転行列</returns>
	inline Mat2 Rotation(float rad)
	{
		float c = std::cos(rad);
		float s = std::sin(rad);
		Mat2 tmp;
		tmp.m00 = c; tmp.m01 = -s; tmp.tx = 0;
		tmp.m10 = s; tmp.m11 =  c; tmp.ty = 0;
		return tmp;
	}

	/// <summary>
	/// ベクトルから平行移動行列を取得
	/// </summary>
	/// <param name="t">移動ベクトル</param>
	/// <returns>移動行列</returns>
	inline Mat2 Translation(const Vector2& t)
	{
		Mat2 tmp;
		tmp.m00 = 1; tmp.m01 = 0; tmp.tx = t.x;
		tmp.m10 = 0; tmp.m11 = 1; tmp.ty = t.y;
		return tmp;
	}

	// ---- 行列合成 ----
	
	/// <summary>
	/// アフィン変換行列の合成
	/// </summary>
	/// <param name="a">最初に適応する行列</param>
	/// <param name="b">次に適応する行列</param>
	/// <returns>合成行列</returns>
	inline Mat2 Multiply(const Mat2& a, const Mat2& b)
	{
		Mat2 res;
		res.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.tx * 0;
		res.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.tx * 0;
		res.tx = a.m00 * b.tx + a.m01 * b.ty + a.tx * 1;
		res.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.ty * 0;
		res.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.ty * 0;
		res.ty =  a.m10 * b.tx  + a.m11 * b.ty  + a.ty * 1;
		return res;
	}

	// ---- 行列 × 点 ----

	/// <summary>
	/// アフィン変換行列の適応
	/// </summary>
	/// <param name="v">座標(ベクトル)</param>
	/// <param name="m">行列</param>
	/// <returns>変換後の座標(ベクトル)</returns>
	inline Vector2 TransformPoint(const Vector2& v, const Mat2& m)
	{
		Vector2 res(0, 0);
		res.x = m.m00 * v.x + m.m01 * v.y + m.tx;
		res.y = m.m10 * v.x + m.m11 * v.y + m.ty;
		return res;
	}
}
