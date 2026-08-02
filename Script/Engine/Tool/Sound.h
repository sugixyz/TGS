#pragma once
#include<string>

namespace Sound
{
	void Initialize();
	void Release();
	/// <summary>
	/// マスターボリューム（全体）設定
	/// </summary>
	/// <param name="vol">音量（0～1）</param>
	void SetMasterVolume(float vol);
	/// <summary>
	/// BGMのボリューム設定
	/// </summary>
	/// <param name="vol">音量（0～1）</param>
	void SetBgmVolume(float vol);
	/// <summary>
	/// SEのボリューム設定
	/// </summary>
	/// <param name="vol">音量（0～1）</param>
	void SetSeVolume(float vol);
	/// <summary>
	/// BGM音量の計算
	/// </summary>
	/// <returns>BGMの音量（0～255）</returns>
	int CalculateBgmVolume();
	/// <summary>
	/// SE音量の計算
	/// </summary>
	/// <returns>SEの音量（0～255）</returns>
	int CalculateSeVolume();

	namespace BGM
	{
		void Initialize();
		/// <summary>
		/// BGMの再生
		/// </summary>
		void Play(const std::string& file,bool loop);
		/// <summary>
		/// BGMの停止
		/// </summary>
		void Stop();
		/// <summary>
		/// 音量の適応
		/// </summary>
		void ApplyVlume();
		/// <summary>
		/// BGMを読み込んで登録する
		/// </summary>
		/// <param name="file">BGM名</param>
		void SetHandle(std::string file);
	}

	namespace SE
	{
		void Initialize();
		/// <summary>
		/// SEの再生
		/// </summary>
		void Play(const std::string& file);
		/// <summary>
		/// SEを読み込んで登録する
		/// </summary>
		/// <param name="file">SE名</param>
		void SetHandle(std::string file);
	}
}