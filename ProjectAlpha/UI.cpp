#include "UI.h"

UI::UI()
{	
}

void UI::load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font)
{
	this->texturesResourcesVec = texturesResourcesVec;
	guiFont1 = font;

	// Initializing local UI view
	view.setSize({ 1920, 1080 });
	view.setCenter(0, 0);

	// In-game clocks initializing
	clock.setPos({ -view.getSize().x / 2 , -view.getSize().y / 2 });
	
	// Items lists load() 
	inventoryItemsList.load(texturesResourcesVec,
		{ 40, -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);
	locationItemsList.load(texturesResourcesVec, 
		{ -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().x - 40, 
		-(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);

	// Backpack opening button initializing
	backpack_b.load("res/bagButton.png");
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ -backpack_b.getGlobalBounds().width / 2, view.getSize().y / 2 - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update();

	inventoryItemsList.update(iec, window, view);
	locationItemsList.update(iec, window, view);

	// If backpack button was clicked and player inventory is NOT opened
	// then
	// set item lists as active, so they can update() and draw() themselves
	if (backpack_b.update(iec, window, view) && !playerInventoryIsOpened)
	{
		inventoryItemsList.setActive(true);
		playerInventoryIsOpened = true;

		if (playerIsInsideLocation)
		{
			locationItemsList.setActive(true);
		}
	}

	// If RMB clicked and player is inside location
	// then
	// Basically logic for item swap from one item list to another
	if (iec._RMB && playerIsInsideLocation)
	{
		if (inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			inventoryItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item item = inventoryItemsList.deleteItem(texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view));
			locationItemsList.addItem(item);
			locationItemsList.getAssignedStorage()->addItem(item);
		}
		if (locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			locationItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item item = locationItemsList.deleteItem(texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view));
			inventoryItemsList.addItem(item);
			inventoryItemsList.getAssignedStorage()->addItem(item);

		}
	}

	// If LMB clicked and player inventory is opened
	// then
	// Basically logic for closing inventory windows(items lists) when clicked outside of
	// their sprite bounds
	if (iec._LMB && playerInventoryIsOpened)
	{
		if((!inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& !locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& playerIsInsideLocation) || (!inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& !playerIsInsideLocation))
		{
			inventoryItemsList.setActive(false);
			locationItemsList.setActive(false);
			playerInventoryIsOpened = false;
			iec._LMB = false;
		}
	}

}

void UI::draw(RenderWindow& window)
{
	// Temporary saving current view, to apply it back after 
	// drawing UI stuff in local UI view(see end of method)
	tempView = window.getView();

	window.setView(view);
	///////////////////////////

	clock.draw(window);

	inventoryItemsList.draw(window);
	locationItemsList.draw(window);

	backpack_b.draw(window);

	///////////////////////////

	// Applying saved view back, so further drawing logics of other modules
	// can't be ruined
	window.setView(tempView);
}

GUI_Clocks* UI::getClocks()
{
	return &clock;
}

GUI_ItemsList* UI::getInventoryItemList()
{
	return &inventoryItemsList;
}

GUI_ItemsList* UI::getLocationItemList()
{
	return &locationItemsList;
}


void UI::setPlayerInventoryIsOpened(bool isOpened)
{
	playerInventoryIsOpened = isOpened;
}

void UI::setPlayerIsInsideLocation(bool isInside)
{
	playerIsInsideLocation = isInside;
}

bool UI::getPlayerInventoryIsOpened()
{
	return playerInventoryIsOpened;
}
