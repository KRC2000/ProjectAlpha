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


	indicatorsVec[HEALTH].load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	indicatorsVec[SLEEP].load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	indicatorsVec[TEMPERATURE].load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	indicatorsVec[THIRST].load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	indicatorsVec[HUNGER].load(&texturesResourcesVec->at(ResourcesEnum::INDICATORLINE_T));
	
	indicatorsVec[HEALTH].setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), {100 * 0, 0, 100, 100});
	indicatorsVec[SLEEP].setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), {100 * 1, 0, 100, 100});
	indicatorsVec[TEMPERATURE].setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 2, 0, 100, 100});
	indicatorsVec[THIRST].setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 3, 0, 100, 100});
	indicatorsVec[HUNGER].setPictureTitle(&texturesResourcesVec->at(ResourcesEnum::STATUSICONS_T), { 100 * 4, 0, 100, 100});
	
	indicatorsVec[HEALTH].setPos({ indicatorsVec[HEALTH].getPictureSprite()->getGlobalBounds().width, clock.getTextObj()->getGlobalBounds().height + 30});
	indicatorsVec[SLEEP].setPos({ indicatorsVec[SLEEP].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 1 * indicatorsVec[SLEEP].getPictureSprite()->getGlobalBounds().height});
	indicatorsVec[TEMPERATURE].setPos({ indicatorsVec[TEMPERATURE].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 2 * indicatorsVec[TEMPERATURE].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[THIRST].setPos({ indicatorsVec[THIRST].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 3 * indicatorsVec[THIRST].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[HUNGER].setPos({ indicatorsVec[HUNGER].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 4 * indicatorsVec[HUNGER].getPictureSprite()->getGlobalBounds().height });

	// In-game clocks initializing
	clock.setPos({ 0 , 0 });
	
	panel.load(*texturesResourcesVec);
	panel.addActionButton("res/info.png", "info");
	panel.addActionButton("res/hand.png", "use");
	panel.addActionButton("res/eating.png", "eat");
	panel.setActive(true);


	// Items lists load() 
	inventoryItemsList.load(texturesResourcesVec,
		{ view.getSize().x / 2 + 40, view.getSize().y / 2 -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);
	locationItemsList.load(texturesResourcesVec, 
		{ view.getSize().x / 2 -(float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().x - 40, 
		view.getSize().y / 2 - (float)texturesResourcesVec->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);

	// Backpack opening button initializing
	backpack_b.load("res/bagButton.png", "backpack");
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ view.getSize().x /2 - backpack_b.getGlobalBounds().width / 2, view.getSize().y - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update();
	//line.update();

	inventoryItemsList.update(iec, window, view);
	locationItemsList.update(iec, window, view);

	Button* tempButton = panel.update(iec, window, view);
	if (tempButton != nullptr)
	{
		if (tempButton->getName() == "eat") cout << "Player eating\n";
		if (tempButton->getName() == "use") cout << "Player using\n";
		if (tempButton->getName() == "info") cout << "Player getting info\n";
	}
	

	/* If backpack button was clicked and player inventory is NOT opened
	 then
	 set item lists as active, so they can update() and draw() themselves*/
	if (backpack_b.update(iec, window, view) && !playerInventoryIsOpened)
	{
		inventoryItemsList.setActive(true);
		playerInventoryIsOpened = true;

		if (playerIsInsideLocation)
		{
			locationItemsList.setActive(true);
		}
	}

	/*If RMB clicked and player is inside location
	then
	Basically logic for item swap from one item list to another*/
	if (iec._RMB && playerIsInsideLocation)
	{
		if (inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			inventoryItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			Item tempItem;
			if (inventoryItemsList.deleteItemUnderCursor(tempItem, texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
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
			if (locationItemsList.deleteItemUnderCursor(tempItem, texturesResourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y,
				iec.getMousePos(window, view)))
			{
				inventoryItemsList.addItem(tempItem);
				inventoryItemsList.getAssignedStorage()->addItem(tempItem);
			}

		}
	}

	/* If LMB clicked and player inventory is opened
	 then
	 Basically logic for closing inventory windows(items lists) when clicked outside of
	 their sprite bounds*/
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

	for (unsigned int i = 0; i < indicatorsVec.size(); i++)
		indicatorsVec[i].draw(window);

	panel.draw(window);

	backpack_b.draw(window);

	///////////////////////////

	// Applying saved view back, so further drawing logics of other modules
	// can't be ruined
	window.setView(tempView);
}

void UI::updatePlayerStatusLines(float health, float sleep, float temperature, float thirst, float hunger)
{
	indicatorsVec[HUNGER].setValue(hunger);
	indicatorsVec[THIRST].setValue(thirst);
	indicatorsVec[TEMPERATURE].setValue(temperature);
	indicatorsVec[SLEEP].setValue(sleep);
	indicatorsVec[HEALTH].setValue(health);
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
