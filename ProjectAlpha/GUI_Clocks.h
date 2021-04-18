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
	GUI_Clocks(): GUI_Element(GUIElementsEnum::GUI_CLOCKS) {};
	virtual ~GUI_Clocks() {};

	virtual void assignRes(vector<Texture>& uiResVec, std::vector<sf::Font>* fontsVec = nullptr, vector<Texture>* textureResVec = nullptr) override;

	// Recalculating format. Basically keeps numbers manipulating as time should -
	// only 59 minutes and 24 hours
	virtual bool update(IEC& iec, RenderWindow& window, View& view);

	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	// Needs for update() to be called after!!!
	void addMinutes(float minutes) { this->minutes += minutes; };

	void setPos(Vector2f pos) { timeText.setPosition(pos); };
	void setColor(Color color) { timeText.setFillColor(color); };

	Text* getTextObj() { return &timeText; };
	int getMinutesOverall() { return ((day * 24 * 60) + hours * 60 + minutes); };
};

