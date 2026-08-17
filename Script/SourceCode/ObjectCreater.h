#pragma once

class ObjectCreater
{
public:
	ObjectCreater();
	~ObjectCreater();
	void CreateObject();
private:
	int BASE_BLOCK;
	int BASE_OFFSET_Y;
private:
	void CreatePlayer();
	void CreateStageObject();
	void CreateBase();
};