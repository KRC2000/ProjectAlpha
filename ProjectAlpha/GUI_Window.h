#pragma once
#include "PrecompiledHeaders.h"
#include "GuiElementsContainer.h"
#include "GUI_Element.h"
#include "GUI_Button.h"

class GUI_Window :	public GUI_Element,
					public GuiElementsContainer
{
	// Size of a canvas without borders and corners, "empty" space size
	Vector2f backgrSize{ 800, 600 };
	Vector2f pos{ 300, 0 };
	int borderSize = 0;
	bool active = false;

	View windowView;
	//View* uiView = nullptr;

	enum class WindowSegments
	{
		UPLEFT_C, UPRIGHT_C, DOWNRIGHT_C, DOWNLEFT_C,
		UP, DOWN, LEFT, RIGHT, BACKGR, 
		AMOUNT
	};

	vector<Sprite> sVec;

	//vector<GUI_Element*> elementsVec;

public:
	GUI_Window();
	virtual ~GUI_Window() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) override;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	void viewportUpdate(View uiView);

	// SETTERS //////////////////

	void setPos(Vector2f newPos);
	void setActive(bool isActive) { active = isActive; };

	/////////////////////////////
};

