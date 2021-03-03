#include "GUI_IndicatorLine.h"

GUI_IndicatorLine::GUI_IndicatorLine()
{
}

void GUI_IndicatorLine::load(Texture* t)
{
	this->t = t;
	this->t->setRepeated(true);
	stamp.setTexture(*t);
}

void GUI_IndicatorLine::update()
{
	if (currentValue < 0) currentValue = 0;
	if (currentValue > maxValue) currentValue = maxValue;


	lengthCost = maxValue / maxLength;
	currentLength = currentValue / lengthCost;
}

void GUI_IndicatorLine::draw(RenderWindow& window)
{
	stamp.setTextureRect(IntRect(0, t->getSize().y / 2, (t->getSize().x / 4) / 2, t->getSize().y / 2));
	stamp.setPosition(pos);
	window.draw(stamp);

	if (currentLength > t->getSize().x / 4)
	{
		stamp.setTextureRect(IntRect(0, 0, currentLength - t->getSize().x / 4, t->getSize().y / 2));
		stamp.setPosition({ pos.x + (t->getSize().x / 4) / 2, pos.y });
		window.draw(stamp);
	}

	stamp.setTextureRect(IntRect((t->getSize().x / 4) / 2, t->getSize().y / 2, (t->getSize().x / 4) / 2, t->getSize().y / 2));
	if (currentLength > t->getSize().x / 4) stamp.setPosition({pos.x + (t->getSize().x / 4) / 2 + (currentLength - t->getSize().x / 4), pos.y});
	else stamp.setPosition({ pos.x + (t->getSize().x / 4) / 2, pos.y });
	window.draw(stamp);
}

void GUI_IndicatorLine::setPos(Vector2f newPos)
{
	pos = newPos;
}

void GUI_IndicatorLine::setValue(float value)
{
	currentValue = value;
	update();
}

void GUI_IndicatorLine::increaseValue(float value)
{
	currentValue += value;
	update();
}

void GUI_IndicatorLine::setMaxLength(int newMaxLength)
{
	maxLength = newMaxLength;
	update();
}

void GUI_IndicatorLine::setMaxValue(float newMaxValue)
{
	maxValue = newMaxValue;
	update();
}

float GUI_IndicatorLine::getValue()
{
	return currentValue;
}

float GUI_IndicatorLine::getMaxValue()
{
	return maxValue;
}
