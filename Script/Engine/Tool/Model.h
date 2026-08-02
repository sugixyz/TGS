#pragma once
#include<string>

namespace Model
{
	void Initialize();
	void Release();
	/// <summary>
	/// モデルの複製ハンドルの取得
	/// </summary>
	/// <param name="fileKey">モデルファイル名</param>
	/// <returns>指定モデルの複製ハンドル</returns>
	int Load(std::string fileKey);
	/// <summary>
	/// モデルを読み込んで登録する
	/// </summary>
	/// <param name="file">モデル名</param>
	void SetHandle(std::string file);
}