#include "DxLib.h"
#include "Engine/globals.h"
#include "Engine/Tool/Input.h"
#include"Engine/Object/ObjectManager.h"
#include"Engine/Scene/SceneManager.h"
#include"Engine/Collid/CollidManager.h"

/// <summary>
/// main関数
/// スクリーン（ウィンドウ）の管理
/// </summary>

namespace
{
	//背景色
	const int BGCOLOR[3] = {0, 0, 0}; 
	int crrTime;
	int prevTime;
	//実際のスクリーン（ウィンドウ）サイズ
	const int SCREEN_WIDHT = 1920;
	const int SCREEN_HEIGHT = 1080;
}


float gDeltaTime = 0.0f; // フレーム間の時間差
Timer gGameTimer;

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	//SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetGraphMode(SCREEN_WIDHT, SCREEN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}

void Initialize()
{
	ObjectManager::Initialize();
	SceneManager::Initialize();
	SetUseLighting(false);
}

void Update()
{
	SceneManager::Update();
	if (!gGameTimer.IsStop()) {
		ObjectManager::Update();
		CollidManager::Update();
	}
}

void Draw()
{
	SetCameraPositionAndTarget_UpVecY(VECTOR(0.0f, 10.0f, -5.0f), VECTOR(0.0f, 0.0f, 0.0f));
	SetCameraNearFar(0.f, 1000.0f);
	ObjectManager::Draw();
	CollidManager::Draw();
	SceneManager::Draw();
}

void Release()
{

}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Initialize();

	//FHDサイズの仮想スクリーン
	int virtualScreen = MakeScreen(WIN_WIDTH, WIN_HEIGHT, FALSE);

	while (true)
	{
		//仮想画面に描画
		SetDrawScreen(virtualScreen);
		ClearDrawScreen();

		Input::KeyStateUpdate(); // キー入力の状態を更新
		Input::PadStateUpdate(); //コントローラの入力状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存

		//ここにやりたい処理を書く
		Update();
		Draw();

		//本番用の画面に
		SetDrawScreen(DX_SCREEN_BACK);
		//ドット維持用
		//SetDrawMode(DX_DRAWMODE_NEAREST);
		//指定した画面サイズに拡縮
		DrawExtendGraph(0, 0, SCREEN_WIDHT, SCREEN_HEIGHT, virtualScreen, FALSE);

		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	Release();
	return 0;
}