#include "StageObject.h"
#include"../Engine/Tool/Model.h"

StageObject::StageObject(VECTOR pos, VECTOR rot, VECTOR sca, int id)
	:GameObject(Tag::STAGE)
{
	position3 = pos;
	rotation3 = rot;
	scale3 = sca;
	objId = id;

	char file[30];
	sprintf_s(file, sizeof(file), "StageObject%02d.mv1", id);
	hModel = Model::Load(file);
	assert(hModel > 0);
}

StageObject::~StageObject()
{
	MV1DeleteModel(hModel);
}

void StageObject::Draw()
{
	if (mode == DEBUG || mode == DOUBLE_MODE)
	{
		if (objId == 1)
		{
			float x = position3.x;
			float y = position3.y;
			DrawBoxAA(x, y, x + WIN_WIDTH, y + WIN_HEIGHT / 2,GetColor(0,100,0), TRUE);
		}
		else if (objId == 2)
		{
			float x = position3.x;
			float y = position3.y;
			DrawBoxAA(x, y, x + WIN_WIDTH, y + WIN_HEIGHT / 2 +36, COL_GRAY, TRUE);
		}
	}

	if (mode == NORMAL || mode == DOUBLE_MODE)
	{
		DrawModel();
	}
}
