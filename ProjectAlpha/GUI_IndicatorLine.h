#pragma once
//#include"PrecompiledHeaders.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourcesEnum.h"
#include "GUI_Element.h"
using namespace sf;
using namespace std;

class GUI_IndicatorLine: public GUI_Element
{
	Sprite s_lineHead, s_lineBody, s_lineTail;
	Sprite s_picture;
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

	virtual void assignTextureRes(vector<sf::Texture>& textureResourcesVec) override;

	void setPictureTitle(Texture* t, IntRect rect);
	//void update();
	//void draw(RenderWindow& window);

	virtual void draw(RenderTarget& target, RenderStates states) const override;

	void increaseValue(float value);

	void setPos(Vector2f newPos);
	void setValue(float value);
	void setMaxLength(int newMaxLength);
	void setMaxValue(float newMaxValue);

	float getValue();
	float getMaxValue();
	Sprite* getPictureSprite();

private:
	void update();
};

