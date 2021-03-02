#pragma once
#include "PrecompiledHeaders.h"

class GUI_ItemsListItem
{
	Sprite boxSprite;
	Text itemNameText, amountText, conditionText;

	Clock fadeTimer;

	ItemsEnum itemId;
	int amount, condition;
	bool reusable;
	
public:
	GUI_ItemsListItem(ItemsEnum itemId, int amount, bool reusable, int condition);
	void load(vector<Texture>& textureResourcesVec, Font * font);
	void fadeIn();
	void fadeOut();
	void update(IEC& iec);
	void draw(RenderWindow& window);

	void setPos(Vector2f pos);
	void move(Vector2f vector);

	// Basically sets alpha RGBA component, but in percents
	void setTransparencyFade(int percent);

	// Basically increments alpha RGBA component, but in percents
	void increaseTransparencyFade(int percent);

	int getAlpha();
	Sprite* getSpriteBox();

private:
	string getItemNameString(ItemsEnum itemId);
};

