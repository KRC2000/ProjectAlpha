#include "GUI_IndicatorLine.h"

void GUI_IndicatorLine::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* textureResVec)
{
	t_line = &uiResVec[(int)UiResEnum::GUI_INDICATORLINE];
	t_line->setRepeated(true);

	text.setFont(fontsVec->at((int)UiFontsEnum::SPECIALELITE));
	text.setCharacterSize(15);

	s_lineHead.setTexture(*t_line);
	s_lineBody.setTexture(*t_line);
	s_lineTail.setTexture(*t_line);
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

void GUI_IndicatorLine::draw(RenderTarget& target, RenderStates states) const
{
	if (pictureTitle)
	{
		target.draw(s_picture);
	}

	target.draw(s_lineHead);

	if (currentLength > t_line->getSize().x / 4)
		target.draw(s_lineBody);
	
	target.draw(s_lineTail);

	if (textEnabled) target.draw(text);
}

void GUI_IndicatorLine::setPos(Vector2f newPos)
{
	pos = newPos;
	s_picture.setPosition({ pos.x - s_picture.getGlobalBounds().width,
			pos.y - s_picture.getGlobalBounds().height / 2 + t_line->getSize().y / 4 });
	update();
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

void GUI_IndicatorLine::update()
{
	if (currentValue < 0) currentValue = 0;
	if (currentValue > maxValue) currentValue = maxValue;

	lengthCost = maxValue / maxLength;
	currentLength = currentValue / lengthCost;

	text.setString(to_string((int)currentValue));

	s_lineHead.setTextureRect(IntRect(0, t_line->getSize().y / 2, (t_line->getSize().x / 4) / 2, t_line->getSize().y / 2));
	s_lineHead.setPosition(pos);

	if (currentLength > t_line->getSize().x / 4)
	{
		s_lineBody.setTextureRect(IntRect(0, 0, currentLength - t_line->getSize().x / 4, t_line->getSize().y / 2));
		s_lineBody.setPosition({ pos.x + (t_line->getSize().x / 4) / 2, pos.y });
	}

	s_lineTail.setTextureRect(IntRect((t_line->getSize().x / 4) / 2, t_line->getSize().y / 2, (t_line->getSize().x / 4) / 2, t_line->getSize().y / 2));
	if (currentLength > t_line->getSize().x / 4) s_lineTail.setPosition({ pos.x + (t_line->getSize().x / 4) / 2 + (currentLength - t_line->getSize().x / 4), pos.y });
	else s_lineTail.setPosition({ pos.x + (t_line->getSize().x / 4) / 2, pos.y });

	text.setPosition(s_lineTail.getPosition().x + s_lineTail.getGlobalBounds().width, s_lineTail.getPosition().y);
}
