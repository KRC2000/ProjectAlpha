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
	bool activated = false;
public:
	GUI_Button(UiResEnum buttonType = UiResEnum::MAINMENU_BUTTON_DEFAULT, string name = "Unnamed") :
		GUI_Element(GUIElementsEnum::GUI_BUTTON),
		name(name),
		buttonType(buttonType) {};

	virtual ~GUI_Button() {};

	virtual void assignRes(vector<Texture>& uiResVec, std::vector<sf::Font>* fontsVec = nullptr, vector<Texture>* textureResVec = nullptr) override;

	// Returns true when button was clicked
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;

	////////// SETTERS
	//
	void setScale(Vector2f factor) { spriteIdle.setScale(factor); };
	void setPosition(Vector2f pos) { spriteIdle.setPosition(pos); };
	//
	//////////////////

	////////// GETTERS
	//
	bool getIsActivated() { return activated; };
	FloatRect getGlobalBounds() { return spriteIdle.getGlobalBounds(); };
	string getName() { return name; };
	//
	//////////////////

};