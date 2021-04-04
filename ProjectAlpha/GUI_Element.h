#pragma once
#include "PrecompiledHeaders.h"


class GUI_Element: public Drawable
{
public:
	GUI_Element() {};
	virtual ~GUI_Element() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) = 0;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) = 0;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override = 0;
};

