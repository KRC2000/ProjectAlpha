#pragma once
#include"PrecompiledHeaders.h"
#include "UiResEnum.h"
#include "UiFontsEnum.h"
#include "GUI_Element.h"

using namespace sf;
using namespace std;

class GUI_IndicatorLine: public GUI_Element
{
	Sprite s_lineHead, s_lineBody, s_lineTail;
	Sprite s_picture;
	Texture* t_line = nullptr, *t_pic = nullptr;
	Text text;
	IntRect pictureRect;

	bool pictureTitle = false;
	bool textEnabled = true;

	Vector2f pos{0, 0};

	int maxLength = 100;
	float currentValue = 0;
	float maxValue = 100;
	float lengthCost = maxValue / maxLength;
	int currentLength = currentValue / lengthCost;

public:
	GUI_IndicatorLine(): GUI_Element(GUIElementsEnum::GUI_INDICATORLINE) {};
	virtual ~GUI_IndicatorLine() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* textureResVec = nullptr) override;

	void setPictureTitle(Texture* t, IntRect rect);
	//void update();
	//void draw(RenderWindow& window);
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override { return false; };


	virtual void draw(RenderTarget& target, RenderStates states) const override;

	void increaseValue(float value);

	void setPos(Vector2f newPos);
	void setValue(float value);
	void setMaxLength(int newMaxLength);
	void setMaxValue(float newMaxValue);
	void setTextVisibility(bool visibility) { textEnabled = visibility; };

	float getValue() { return currentValue; };
	float getMaxValue() { return maxValue; };
	Sprite* getPictureSprite() { return &s_picture; };

private:
	void update();
};

