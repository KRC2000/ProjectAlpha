#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"

class GUI_Window : public GUI_Element
{

public:
	GUI_Window() :GUI_Element(GUIElementsEnum::GUI_WINDOW) {};
	virtual ~GUI_Window() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr);
	virtual bool update(IEC& iec, RenderWindow& window, View& view) { return false; };
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override { cout << "you drew nothing!\n"; };
};

