#include "GUI_IndicatorLine.h"

GUI_IndicatorLine::GUI_IndicatorLine()
{
}

void GUI_IndicatorLine::load(Texture* t)
{
	t_line = t;
	t_line->setRepeated(true);

	s_line.setTexture(*t_line);

}

void GUI_IndicatorLine::setPictureTitle(Texture* t, IntRect rect)
{
	pictureTitle = true;
	t_pic = t;
	pictureRect = rect;

	s_picture.setTexture(*t_pic);
	s_picture.setTextureRect(pictureRect);
	s_picture.setScale({ 0.5, 0.5 });
	s_picture.setPosition({ pos.x - s_picture.getGlobalBounds().width,
			pos.y - s_picture.getGlobalBounds().height / 2 + t_line->getSize().y / 4 });
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
	if (pictureTitle)
	{
		window.draw(s_picture);
	}

	
	s_line.setTextureRect(IntRect(0, t_line->getSize().y / 2, (t_line->getSize().x / 4) / 2, t_line->getSize().y / 2));
	s_line.setPosition(pos);
	window.draw(s_line);

	if (currentLength > t_line->getSize().x / 4)
	{
		s_line.setTextureRect(IntRect(0, 0, currentLength - t_line->getSize().x / 4, t_line->getSize().y / 2));
		s_line.setPosition({ pos.x + (t_line->getSize().x / 4) / 2, pos.y });
		window.draw(s_line);
	}

	s_line.setTextureRect(IntRect((t_line->getSize().x / 4) / 2, t_line->getSize().y / 2, (t_line->getSize().x / 4) / 2, t_line->getSize().y / 2));
	if (currentLength > t_line->getSize().x / 4) s_line.setPosition({pos.x + (t_line->getSize().x / 4) / 2 + (currentLength - t_line->getSize().x / 4), pos.y});
	else s_line.setPosition({ pos.x + (t_line->getSize().x / 4) / 2, pos.y });
	window.draw(s_line);
}

void GUI_IndicatorLine::setPos(Vector2f newPos)
{
	pos = newPos;
	s_picture.setPosition({ pos.x - s_picture.getGlobalBounds().width,
			pos.y - s_picture.getGlobalBounds().height / 2 + t_line->getSize().y / 4 });
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

Sprite* GUI_IndicatorLine::getPictureSprite()
{
	return &s_picture;
}
