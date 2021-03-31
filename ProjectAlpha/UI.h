#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Clocks.h"
#include "GUI_ItemsList.h"
#include "GUI_IndicatorLine.h"
#include "GUI_ActionPanel.h"
#include"GUI_Button.h"


class UI
{
	/*Global textures storage reference to spread among object's load() functions*/
	vector<Texture>* texturesResourcesVec;

	/* Own view for objects, that should be aligned to center of the screen
	 and not to global world*/
	View view;

	/* Used to store and restore window view that disconnects when assigning UI's own 
	 view to the window to draw UI content*/
	View tempView;

	GUI_Clocks clock;

	GUI_ItemsList inventoryItemsList, locationItemsList;

	/*Player health, hunger, thirst, etc. gui indicators*/
	vector<GUI_IndicatorLine> indicatorsVec{ PLAYERSTATEINDICATORS_AMOUNT };

	bool playerInventoryIsOpened = false;
	bool playerIsInsideLocation = false;

	/* Button for opening backpack*/
	GUI_Button backpack_b;

	GUI_ActionPanel panel;

	/* Font reference to spread among object's load() functions(those who got drawable Text objects)*/
	Font* guiFont1;

public:
	UI();
	void load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font);
	//void getPlayerVarsPointers();
	void update(IEC& iec, RenderWindow& window);
	void draw(RenderWindow& window);

	void updatePlayerStatusLines(float health, float sleep, float temperature, float thirst, float hunger);

	/*movingFromList - list that will lose item
	movingToList - list that gain that item
	itemVecIndex - index of item in both GUI_ItemListItem and assignedStorage Item vectors of "movingFromList" list */
	void moveItemBetweenLists(GUI_ItemsList& movingFromList, GUI_ItemsList& movingToList, unsigned int itemVecIndex);

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

