#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Clocks.h"
#include "GUI_ItemsList.h"
#include"Button.h"


class UI
{
	// Global textures storage reference to spread among object's load() functions
	vector<Texture>* texturesResourcesVec;

	// Own view for objects, that should be aligned to center of the screen
	// and not to global world
	View view;

	// Used to store and restore window view that disconnects when assigning UI's own 
	// view to the window to draw UI content
	View tempView;

	GUI_Clocks clock;

	GUI_ItemsList inventoryItemsList, locationItemsList;

	bool playerInventoryIsOpened = false;
	bool playerIsInsideLocation = false;

	// Button for opening backpack
	Button backpack_b;

	// Font reference to spread among object's load() functions(those who got drawable Text objects)
	Font* guiFont1;

public:
	UI();
	void load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font);
	void update(IEC& iec, RenderWindow& window);
	void draw(RenderWindow& window);

	////////// SETTERS

	void setPlayerInventoryIsOpened(bool isOpened);
	void setPlayerIsInsideLocation(bool isInside);

	//////////////////

	////////// GETTERS

	bool getPlayerInventoryIsOpened();
	GUI_Clocks* getClocks();
	GUI_ItemsList* getInventoryItemList();
	GUI_ItemsList* getLocationItemList();

	//////////////////

	// Functions for use only inside the class
private:

};

