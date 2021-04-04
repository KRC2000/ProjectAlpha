#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"
#include "UiFontsEnum.h"

class GUI_Clocks: public GUI_Element
{
	
	Text timeText;
	float hours = 14, minutes = 0, day = 0;
	string str, hoursStr, minutesStr, dayStr;

	
public:
	GUI_Clocks() {};
	virtual ~GUI_Clocks() {};

	virtual void assignRes(vector<Texture>& uiResVec, std::vector<sf::Font>* fontsVec = nullptr) override;

	// Recalculating format. Basically keeps numbers manipulating as time should -
	// only 59 minutes and 24 hours
	virtual bool update(IEC& iec, RenderWindow& window, View& view);

	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	// Needs for update() to be called after!!!
	void addMinutes(float minutes);

	void setPos(Vector2f pos);

	Text* getTextObj();
	int getMinutesOverall();
};

