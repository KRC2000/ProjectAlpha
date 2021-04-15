#pragma once
#include "PrecompiledHeaders.h"

class GUI_Element: public Drawable
{
	string name;
	GUIElementsEnum guiType;
public:
	GUI_Element(GUIElementsEnum guiType):guiType(guiType) {};
	virtual ~GUI_Element() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) {};
	virtual bool update(IEC& iec, RenderWindow& window, View& view) { return false; };
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override {};
	const GUIElementsEnum getType() { return guiType; };
	const string getName() { return name; };
	void setName(string newName) { name = newName; };
};

