#pragma once
#include<string>

namespace Model
{
	void Initialize();
	void Release();
	int Load(std::string fileKey);
	void SetHandle(std::string file);
}