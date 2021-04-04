#include "GUI_Clocks.h"

void GUI_Clocks::assignRes(vector<Texture>& uiResVec, std::vector<Font>* fontsVec, vector<Texture>* textureResVec)
{
	if (fontsVec)
	{
		timeText.setFont(fontsVec->at(UiFontsEnum::PIXELATED_3D_DEFAULT));
		timeText.setCharacterSize(100);
		timeText.setScale({ 0.3, 0.3 });
		timeText.setFillColor(sf::Color::Black);
		timeText.setString("00 : 00\nDay: 00000");
	}
}

bool GUI_Clocks::update(IEC& iec, RenderWindow& window, View& view)
{
	int difference;
	if (minutes >= 60) { difference = minutes - 60; hours++; minutes = 0 + difference; }
	if (hours >= 24) { hours = 0; day++; }

	if (hours < 10) hoursStr = "0" + to_string((int)hours); else hoursStr = to_string((int)hours);
	if (minutes < 10) minutesStr = "0" + to_string((int)minutes); else minutesStr = to_string((int)minutes);
	dayStr = "Day: " + to_string((int)day);

	str = dayStr + "\n" + hoursStr + " : " + minutesStr;
	timeText.setString(str);

	return false;
}

void GUI_Clocks::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(timeText);
}

void GUI_Clocks::addMinutes(float minutes)
{
	this->minutes += minutes;
}

void GUI_Clocks::setPos(Vector2f pos)
{
	timeText.setPosition(pos);
}

Text* GUI_Clocks::getTextObj()
{
	return &timeText;
}

int GUI_Clocks::getMinutesOverall()
{
	
	return ((day * 24 * 60) + hours * 60 + minutes);
}
