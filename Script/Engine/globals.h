#pragma once
#include"DxLib.h"
#include"Tool/Time.h"

//ウィンドウサイズ
const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
//描画ウィンドウの拡大倍率
const int SCREEN_ZOOM = 1;

//色
//赤
const int COL_RED = GetColor(255, 0, 0);
//緑
const int COL_GREEN = GetColor(0, 255, 0);
//青
const int COL_BLUE = GetColor(0, 0, 255);
//白
const int COL_WHITE = GetColor(255, 255, 255);
//グレー
const int COL_GRAY = GetColor(128, 128, 128);
//黒
const int COL_BLACK = GetColor(0, 0, 0);
//シアン
const int COL_CYAN = GetColor(0, 255, 255);
//マゼンタ
const int COL_MAGENTA = GetColor(255, 0, 255);
//黄色
const int COL_YELLOW = GetColor(255, 255, 0);


enum Mode
{
	DEBUG,
	NORMAL,
	DOUBLE_MODE
};
extern Mode mode;