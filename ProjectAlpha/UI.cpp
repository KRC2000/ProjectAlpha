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
	indicatorsVec[HEALTH].assignRes(uiResVec);
	indicatorsVec[SLEEP].assignRes(uiResVec);
	indicatorsVec[TEMPERATURE].assignRes(uiResVec);
	indicatorsVec[THIRST].assignRes(uiResVec);
	indicatorsVec[HUNGER].assignRes(uiResVec);
	
	indicatorsVec[HEALTH].setPictureTitle(&texturesResVecPtr->at(ResourcesEnum::STATUSICONS_T), {100 * 0, 0, 100, 100});
	indicatorsVec[SLEEP].setPictureTitle(&texturesResVecPtr->at(ResourcesEnum::STATUSICONS_T), {100 * 1, 0, 100, 100});
	indicatorsVec[TEMPERATURE].setPictureTitle(&texturesResVecPtr->at(ResourcesEnum::STATUSICONS_T), { 100 * 2, 0, 100, 100});
	indicatorsVec[THIRST].setPictureTitle(&texturesResVecPtr->at(ResourcesEnum::STATUSICONS_T), { 100 * 3, 0, 100, 100});
	indicatorsVec[HUNGER].setPictureTitle(&texturesResVecPtr->at(ResourcesEnum::STATUSICONS_T), { 100 * 4, 0, 100, 100});
	
	indicatorsVec[HEALTH].setPos({ indicatorsVec[HEALTH].getPictureSprite()->getGlobalBounds().width, clock.getTextObj()->getGlobalBounds().height + 30});
	indicatorsVec[SLEEP].setPos({ indicatorsVec[SLEEP].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 1 * indicatorsVec[SLEEP].getPictureSprite()->getGlobalBounds().height});
	indicatorsVec[TEMPERATURE].setPos({ indicatorsVec[TEMPERATURE].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 2 * indicatorsVec[TEMPERATURE].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[THIRST].setPos({ indicatorsVec[THIRST].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 3 * indicatorsVec[THIRST].getPictureSprite()->getGlobalBounds().height });
	indicatorsVec[HUNGER].setPos({ indicatorsVec[HUNGER].getPictureSprite()->getGlobalBounds().width,
		clock.getTextObj()->getGlobalBounds().height + 30 + 4 * indicatorsVec[HUNGER].getPictureSprite()->getGlobalBounds().height });

	
	panel.load(*texturesResourcesVec);
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO, "info");
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_USE, "use");
	panel.addActionButton(uiResVec, UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT, "eat");
	/*panel.addActionButton("res/info.png", "info");
	panel.addActionButton("res/hand.png", "use");
	panel.addActionButton("res/eating.png", "eat");*/


	// Items lists load() 
	inventoryItemsList.load(texturesResVecPtr, uiResVec,
		{ view.getSize().x / 2 + 40, view.getSize().y / 2 -(float)texturesResVecPtr->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);
	locationItemsList.load(texturesResVecPtr, uiResVec,
		{ view.getSize().x / 2 -(float)texturesResVecPtr->at(ResourcesEnum::GUI_T).getSize().x - 40,
		view.getSize().y / 2 - (float)texturesResVecPtr->at(ResourcesEnum::GUI_T).getSize().y / 2 }, guiFont1);

	// Backpack opening button initializing
	backpack_b.assignRes(uiResVec);
	//backpack_b.load("res/bagButton.png", "backpack");
	backpack_b.setScale({ 0.2, 0.2 });
	backpack_b.setPosition({ view.getSize().x /2 - backpack_b.getGlobalBounds().width / 2, view.getSize().y - backpack_b.getGlobalBounds().height });
}

void UI::update(IEC& iec, RenderWindow& window)
{
	clock.update(iec, window, view);
	//line.update();

	inventoryItemsList.update(iec, window, view);
	locationItemsList.update(iec, window, view);

	GUI_Button* tempButton = panel.update(iec, window, view);
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
					panel.setPos({ iec.getMousePos(window, view).x,
						inventoryItemsList.getItemsVec()[itemVecIndex].getSpriteBox()->getPosition().y + inventoryItemsList.getItemsVec()[itemVecIndex].getSpriteBox()->getGlobalBounds().height / 2 });
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
	indicatorsVec[HUNGER].setValue(hunger);
	indicatorsVec[THIRST].setValue(thirst);
	indicatorsVec[TEMPERATURE].setValue(temperature);
	indicatorsVec[SLEEP].setValue(sleep);
	indicatorsVec[HEALTH].setValue(health);
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
	for (int i = 0; i < UiResEnum::RES_AMOUNT; i++)
		uiResVec.push_back(Texture());

	uiResVec[UiResEnum::MAINMENU_BUTTON_DEFAULT].loadFromFile("res/mainMenuDefaultButton.png");
	uiResVec[UiResEnum::GAMESCENE_BUTTON_BACKPACK].loadFromFile("res/bagButton.png");
	uiResVec[UiResEnum::GUI_INDICATORLINE].loadFromFile("res/IndicatorLine.png");
	uiResVec[UiResEnum::GUI_ITEMLIST_BUTTON_UPLIST].loadFromFile("res/upListButton.png");
	uiResVec[UiResEnum::GUI_ITEMLIST_BUTTON_DOWNLIST].loadFromFile("res/downListButton.png");
	uiResVec[UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO].loadFromFile("res/info.png");
	uiResVec[UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT].loadFromFile("res/eating.png");
	uiResVec[UiResEnum::GUI_ACTIONPANEL_BUTTON_USE].loadFromFile("res/hand.png");

	for (int i = 0; i < UiFontsEnum::FONTS_AMOUNT; i++)
		uiFontsVec.push_back(Font());

	uiFontsVec[UiFontsEnum::PIXELATED_3D_DEFAULT].loadFromFile("res/VintageOne.ttf");
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
