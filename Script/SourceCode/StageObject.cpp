#include "StageObject.h"

StageObject::StageObject(Vector3 pos, Vector3 rot, Vector3 sca, int id)
	:GameObject(Tag::STAGE)
{
	position3 = pos;
	rotation3 = rot;
	scale3 = sca;
	objId = id;
}

StageObject::~StageObject()
{}

void StageObject::Draw()
{
	if (objId == 1)
	{
		float x = position3.x;
		float y = position3.y;
		DrawBox(x, y, x + WIN_WIDTH, y + WIN_HEIGHT / 2,GetColor(0,100,0), TRUE);
	}
	else if (objId == 2)
	{
		float x = position3.x;
		float y = position3.y;
		DrawBox(x, y, x + WIN_WIDTH, y + WIN_HEIGHT / 2 +36, COL_GRAY, TRUE);
	}
}
