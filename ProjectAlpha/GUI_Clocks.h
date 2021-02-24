#pragma once
#include "PrecompiledHeaders.h"

class GUI_Clocks
{
	Font font;
	Text timeText;
	float hours = 14, minutes = 0, day = 0;
	string str, hoursStr, minutesStr, dayStr;
	
public:
	GUI_Clocks();
	void update(float factor);
	void draw(RenderWindow& window);
	void addMinutes(float minutes);
	void setPos(Vector2f pos);
};

