#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"

class GUI_Window : public GUI_Element
{
	// Size of a canvas without borders and corners, "empty" space size
	Vector2f backgrSize{ 800, 600 };
	Vector2f pos{ 0, 0 };
	int borderSize = 0;
	bool active = false;

	enum class WindowSegments
	{
		UPLEFT_C, UPRIGHT_C, DOWNRIGHT_C, DOWNLEFT_C,
		UP, DOWN, LEFT, RIGHT, BACKGR, 
		AMOUNT
	};

	vector<Sprite> sVec;

	vector<GUI_Element*> elementsVec;

public:
	GUI_Window();
	virtual ~GUI_Window() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr);
	virtual bool update(IEC& iec, RenderWindow& window, View& view) { return false; };
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	// SETTERS //////////////////

	void setPos(Vector2f newPos);

	/////////////////////////////
};

