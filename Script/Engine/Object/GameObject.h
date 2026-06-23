#pragma once
/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>

#include<string>
#include"ObjectManager.h"
#include"../Scene/SceneManager.h"
#include"../globals.h"
#include"../Tool/Math2D.h"
#include"../Tool/Input.h"
#include "DxLib.h"
#include"../Collid/Collider.h"
#include<assert.h>
#include<cstdio>

/// <summary>
/// これを継承したクラスのインスタンスは、ObjectManagerで管理され、
/// Update()とDraw()が自動で呼ばれます
/// </summary>
class GameObject
{
public:
	GameObject(Tag tag)
		: destroy(false),
		dontDestroy(false),
		myTag(tag)
	{
		ObjectManager::Push(this);
	}
	virtual ~GameObject()
	{
		ObjectManager::Pop(this);
	}

	/// <summary>
	/// 毎フレームの更新処理のために呼ばれます
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// 毎フレームの描画処理のために呼ばれます
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// ２Dの座標、方向ベクトルを３D描画用に変換
	/// </summary>
	virtual void Convert2Dto3D()
	{
		position3.x = (position.x - WIN_WIDTH / 2) / 100.0f;
		position3.y = 0;
		position3.z = -(position.y - WIN_HEIGHT / 2) / 100.0f;
		rotation3.y = atan2f(direction.x, -direction.y);
	}

	void DrawModel()
	{
		MATRIX mTrans = MGetTranslate(position3);
		MATRIX mRotX = MGetRotX(rotation3.x);
		MATRIX mRotY = MGetRotY(rotation3.y);
		MATRIX mRotZ = MGetRotZ(rotation3.z);
		MATRIX mScale = MGetScale(scale3);
		MATRIX mat = mScale;
		mat = MMult(mat, mRotZ);
		mat = MMult(mat, mRotX);
		mat = MMult(mat, mRotY);
		mat = MMult(mat, mTrans);
		MV1SetMatrix(hModel, mat);
		MV1DrawModel(hModel);
	}

	/// <summary>
	/// 自分のインスタンスを削除する時に呼び出してください
	/// 次回のUpdateの前に削除されます
	/// </summary>
	void DestroyMe() { destroy = true; }

	/// <summary>
	/// DestroyMeされているか調べる
	/// この関数はObjectManagerが使っています。
	/// </summary>
	/// <returns>DestroyMeされているとtrue</returns>
	inline bool DestroyRequested() const { return destroy; }

	/// <summary>
	/// シーンチェンジするときに、削除されなくする
	/// </summary>
	/// <param name="sw">書かなければtrue、falseにすると削除される</param>
	void DontDestroyOnSceneChange(bool sw = true) { dontDestroy = sw; }

	/// <summary>
	/// DontDestroyが設定されているか調べる
	/// この関数はObjectManagerが使っています
	/// </summary>
	/// <returns>DontDetroyになっていればtrue</returns>
	bool IsDontDestroy() const { return dontDestroy; }

	/// <summary>
	/// 自分のタグを取得
	/// </summary>
	/// <returns>タグ</returns>
	Tag GetTag() const
	{
		return myTag;
	}

	/// <summary>
	/// コライダーを持っているか
	/// </summary>
	/// <returns>コライダーがあればtrue</returns>
	bool HasCollider() { return myCollider.hasObject; }

	/// <summary>
	/// カプセルコライダーを持っているか
	/// </summary>
	/// <returns>カプセルコライダーがあればtrue</returns>
	bool HasCapsule() { return myCollider.hasCapsule; }

	/// <summary>
	/// ボックスコライダーを持っているか
	/// </summary>
	/// <returns>ボックスコライダーがあればtrue</returns>
	bool HasBox() { return myCollider.hasBox; }

	/// <summary>
	/// コライダーのゲット
	/// </summary>
	/// <returns>登録されたコライダー</returns>
	Collider GetCollider() { return myCollider; }

	/// <summary>
	/// カプセルコライダーのセット
	/// </summary>
	/// <param name="startPos">始点</param>
	/// <param name="endPos">終点</param>
	/// <param name="rad">半径</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCapsule(Vector2 sPos, Vector2 ePos, float rad, Layer layer, uint32_t mask = 0x00000000)
	{
		myCollider.SetCapsule(sPos, ePos, rad, layer, mask);
	}

	/// <summary>
	/// ボックスコライダーのセット
	/// </summary>
	/// <param name="startPos">始点</param>
	/// <param name="endPos">終点</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetBox(Vector2 sPos, Vector2 ePos, Layer layer, uint32_t mask = 0x00000000)
	{
		myCollider.SetBox(sPos, ePos, layer, mask);
	}

	/// <summary>
	/// ポジションを中心とした円コライダーのセット
	/// </summary>
	/// <param name="rad">半径</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCenterCircle(float rad,Layer layer, uint32_t mask = 0x00000000)
	{
		myCollider.SetCapsule(Vector2(0, 0), Vector2(0, 0), rad, layer, mask);
	}
	/// <summary>
	/// ポジションを中心としたボックスコライダーのセット
	/// </summary>
	/// <param name="rad">半径</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）
	void SetCenterBox(float rad,Layer layer, uint32_t mask = 0x00000000)
	{
		Vector2 p1 = Vector2((float)-rad, (float)-rad);
		Vector2 p2 = Vector2((float)rad, (float)rad);
		myCollider.SetBox(p1, p2, layer, mask);
	}

	/// <summary>
	/// 接触時の処理
	/// </summary>
	/// <param name="">接触した相手のポインタ</param>
	virtual void OnCollision(GameObject*) {}

	/// <summary>
	/// 位置の設定
	/// </summary>
	/// <param name="pos">適応する位置</param>
	void SetPos(Vector2 pos) {
		position = pos;
	}
	/// <summary>
	/// 位置を取得する
	/// </summary>
	/// <returns>現在の位置</returns>
	Vector2 GetPos() { return position; }

	/// <summary>
	/// 方向の設定
	/// </summary>
	/// <param name="dir">適応する方向</param>
	void SetDir(Vector2 dir) { direction = dir; }
	/// <summary>
	/// 方向を取得する
	/// </summary>
	/// <returns>現在の方向</returns>
	Vector2 GetDir() { return direction; }

private:
	bool destroy;
	bool dontDestroy;
	Tag myTag;
protected:
	//コライダー
	Collider myCollider;
	//モデル保存用ハンドル
	int hModel = -1;
	//位置 コリジョン処理の関係でGameObjectに移動
	Vector2 position;
	//方向
	Vector2 direction;

	//3D描画用の変数
	VECTOR position3 = { 0,0,0 };
	VECTOR rotation3 = { 0,0,0 };
	VECTOR scale3 = { 1,1,1 };
};