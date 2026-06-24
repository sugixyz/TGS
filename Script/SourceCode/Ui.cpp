#include "Ui.h"

namespace
{
	int currentId = 0;
	int fontSize = 0;
	const Vector2 DRAW_POS = { WIN_WIDTH / 2, 50 };
	const float OFFSET_Y = 40.0f;
}


Ui::Ui(const std::string& str, const int* val, unsigned int col)
	:GameObject(Tag::UI), title(str), intVal(val), floatVal(nullptr), color(col)
{
	if (FindTagObjects(Tag::UI).size() == 1)
	{
		fontSize = GetFontSize();
		currentId = 0;
	}

	id = currentId;
	currentId++;

}

Ui::Ui(const std::string& str, const float* val, unsigned int col)
	:GameObject(Tag::UI), title(str), intVal(nullptr), floatVal(val), color(col)
{
	if (FindTagObjects(Tag::UI).size() == 1)
	{
		fontSize = GetFontSize();
		currentId = 0;
	}

	id = currentId;
	currentId++;
}

Ui::Ui(const std::string& str, unsigned int col)
	:GameObject(Tag::UI), title(str), intVal(nullptr), floatVal(nullptr), color(col)
{
	if (FindTagObjects(Tag::UI).size() == 1)
	{
		fontSize = GetFontSize();
		currentId = 0;
	}

	id = currentId;
	currentId++;
}

Ui::~Ui()
{}

void Ui::Draw()
{
	float x = DRAW_POS.x;
	float y = DRAW_POS.y + (fontSize + OFFSET_Y) * id;
	if (intVal != nullptr)
	{
		DrawFormatString((int)x, (int)y, color, "%s %d", title.c_str(), *intVal);
	}
	else if (floatVal != nullptr)
	{
		DrawFormatString((int)x, (int)y, color, "%s %f", title.c_str(), *floatVal);
	}
	else
	{
		DrawFormatString((int)x, (int)y, color, "%s", title.c_str());
	}
}
