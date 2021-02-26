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

	// Recalculating format. Basically keeps numbers manipulating as time should -
	// only 59 minutes and 24 hours
	void update();

	void draw(RenderWindow& window);

	// Needs for update() to be called after!!!
	void addMinutes(float minutes);

	void setPos(Vector2f pos);
};

