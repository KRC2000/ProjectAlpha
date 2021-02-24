#pragma once
#include "PrecompiledHeaders.h"

class GUI_ItemsListItem
{
	Sprite boxSprite;
	Text itemNameText, amountText, conditionText;
	//Font f;

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
	void setTransparencyFade(int percent);
	void increaseTransparencyFade(int percent);

	int getAlpha();
	Sprite* getSpriteBox();

private:
	string getItemNameString(ItemsEnum itemId);
};

