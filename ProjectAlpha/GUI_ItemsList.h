#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_ItemsListItem.h"
#include "Button.h"
#include "Storage.h"
#include "Slider.h"
#include "GUI_ItemsListItem.h"

class GUI_ItemsList
{
	vector<Texture> * resourcesVec;

	Sprite s_border;
	float fadeGap = 80;

	bool active = false;
	Button upListButton, downListButton;
	Slider slider;

	Font* guiFont1;
	Storage* assignedStorage;
	vector<GUI_ItemsListItem> itemsVec;
	float distanceBetweenItems = 2;
	float itemListLenght;
public:
	GUI_ItemsList();
	void load(vector<Texture>* texturesResourcesVec, Vector2f pos, Font* font);
	
	void assignStorage(Storage* storage);
	void moveItems(Vector2f factor);

	void update(IEC & iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void scrollUp();
	void scrollDown();
	void recalculateItemListLenght();
	Item deleteItem(float itemSizeY, Vector2f mousePos);
	void addItem(Item newItem);

	void setPosition(Vector2f pos);
	void setActive(bool active);
	void setPositionPercent(float percent);

	Sprite* getBorderSprite();
	Storage* getAssignedStorage();
	float getPositionPercent();
	bool isBorderIntersectsWithItem(int itemVectorIndex);

};

