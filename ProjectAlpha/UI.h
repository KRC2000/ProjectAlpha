#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Clocks.h"
#include "GUI_ItemsList.h"
#include"Button.h"

class UI
{
	vector<Texture>* texturesResourcesVec;

	View view, temp;
	GUI_Clocks clock;
	GUI_ItemsList inventoryItemsList, locationItemsList;

	bool playerInventoryIsOpened = false;
	bool playerIsInsideLocation = false;
	Button backpack_b;

	Font* guiFont1;
public:
	UI();
	void load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font);
	void update(IEC& iec, RenderWindow& window);
	void draw(RenderWindow& window);

	
	void setPlayerInventoryIsOpened(bool isOpened);
	void setPlayerIsInsideLocation(bool isInside);

	
	bool getPlayerInventoryIsOpened();
	GUI_Clocks* getClocks();
	GUI_ItemsList* getInventoryItemList();
	GUI_ItemsList* getLocationItemList();
};

