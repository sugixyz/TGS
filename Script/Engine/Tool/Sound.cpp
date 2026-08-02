#include "Sound.h"
#include"DxLib.h"
#include<unordered_map>
#include<algorithm>
#include<assert.h>

namespace
{
    float masterVolume = 1.0f;
    float bgmVolume = 1.0f;
    float seVolume = 1.0f;

    std::unordered_map<std::string, int> bgmHandles;
    std::unordered_map<std::string, int> seHandles;
    std::string currentBgm = "";
}

void Sound::Initialize()
{
    masterVolume = 1.0f;
    bgmVolume = 1.0f;
    seVolume = 1.0f;
    BGM::Initialize();
    SE::Initialize();
}

void Sound::Release()
{
    BGM::Stop();
    for (auto bgm : bgmHandles)DeleteSoundMem(bgm.second);
    for (auto se : seHandles)DeleteSoundMem(se.second);
    bgmHandles.clear();
    seHandles.clear();
}

void Sound::SetMasterVolume(float vol)
{
    masterVolume = std::clamp(vol, 0.0f, 1.0f);
    BGM::ApplyVlume();
}

void Sound::SetBgmVolume(float vol)
{
    bgmVolume = std::clamp(vol, 0.0f, 1.0f);
    BGM::ApplyVlume();
}

void Sound::SetSeVolume(float vol)
{
    seVolume = std::clamp(vol, 0.0f, 1.0f);
}

int Sound::CalculateBgmVolume()
{
    int vol = static_cast<int>(255 * masterVolume * bgmVolume);
    return vol;
}

int Sound::CalculateSeVolume()
{
    int vol = static_cast<int>(255 * masterVolume * seVolume);
    return vol;
}

void Sound::BGM::Initialize()
{
    //ここで必要なBGMを読み込む
    //例：SetHandle("TitleBgm.mp3")
}

void Sound::BGM::Play(const std::string& file, bool loop)
{
    //もし同じBGMが再生中ならスルー
    if (currentBgm == file && CheckSoundMem(bgmHandles[file] == 1))return;

    Stop();

    auto bgm = bgmHandles.find(file);
    if (bgm == bgmHandles.end())return;
    currentBgm = file;
    ApplyVlume();
    int playType = loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
    PlaySoundMem(bgm->second, playType, TRUE);
}

void Sound::BGM::Stop()
{
    if (currentBgm.empty())return;
    auto bgm = bgmHandles.find(currentBgm);
    if (bgm == bgmHandles.end())return;
    StopSoundMem(bgm->second);
    currentBgm = "";
}

void Sound::BGM::ApplyVlume()
{
    if (currentBgm.empty())return;
    auto bgm = bgmHandles.find(currentBgm);
    if (bgm == bgmHandles.end())return;
    ChangeVolumeSoundMem(CalculateBgmVolume(), bgm->second);
}

void Sound::BGM::SetHandle(std::string file)
{
    std::string path;
    int handle = -1;
    path = "Assets/Sound/BGM/" + file + ".mp3";
    handle = LoadSoundMem(path.c_str());
    assert(handle > 0);
    bgmHandles[file + ".mp3"] = handle;
}

void Sound::SE::Initialize()
{
    //ここで必要なSEを読み込む
    //例：SetHandle("TitleSe.mp3")
}

void Sound::SE::Play(const std::string& file)
{
    auto se = seHandles.find(file);
    if (se == seHandles.end())return;
    ChangeVolumeSoundMem(CalculateSeVolume(), se->second);
    PlaySoundMem(se->second, DX_PLAYTYPE_BACK, TRUE);
}

void Sound::SE::SetHandle(std::string file)
{
    std::string path;
    int handle = -1;
    path = "Assets/Sound/SE/" + file + ".mp3";
    handle = LoadSoundMem(path.c_str());
    assert(handle > 0);
    seHandles[file + ".mp3"] = handle;
}
