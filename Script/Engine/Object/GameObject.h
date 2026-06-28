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
		myTag(tag),
		hModel(-1)
	{
		myColliders.clear();
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
	bool HasCollider() { return myColliders.size() > 0; }

	/// <summary>
	/// コライダーのゲット
	/// </summary>
	/// <returns>登録されたコライダー</returns>
	std::vector<Collider> GetCollider() { return myColliders; }

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
		Collider col;
		col.SetCapsule(sPos, ePos, rad, layer, mask);
		myColliders.push_back(col);
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
		Collider col;
		col.SetBox(sPos, ePos, layer, mask);
		myColliders.push_back(col);
	}

	/// <summary>
	/// ポジションを中心とした円コライダーのセット
	/// </summary>
	/// <param name="rad">半径</param>
	/// <param name="layer">自分を識別するレイヤー</param>
	/// <param name="mask">当たりたい対象のマスク（デフォルトなし）</param>
	void SetCenterCircle(float rad,Layer layer, uint32_t mask = 0x00000000)
	{
		Collider col;
		col.SetCapsule(Vector2(0, 0), Vector2(0, 0), rad, layer, mask);
		myColliders.push_back(col);
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
		Collider col;
		col.SetBox(p1, p2, layer, mask);
		myColliders.push_back(col);
	}

	/// <summary>
	/// 接触時の処理
	/// </summary>
	/// <param name="myLeyer">自分のレイヤー</param>
	/// <param name="other">接触した相手のポインタ</param>
	/// <param name="otherLayer">接触した相手のレイヤー</param>
	virtual void OnCollision(Layer myLeyer, GameObject* other, Layer otherLayer) {}

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
	//コライダーのリスト
	std::vector<Collider> myColliders;
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