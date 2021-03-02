#include "GUI_Clocks.h"

GUI_Clocks::GUI_Clocks()
{
	// Loading font and initializing 
	if (!font.loadFromFile("res/VintageOne.ttf")) cout << ">>>>>Font loading failed!" << endl;
	timeText.setFont(font);
	timeText.setCharacterSize(100);
	timeText.setScale({0.3, 0.3});
	timeText.setFillColor(sf::Color::Black);

	update();
}

void GUI_Clocks::update()
{
	//Forming dayStr, hoursStr and minutesStr,
	//keeping numbers legit for time displaying
	int difference;
	if (minutes >= 60) { difference = minutes - 60; hours++; minutes = 0 + difference; }
	if (hours >= 24) { hours = 0; day++; }

	if (hours < 10) hoursStr = "0" + to_string((int)hours); else hoursStr = to_string((int)hours);
	if (minutes < 10) minutesStr = "0" + to_string((int)minutes); else minutesStr = to_string((int)minutes);
	dayStr = "Day: " + to_string((int)day);
	
	str = dayStr + "\n" + hoursStr + " : " + minutesStr;
	timeText.setString(str);

}

void GUI_Clocks::draw(RenderWindow& window)
{
	window.draw(timeText);
}

void GUI_Clocks::addMinutes(float minutes)
{
	this->minutes += minutes;
}

void GUI_Clocks::setPos(Vector2f pos)
{
	timeText.setPosition(pos);
}
