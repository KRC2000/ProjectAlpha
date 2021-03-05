#pragma once
#include"PrecompiledHeaders.h"

class GUI_IndicatorLine
{
	Sprite s_line, s_picture;
	Texture* t_line, *t_pic;

	IntRect pictureRect;

	bool pictureTitle = false;

	Vector2f pos{0, 0};
	int maxLength = 100;
	float currentValue = 0;
	float maxValue = 100;
	float lengthCost = maxValue / maxLength;
	int currentLength = currentValue / lengthCost;

public:
	GUI_IndicatorLine();
	void load(Texture* t);
	void setPictureTitle(Texture* t, IntRect rect);
	void update();
	void draw(RenderWindow& window);
	void increaseValue(float value);

	void setPos(Vector2f newPos);
	void setValue(float value);
	void setMaxLength(int newMaxLength);
	void setMaxValue(float newMaxValue);

	float getValue();
	float getMaxValue();
	Sprite* getPictureSprite();
};

