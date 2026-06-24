#include "Input.h"
#include "DxLib.h"

/// <summary>
/// キーボードとコントローラーの入力を管理する
/// </summary>

namespace Input {
	//キーボード取得関連
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//キーバッファ (現フレーム)
	char keyBuffOld[KEY_MAX];	//1つ前のキーバッファ(前フレーム) 
	char key_down[KEY_MAX];		//押された瞬間 
	char key_up[KEY_MAX];		//離された瞬間 
	char Key_Keep[KEY_MAX];		//押しっぱなし

	//コントローラー取得関連
	const int PAD_MAX = 32;
	char padBuff[2][PAD_MAX];      //現フレーム
	char padBuffOld[2][PAD_MAX];   //前フレーム
	char pad_down[2][PAD_MAX];     //押された瞬間
	char pad_up[2][PAD_MAX];       //離された瞬間
	char pad_keep[2][PAD_MAX];     //押しっぱなし
	//スティックの値を保持する変数
	int stickX[2], stickY[2];
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//全てのキーの状態を取得 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		if (Key_Keep[i] < 0)Key_Keep[i] = 1; //オーバーフロー対策
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//前フレームと現フレームのxor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		key_up[i] = key_xor & keyBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 
	}

}

bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]);

}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}

void Input::PadStateUpdate()
{
	//1Pか2Pかの識別子
	int padId[2] = { DX_INPUT_PAD1,DX_INPUT_PAD2 };

	for (int p = 0; p < 2; p++)
	{
		memcpy_s(padBuffOld[p], sizeof(char) * PAD_MAX, padBuff[p], sizeof(char) * PAD_MAX);

		int inputBit = GetJoypadInputState(padId[p]);
		GetJoypadAnalogInput(&stickX[p], &stickY[p], padId[p]);
		AssociateKey(p,inputBit);

		for (int i = 0; i < PAD_MAX; i++)
		{
			//i番目のビットが立っているかチェック
			if (inputBit & (1 << i))
			{
				padBuff[p][i] = 1;
			}
			else
			{
				padBuff[p][i] = 0;
			}

			if (padBuff[p][i] && padBuffOld[p][i]) pad_keep[p][i]++;
			if (pad_keep[p][i] < 0)pad_keep[p][i] = 1; //オーバーフロー対策
			int pad_xor = padBuff[p][i] ^ padBuffOld[p][i];	//前フレームと現フレームのxor
			if (pad_xor) pad_keep[p][i] = 0;
			pad_down[p][i] = pad_xor & padBuff[p][i];		//押された瞬間 = (現フレームとkey_xorのAND) 
			pad_up[p][i] = pad_xor & padBuffOld[p][i];	//離された瞬間 = (前フレームとkey_xorのAND) 
		}

	}
}

bool Input::IsPadUp(int padCode, int padId)
{
	return pad_up[padId][padCode];
}

bool Input::IsPadDown(int padCode, int padId)
{
	return pad_down[padId][padCode];
}

int Input::IsKeepPadDown(int padCode, int padId)
{
	return pad_keep[padId][padCode];
}

Vector2 Input::GetStick(int padId)
{
	return CangeNumberToRate(Vector2((float)stickX[padId], (float)stickY[padId]));
}

void Input::AssociateKey(int id,int& bit)
{
	//パッド１
	if (id == 0)
	{
		//Wでパッド１のスティック上
		if (Input::IsKeepKeyDown(KEY_INPUT_W))stickY[id] = -1000;
		else if (Input::IsKeyUP(KEY_INPUT_W))stickY[id] = 0;
		//Sでパッド１のスティック下
		if (Input::IsKeepKeyDown(KEY_INPUT_S))stickY[id] = 1000;
		else if (Input::IsKeyUP(KEY_INPUT_S))stickY[id] = 0;
		//Aでパッド１のスティック左
		if (Input::IsKeepKeyDown(KEY_INPUT_A))stickX[id] = -1000;
		else if (Input::IsKeyUP(KEY_INPUT_A))stickX[id] = 0;
		//Dでパッド１のスティック右
		if (Input::IsKeepKeyDown(KEY_INPUT_D))stickX[id] = 1000;
		else if (Input::IsKeyUP(KEY_INPUT_D))stickX[id] = 0;
		//Fでパッド１のボタンA
		if (Input::IsKeepKeyDown(KEY_INPUT_F))bit = bit | 1 << Pad::A;
		//左sftでパッド１のボタンRB
		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))bit = bit | 1 << Pad::RB;
	}

	//パッド２
	if (id == 1)
	{
		//↑でパッド２のスティック上
		if (Input::IsKeepKeyDown(KEY_INPUT_UP))stickY[id] = -1000;
		else if (Input::IsKeyUP(KEY_INPUT_UP))stickY[id] = 0;
		//↓でパッド２のスティック下
		if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))stickY[id] = 1000;
		else if (Input::IsKeyUP(KEY_INPUT_DOWN))stickY[id] = 0;
		//←でパッド２のスティック左
		if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))stickX[id] = -1000;
		else if (Input::IsKeyUP(KEY_INPUT_LEFT))stickX[id] = 0;
		//→でパッド２のスティック右
		if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))stickX[id] = 1000;
		else if (Input::IsKeyUP(KEY_INPUT_RIGHT))stickX[id] = 0;
		//右ctrでパッド２のボタンA
		if (Input::IsKeepKeyDown(KEY_INPUT_RCONTROL))bit = bit | 1 << Pad::A;
		//右sftでパッド２のボタンRB
		if (Input::IsKeepKeyDown(KEY_INPUT_RSHIFT))bit = bit | 1 << Pad::RB;
	}
}

Vector2 Input::CangeNumberToRate(Vector2 n)
{
	Vector2 rate;
	//1～-1の割合にして返す
	rate.x = n.x / 1000.0f;
	rate.y = n.y / 1000.0f;
	//制限
	if (rate.x > 1.0f)rate.x = 1.0f;
	if (rate.x < -1.0f)rate.x = -1.0f;
	if (rate.y > 1.0f)rate.y = 1.0f;
	if (rate.y < -1.0f)rate.y = -1.0f;
	////中央を無視
	//if (-0.1f < rate.x && rate.x < 0.1f)rate.x = 0.0f;
	//if (-0.1f < rate.y && rate.y < 0.1f)rate.y = 0.0f;
	return rate;
}
