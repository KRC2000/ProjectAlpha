#include "UI.h"

UI::UI()
{	
}

void UI::load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font)
{
	this->texturesResourcesVec = texturesResourcesVec;
	guiFont1 = font;

	// Initializing local UI view
	//view.setSize({ 1920, 1080 });
	view.setSize({ (float)window.getSize().x, (float)window.getSize().y });
	//view.setSize({ 2000, 1800});
	view.setCenter(view.getSize().x/2, view.getSize().y / 2);

	healthLine.load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	sleepLine.load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	temperatureLine.load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	thirstLine.load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	hungerLine.load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	
	healthLine.setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), {100 * 0, 0, 100, 100});
	sleepLine.setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), {100 * 1, 0, 100, 100});
	temperatureLine.setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 2, 0, 100, 100});
	thirstLine.setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 3, 0, 100, 100});
	hungerLine.setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 4, 0, 100, 100});
	
	healthLine.setPos({ healthLine.getPictureSprite()->getGlobalBounds().width, clock.getTextObj()->getGlobalBounds().height + 30});
	sleepLine.setPos({ healthLine.getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 1 * healthLine.getPictureSprite()->getGlobalBounds().height});
	temperatureLine.setPos({ temperatureLine.getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 2 * healthLine.getPictureSprite()->getGlobalBounds().height });
	thirstLine.setPos({ thirstLine.getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 3 * healthLine.getPictureSprite()->getGlobalBounds().height });
	hungerLine.setPos({ hungerLine.getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 4 * healthLine.getPictureSprite()->getGlobalBounds().height });

	// In-game clocks initializing
	clock.setPos({ 0 , 0 });
	
	// Items lists load() 
	inventoryItemsList.load(texturesResourcesVec,
		{ view.getSize().x / 2 + 40, view.getSize().y / 2 -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);
	locationItemsList.load(texturesResourcesVec, 
		{ view.getSize().x / 2 -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().x - 40, 
		view.getSize().y / 2 - (float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);

	// Backpack opening button initializing
	backpack_b.load("res/bagButton.png");
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ view.getSize().x /2 - backpack_b.getGlobalBounds().width / 2, view.getSize().y - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update();
	//line.update();

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
			Item tempItem;
			if (inventoryItemsList.deleteItem(&tempItem, texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view)))
			{
				locationItemsList.addItem(tempItem);
				locationItemsList.getAssignedStorage()->addItem(tempItem);
			}
		}
		if (locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			locationItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item tempItem;
			if (locationItemsList.deleteItem(&tempItem, texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view)))
			{
				inventoryItemsList.addItem(tempItem);
				inventoryItemsList.getAssignedStorage()->addItem(tempItem);
			}

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

	healthLine.draw(window);
	sleepLine.draw(window);
	temperatureLine.draw(window);
	thirstLine.draw(window);
	hungerLine.draw(window);

	backpack_b.draw(window);

	///////////////////////////

	// Applying saved view back, so further drawing logics of other modules
	// can't be ruined
	window.setView(tempView);
}

void UI::updatePlayerStatusLines(float health, float sleep, float temperature, float thirst, float hunger)
{
	healthLine.setValue(health);
	sleepLine.setValue(sleep);
	temperatureLine.setValue(temperature);
	thirstLine.setValue(thirst);
	hungerLine.setValue(hunger);
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
