#include "UI.h"

UI::UI()
{
	//view.zoom(3.f);
	//view.setCenter({1500, 1500});
	
}

void UI::load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font)
{
	this->texturesResourcesVec = texturesResourcesVec;
	view.setSize({ 1920, 1080 });
	view.setCenter(0, 0);

	clock.setPos({ -view.getSize().x / 2 , -view.getSize().y / 2 });
	
	guiFont1 = font;

	inventoryItemsList.load(texturesResourcesVec,
		{ 40, -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);
	locationItemsList.load(texturesResourcesVec, 
		{ -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().x - 40, 
		-(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);

	

	backpack_b.load("res/bagButton.png");
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ -backpack_b.getGlobalBounds().width / 2, view.getSize().y / 2 - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update(1);
	inventoryItemsList.update(iec, window, view);
	locationItemsList.update(iec, window, view);

	if (backpack_b.update(iec, window, view) && !playerInventoryIsOpened)
	{
		inventoryItemsList.setActive(true);
		playerInventoryIsOpened = true;
		if (playerIsInsideLocation)
		{
			locationItemsList.setActive(true);
		}
	}


	if (iec._RMB && playerIsInsideLocation)
	{
		if (inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			inventoryItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item item = inventoryItemsList.deleteItem(texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view));
			locationItemsList.addItem(item);
		}
		if (locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			locationItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item item = locationItemsList.deleteItem(texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view));
			inventoryItemsList.addItem(item);
		}
	}

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
	temp = window.getView();
	window.setView(view);
	///////////////////////////

	clock.draw(window);

	inventoryItemsList.draw(window);
	locationItemsList.draw(window);

	backpack_b.draw(window);

	///////////////////////////
	window.setView(temp);
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
