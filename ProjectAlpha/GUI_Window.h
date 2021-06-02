#pragma once
#include "PrecompiledHeaders.h"
#include "GuiElementsContainer.h"
#include "GUI_Element.h"
#include "GUI_Button.h"
#include "GUI_Slider.h"
#include "GUI_RenderTextureContainer.h"
#include "GUI_Interactable.h"

class GUI_Window :	public GUI_Element,
					public GUI_RenderTextureContainer,
					public GUI_Interactable,
					public GuiElementsContainer
{
	// Size of a canvas without borders and corners, but with buttons and scrollers
	Vector2f backgrSize{ 600, 700 };
	Vector2f pos{ 300, 0 };
	Vector2f grabOffset{};
	// Width and height of minimal rectangle that includes all elements
	Vector2f contentOccupySize{ 0, 0 };
	Vector2f defaultViewPos{};
	int borderSize = 0;
	int rightSideGap = 33 + 5;
	bool beingScrolled = false;
	bool grabbed = false;
	bool resized = false;

	View rtView;
	RenderTexture rt;
	Sprite rts;

	GUI_Button b_close{ UiResEnum::BUTTON_CLOSE };
	GUI_Button b_up{ UiResEnum::BUTTON_UP };
	GUI_Button b_down{ UiResEnum::BUTTON_DOWN };
	GUI_Slider slider;


	// Window sprite-segments names
	enum class WindowSegments
	{
		UPLEFT_C, UPRIGHT_C, DOWNRIGHT_C, DOWNLEFT_C,
		UP, DOWN, LEFT, RIGHT, BACKGR, 
		AMOUNT
	};

	vector<Sprite> sVec;
private:
	//void viewportUpdate(View uiView);
	void recalculateContentOccupySize();
public:
	GUI_Window(GUI_Element* owner = nullptr);
	virtual ~GUI_Window() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) override;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;


	// SETTERS //////////////////
	//
	void setPos(Vector2f newPos);
	//void setActive(bool isActive) { active = isActive; };
	void setSize(Vector2f newSize);
	//
	/////////////////////////////

	// GETTERS //////////////////
	//
	virtual FloatRect getGlobalElementBounds() override;
	Vector2f getContentOccupySize() { return contentOccupySize; };
	//
	/////////////////////////////

private:
	void normalizeOutOfBoundsView();
	float getVerticalPosPercent();
	void setVerticalPosPercent(float percent);
};

