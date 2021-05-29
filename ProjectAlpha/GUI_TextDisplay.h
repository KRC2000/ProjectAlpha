#pragma once
#include "GUI_Element.h"
#include "UiFontsEnum.h"

class GUI_TextDisplay :public GUI_Element
{
	View windowView;
	bool active = false;

	Text text;
	RectangleShape boundsRectShape{ {400, 200} };
public:
	GUI_TextDisplay();
	virtual ~GUI_TextDisplay() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr);
	virtual bool update(IEC& iec, RenderWindow& window, View& view);
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	// SETTERS //////////////////
	//
	//void setPos(Vector2f newPos);
	void setActive(bool isActive) { active = isActive; };
	//
	/////////////////////////////

	// GETTERS //////////////////
	//
	virtual FloatRect getGlobalElementBounds() override;
	//
	/////////////////////////////
};

