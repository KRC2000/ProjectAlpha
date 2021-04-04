#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"
#include "UiResEnum.h"

using namespace sf;
using namespace std;

class GUI_Button: public GUI_Element
{
private:
	Texture* t;
	UiResEnum buttonType;
	Sprite spriteIdle;
	string name = "Unnamed";
public:
	GUI_Button(UiResEnum buttonType = UiResEnum::MAINMENU_BUTTON_DEFAULT, string name = "Unnamed");
	virtual ~GUI_Button() {};

	virtual void assignRes(vector<Texture>& uiResVec, std::vector<sf::Font>* fontsVec = nullptr) override;

	// Returns true when button was clicked
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;

	////////// SETTERS
	//
	void setScale(Vector2f factor);
	void setPosition(Vector2f pos);
	//
	//////////////////

	////////// GETTERS
	//
	FloatRect getGlobalBounds();
	string getName();
	//
	//////////////////

};