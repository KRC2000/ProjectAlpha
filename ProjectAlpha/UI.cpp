#include "UI.h"

UI::UI()
{	
}

void UI::load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font)
{
	this->texturesResVecPtr = texturesResourcesVec;
	guiFont1 = font;

	// Initializing local UI view
	//view.setSize({ 1920, 1080 });
	view.setSize({ (float)window.getSize().x, (float)window.getSize().y });
	//view.setSize({ 2000, 1800});
	view.setCenter(view.getSize().x/2, view.getSize().y / 2);

	loadUiRes();

	// In-game clocks initializing
	clock.assignRes(uiResVec, &uiFontsVec);

	//indicatorsVec[HEALTH].load(&texturesResVecPtr->at(ResourcesEnum::INDICATORLINE_T));
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HEALTH].assignRes(uiResVec);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].assignRes(uiResVec);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].assignRes(uiResVec);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].assignRes(uiResVec);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].assignRes(uiResVec);
	
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HEALTH].setPictureTitle(&texturesResVecPtr->at((int)ResourcesEnum::STATUSICONS_T), {100 * 0, 0, 100, 100});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].setPictureTitle(&texturesResVecPtr->at((int)ResourcesEnum::STATUSICONS_T), {100 * 1, 0, 100, 100});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].setPictureTitle(&texturesResVecPtr->at((int)ResourcesEnum::STATUSICONS_T), { 100 * 2, 0, 100, 100});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].setPictureTitle(&texturesResVecPtr->at((int)ResourcesEnum::STATUSICONS_T), { 100 * 3, 0, 100, 100});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].setPictureTitle(&texturesResVecPtr->at((int)ResourcesEnum::STATUSICONS_T), { 100 * 4, 0, 100, 100});
	
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HEALTH].setPos({ indicatorsVec[(int)PlayerStateIndicatorsEnum::HEALTH].getPictureSprite()->getGlobalBounds().width, clock.getTextObj()->getGlobalBounds().height + 30});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].setPos({ indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 1 * indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].getPictureSprite()->getGlobalBounds().height});
	indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].setPos({ indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 2 * indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].setPos({ indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 3 * indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].setPos({ indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 4 * indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].getPictureSprite()->getGlobalBounds().height });

	panel.assignRes(uiResVec);
	//panel.load(*texturesResourcesVec);
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO, "info");
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_USE, "use");
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT, "eat");

	// Items lists load() 
	inventoryItemsList.assignRes(uiResVec, &uiFontsVec, texturesResVecPtr);
	inventoryItemsList.setPosition({ view.getSize().x / 2 + 40, view.getSize().y / 2 - (float)texturesResVecPtr->at((int)ResourcesEnum::GUI_T).getSize().y / 2 });
	locationItemsList.assignRes(uiResVec, &uiFontsVec, texturesResVecPtr);
	locationItemsList.setPosition({ view.getSize().x / 2 - (float)texturesResVecPtr->at((int)ResourcesEnum::GUI_T).getSize().x - 40,
		view.getSize().y / 2 - (float)texturesResVecPtr->at((int)ResourcesEnum::GUI_T).getSize().y / 2 });

	// Backpack opening button initializing
	backpack_b.assignRes(uiResVec);
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ view.getSize().x /2 - backpack_b.getGlobalBounds().width / 2, view.getSize().y - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update(iec, window, view);
	//line.update();

	inventoryItemsList.update(iec, window, view);
	locationItemsList.update(iec, window, view);

	if (panel.update(iec, window, view))
	{
		GUI_Button* btn = &panel.getActivatedButton();
		if (btn)
		{
			if (btn->getName() == "eat") cout << "Player eating\n";
			if (btn->getName() == "use") cout << "Player using\n";
			if (btn->getName() == "info") cout << "Player getting info\n";
		}
	}

	/*if (tempButton != nullptr)
	{
		if (tempButton->getName() == "eat") cout << "Player eating\n";
		if (tempButton->getName() == "use") cout << "Player using\n";
		if (tempButton->getName() == "info") cout << "Player getting info\n";
	}*/
	

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
	if ((iec.getMouseButtonState(Mouse::Right) == IEC::KeyState::JUSTPRESSED) && playerIsInsideLocation)
	{
		if (inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			inventoryItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			unsigned int itemVecIndex;
			if (inventoryItemsList.isCursorPointingAtItem(itemVecIndex, iec.getMousePos(window, view)))
			{
				moveItemBetweenLists(inventoryItemsList, locationItemsList, itemVecIndex);
			}
		}
		if (locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view)) &&
			locationItemsList.getAssignedStorage()->getItemsVec()->size() >= 1)
		{
			unsigned int itemVecIndex;
			if (locationItemsList.isCursorPointingAtItem(itemVecIndex, iec.getMousePos(window, view)))
			{
				moveItemBetweenLists(locationItemsList, inventoryItemsList, itemVecIndex);
			}
		}
	}

	if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
	{
		if (!panel.getIsActive())
		{
			if (inventoryItemsList.getIsActive())
			{
				unsigned int itemVecIndex;
				if (inventoryItemsList.isCursorPointingAtItem(itemVecIndex, iec.getMousePos(window, view)))
				{
					panel.setPos({ inventoryItemsList.getItemsVec()[itemVecIndex].getSpriteBox()->getPosition().x + inventoryItemsList.getItemsVec()[itemVecIndex].getSpriteBox()->getGlobalBounds().width,
						inventoryItemsList.getItemsVec()[itemVecIndex].getSpriteBox()->getPosition().y});
					panel.setActive(true);
				}
			}
		}
		else
		{
			panel.setActive(false);
		}
	}
	if (inventoryItemsList.isBeingScrolled())
		panel.setActive(false);

	/* If LMB clicked and player inventory is opened
	 then
	 Basically logic for closing inventory windows(items lists) when clicked outside of
	 their sprite bounds*/
	if ((iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED) && playerInventoryIsOpened)
	{
		if((!inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& !locationItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& playerIsInsideLocation) || (!inventoryItemsList.getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, view))
			&& !playerIsInsideLocation))
		{
			inventoryItemsList.setActive(false);
			locationItemsList.setActive(false);
			panel.setActive(false);
			playerInventoryIsOpened = false;
			iec.eventExpire(Mouse::Left);
		}
	}

}

void UI::draw(RenderWindow& window)
{
	/*Temporary saving current view, to apply it back after 
	drawing UI stuff in local UI view(see end of method)*/
	tempView = window.getView();

	window.setView(view);
	///////////////////////////

	window.draw(clock);

	inventoryItemsList.draw(window);
	locationItemsList.draw(window);

	for (unsigned int i = 0; i < indicatorsVec.size(); i++)
		window.draw(indicatorsVec[i]);

	panel.draw(window);

	window.draw(backpack_b);

	///////////////////////////

	/* Applying saved view back, so further drawing logics of other modules
	 can't be ruined*/
	window.setView(tempView);
}

void UI::updatePlayerStatusLines(float health, float sleep, float temperature, float thirst, float hunger)
{
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HUNGER].setValue(hunger);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::THIRST].setValue(thirst);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::TEMPERATURE].setValue(temperature);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::SLEEP].setValue(sleep);
	indicatorsVec[(int)PlayerStateIndicatorsEnum::HEALTH].setValue(health);
}

void UI::addGuiElement(GUI_Element* newElement, string name)
{
	newElement->setName(name);
	guiElementsVec.push_back(*newElement);
}

void UI::moveItemBetweenLists(GUI_ItemsList& movingFromList, GUI_ItemsList& movingToList, unsigned int itemVecIndex)
{
	Item tempItem = movingFromList.deleteItem(itemVecIndex);
	movingToList.addItem(tempItem);
	movingToList.getAssignedStorage()->addItem(tempItem);
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

void UI::loadUiRes()
{
	for (int i = 0; i < (int)UiResEnum::RES_AMOUNT; i++)
		uiResVec.push_back(Texture());

	uiResVec[(int)UiResEnum::MAINMENU_BUTTON_DEFAULT].loadFromFile("res/mainMenuDefaultButton.png");
	uiResVec[(int)UiResEnum::GAMESCENE_BUTTON_BACKPACK].loadFromFile("res/bagButton.png");
	uiResVec[(int)UiResEnum::GUI_INDICATORLINE].loadFromFile("res/IndicatorLine.png");
	uiResVec[(int)UiResEnum::GUI_ITEMLIST_BUTTON_UPLIST].loadFromFile("res/upListButton.png");
	uiResVec[(int)UiResEnum::GUI_ITEMLIST_BUTTON_DOWNLIST].loadFromFile("res/downListButton.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].loadFromFile("res/actionPanel.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO].loadFromFile("res/info.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT].loadFromFile("res/eating.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_USE].loadFromFile("res/hand.png");
	uiResVec[(int)UiResEnum::GUI_ITEMSLISTITEM_CANVAS].loadFromFile("res/ItemBar.png");
	uiResVec[(int)UiResEnum::GUI_SLIDER].loadFromFile("res/listScrollBar.png");

	for (int i = 0; i < (int)UiFontsEnum::FONTS_AMOUNT; i++)
		uiFontsVec.push_back(Font());

	uiFontsVec[(int)UiFontsEnum::PIXELATED_3D_DEFAULT].loadFromFile("res/VintageOne.ttf");
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
