#include "DataHolder.h"

/// <summary>
/// 画面遷移後も変数の値を保持する
/// </summary>

DataHolder::DataHolder()
	:GameObject(Tag::SYSTEM)
{
	DontDestroyOnSceneChange();
	//ここで変数の初期化
}

DataHolder::~DataHolder()
{
}
