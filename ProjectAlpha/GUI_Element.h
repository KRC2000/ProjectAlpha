#pragma once
#include "PrecompiledHeaders.h"
#include "UiResEnum.h"

class GUI_Element: public Drawable
{
	string name;
	GUIElementsEnum guiType;
protected: GUI_Element* owner = nullptr;
public:
	GUI_Element(GUIElementsEnum guiType, GUI_Element* owner = nullptr):guiType(guiType), owner(owner) {};
	virtual ~GUI_Element() {};

	// Must be overloaded
	//
	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) {};
	virtual bool update(IEC& iec, RenderWindow& window, View& view) { return false; };
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override { cout << "you drew nothing!\n"; };
	virtual FloatRect getGlobalElementBounds() { return { 0, 0, 0, 0 }; };
	//
	//////////////////////

	const GUIElementsEnum getType() { return guiType; };
	const string getName() { return name; };
	void setName(string newName) { name = newName; };
};

