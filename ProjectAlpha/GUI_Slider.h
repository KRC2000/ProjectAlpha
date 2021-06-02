#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"
#include "GUI_Interactable.h"
#include "UiResEnum.h"

class GUI_Slider:	public GUI_Element,
					public GUI_Interactable
{
	Sprite s_slider;
	Texture t_slider;

	// basePoint is upper start point(atm GUI_Slider is only vertical)
	Vector2f basePoint, cursorOffset;
	float pathLenght= 100;
	bool grabbed = false;
public:
	GUI_Slider(): GUI_Element(GUIElementsEnum::GUI_SLIDER) {};
	virtual ~GUI_Slider() {};


	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) override;
	// Returns true when scrolled
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	void setPositionPercent(float percent);
	void setPosition(Vector2f newPos);
	void setPathLenght(float pathLenght) { this->pathLenght = pathLenght - s_slider.getGlobalBounds().height; };
	
	float getPositionPercent();
	Sprite* getS_slider();
};

