#pragma once
#include "PrecompiledHeaders.h"

class Slider
{
	Sprite s_slider;
	Texture t_slider;

	// basePoint is upper start point(atm slider is only vertical)
	Vector2f basePoint, cursorOffset;
	float pathLenght= 100;
	bool grabbed = false;
public:
	Slider();
	void load(Vector2f basePoint, float pathLenght);

	// return TRUE when slider get moved
	bool update(IEC& iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void setPositionPercent(float percent);

	float getPositionPercent();
	Sprite* getS_slider();
};

