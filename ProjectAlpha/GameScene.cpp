#include "GameScene.h"

GameScene::GameScene():
	player({ 1000, 800 })
{
	ui.addGuiElement(new GUI_Clocks(), "clocks");
	ui.addGuiElement(new GUI_Button(UiResEnum::GAMESCENE_BUTTON_BACKPACK), "button_backpack");

	ui.addGuiElement(new GUI_IndicatorLine(), "health_line");
	ui.addGuiElement(new GUI_IndicatorLine(), "sleep_line");
	ui.addGuiElement(new GUI_IndicatorLine(), "temperature_line");
	ui.addGuiElement(new GUI_IndicatorLine(), "thirst_line");
	ui.addGuiElement(new GUI_IndicatorLine(), "hunger_line");

	ui.addGuiElement(new GUI_ItemsList(), "player_inventory");
	ui.addGuiElement(new GUI_ItemsList(), "location_inventory");

	ui.addGuiElement(new GUI_ActionPanel(), "inv_panel");

	ui.addGuiElement(new GUI_Window(), "win0");
	ui.getGuiElement<GUI_Window>("win0")->setActive(true);
}

void GameScene::load(RenderWindow& window)
{
	view.reset(FloatRect(0, 0, 1920, 1080));
	view.zoom(1);

	loadResources();
	ui.load(&textureResourcesVec, window, &guiFont1);
	//////////////////////////////////////

	ui.getGuiElement<GUI_Clocks>("clocks")->setColor({32, 70, 49, 255});

	ui.getGuiElement<GUI_Button>("button_backpack")->setScale({ 0.2, 0.2 });
	ui.getGuiElement<GUI_Button>("button_backpack")->setPosition({ ui.getView().getSize().x / 2 - ui.getGuiElement<GUI_Button>("button_backpack")->getGlobalBounds().width / 2,
		ui.getView().getSize().y - ui.getGuiElement<GUI_Button>("button_backpack")->getGlobalBounds().height });
	
	//Find every GUI_IndicatorLine in UI, place them vertically one after another, add title pictures
	int posMultiplier = 0;
	for (auto element : ui.getGuiElementsVec())
	{
		GUI_IndicatorLine* indicatorLinePtr;
		if (indicatorLinePtr = dynamic_cast<GUI_IndicatorLine*>(element))
		{
			indicatorLinePtr->setPos({ 50, 100 + 35 * (float)posMultiplier });
			if (element->getName() == "health_line") indicatorLinePtr->setPictureTitle(&textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T], { 100 * 0, 0, 100, 100 });
			if (element->getName() == "sleep_line") indicatorLinePtr->setPictureTitle(&textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T], { 100 * 1, 0, 100, 100 });
			if (element->getName() == "temperature_line") indicatorLinePtr->setPictureTitle(&textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T], { 100 * 2, 0, 100, 100 });
			if (element->getName() == "thirst_line") indicatorLinePtr->setPictureTitle(&textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T], { 100 * 3, 0, 100, 100 });
			if (element->getName() == "hunger_line") indicatorLinePtr->setPictureTitle(&textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T], { 100 * 4, 0, 100, 100 });
			posMultiplier++;
		}
	}

	ui.getGuiElement<GUI_ItemsList>("player_inventory")->setPosition({ ui.getView().getSize().x / 2 + 40, ui.getView().getSize().y / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().y / 2 });
	ui.getGuiElement<GUI_ItemsList>("location_inventory")->setPosition({ ui.getView().getSize().x / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().x - 40,
		ui.getView().getSize().y / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().y / 2 });

	ui.getGuiElement<GUI_ItemsList>("player_inventory")->assignStorage(player.getStoragePtr());

	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO, "info");
	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_USE, "use");
	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT, "eat");

	/////////////////////////////////////
	player.load(textureResourcesVec, ui);
	map.loadTextures(&textureResourcesVec);

	cout << "Game scene loaded!" << endl;
}

SceneType GameScene::update(IEC& iec, RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		ui.update(iec, window);
		map.update(iec, window);
		
		// Updating every player status indicators according to player's status
		for (auto element : ui.getGuiElementsVec())
		{
			GUI_IndicatorLine* indicatorLinePtr;
			if (indicatorLinePtr = dynamic_cast<GUI_IndicatorLine*>(element))
			{
				if (element->getName() == "health_line") indicatorLinePtr->setValue(player.getStateIndicatorNum(SurvivalParametersEnum::HEALTH));
				if (element->getName() == "sleep_line") indicatorLinePtr->setValue(player.getStateIndicatorNum(SurvivalParametersEnum::SLEEP));
				if (element->getName() == "temperature_line") indicatorLinePtr->setValue(player.getStateIndicatorNum(SurvivalParametersEnum::TEMPERATURE));
				if (element->getName() == "thirst_line") indicatorLinePtr->setValue(player.getStateIndicatorNum(SurvivalParametersEnum::THIRST));
				if (element->getName() == "hunger_line") indicatorLinePtr->setValue(player.getStateIndicatorNum(SurvivalParametersEnum::HUNGER));
			}
		}

		GUI_ItemsList* p_inv = ui.getGuiElement<GUI_ItemsList>("player_inventory");
		GUI_ItemsList* l_inv = ui.getGuiElement<GUI_ItemsList>("location_inventory");
		GUI_ActionPanel* inv_panel = ui.getGuiElement<GUI_ActionPanel>("inv_panel");


		if (ui.getGuiElement<GUI_Button>("button_backpack")->getIsActivated())
		{
			p_inv->setActive(true);
			if (player.getIsInside()) l_inv->setActive(true);
		}

		//if clicked outside of a inventory windows - close them
		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (p_inv->getIsActive() && !l_inv->getIsActive())
			{
				if (!p_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())))
				{
					p_inv->setActive(false);
					inv_panel->setActive(false);
					iec.eventExpire(Mouse::Left);
				}
			}
			else if (p_inv->getIsActive() && l_inv->getIsActive())
			{
				if (!p_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())) &&
					!l_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())))
				{
					p_inv->setActive(false);
					l_inv->setActive(false);
					inv_panel->setActive(false);
					iec.eventExpire(Mouse::Left);
				}
			}
		}


		//if clicked on player inventory blank - expire click event
		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (p_inv->getIsActive())
			{
				if (p_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())))
				{
					if (!p_inv->isCursorPointingAtItem(iec.getMousePos(window, ui.getView())))
						iec.eventExpire(Mouse::Left);
				}
			}
		}


		//if clicked on location inventory blank - expire click event
		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (l_inv->getIsActive())
			{
				if (l_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())))
				{
					if (!l_inv->isCursorPointingAtItem(iec.getMousePos(window, ui.getView())))
						iec.eventExpire(Mouse::Left);
				}
			}
		}

		//if player enters inside - assign storage of that place to the location inventory
		if (player.getIsInside())
		{
			if (l_inv->getAssignedStorage() != player.getRelatedPointerPtr()->getStorage())
			{
				l_inv->assignStorage(player.getRelatedPointerPtr()->getStorage());
			}
		}

		//if RMB clicked on item while inside - swap the items from one inventory to other
		if (iec.getMouseButtonState(Mouse::Right) == IEC::KeyState::JUSTPRESSED && player.getIsInside())
		{
			if (p_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())) &&
				p_inv->getAssignedStorage()->getItemsVec()->size() >= 1)
			{
				if (p_inv->isCursorPointingAtItem(iec.getMousePos(window, ui.getView())))
				{
					unsigned int itemVecIndex;
					itemVecIndex = p_inv->getItemIndexCursorPointingAt(iec.getMousePos(window, ui.getView()));
					Item tempItem = p_inv->deleteItem(itemVecIndex);
					l_inv->getAssignedStorage()->addItem(tempItem);
					l_inv->addItem(l_inv->getAssignedStorage()->getItemsVec()->back());
				}
			}
			if (l_inv->getBorderSprite()->getGlobalBounds().contains(iec.getMousePos(window, ui.getView())) &&
				l_inv->getAssignedStorage()->getItemsVec()->size() >= 1)
			{
				if (l_inv->isCursorPointingAtItem(iec.getMousePos(window, ui.getView())))
				{
					unsigned int itemVecIndex;
					itemVecIndex = l_inv->getItemIndexCursorPointingAt(iec.getMousePos(window, ui.getView()));
					Item tempItem = l_inv->deleteItem(itemVecIndex);
					p_inv->getAssignedStorage()->addItem(tempItem);
					p_inv->addItem(p_inv->getAssignedStorage()->getItemsVec()->back());
				}
			}
		}

		//if clicked on inventory item - show up action panel and assign it to 
		if (p_inv->getIsActive())
		{
			if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
			{
				if (p_inv->isCursorPointingAtItem(iec.getMousePos(window, ui.getView())))
				{
					cout << "This happens\n";
					inv_panel->setActive(true);
					inv_panel->assignGuiElement(&p_inv->getItemsVec().at(p_inv->getItemIndexCursorPointingAt(iec.getMousePos(window, ui.getView()))));
					GUI_ItemsListItem* assignedItem = dynamic_cast<GUI_ItemsListItem*>(inv_panel->getAssignedGuiElement());
					inv_panel->setPos({ assignedItem->getPos().x + assignedItem->getSpriteBox()->getGlobalBounds().width, assignedItem->getPos().y });
					iec.eventExpire(Mouse::Left);
				}
			}
		}

		if (p_inv->isBeingScrolled())
		{
			inv_panel->setActive(false);
		}

		//action panel buttons interactions
		if (inv_panel->getIsActive())
		{
			GUI_Button* button = inv_panel->getActivatedButton();
			if (button)
			{
				if (button->getName() == "eat")
				{
					GUI_ItemsListItem* listItem = dynamic_cast<GUI_ItemsListItem*>(inv_panel->getAssignedGuiElement());
					if (listItem)
					{
						player.consume(*listItem->getRelatedItem());
						p_inv->deleteItem(listItem);
						inv_panel->setActive(false);
					}
					cout << "Player eating\n";
				}
				if (button->getName() == "use") cout << "Player using\n";
				if (button->getName() == "info") cout << "Player getting info\n";
			}
		}

		player.update(iec, window, map, ui);

		view.setCenter(player.getPos());
		if (iec.getMouseWheelDelta() != 0) view.zoom(1 - (float)iec.getMouseWheelDelta() / 10);
	}
	return SceneType::NONE_SCENE;
}

void GameScene::draw(RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		window.setView(view);

		map.draw(window);
		window.draw(player);

		ui.draw(window);
	}
}

void GameScene::unload()
{
	cout << "Game scene UNloaded!" << endl;
}



void GameScene::loadResources()
{
	for (int i = 0; i < (int)ResourcesEnum::RESOURCES_AMOUNT; i++)
	{
		Texture t;
		textureResourcesVec.push_back(t);
	}

	///////////// Loading textures /////////////
	textureResourcesVec[(int)ResourcesEnum::PLAYERICON_T].loadFromFile("res/playerIcon.png");
	textureResourcesVec[(int)ResourcesEnum::TARGETPOINT_T].loadFromFile("res/impact-point.png");
	textureResourcesVec[(int)ResourcesEnum::POINTERS_T].loadFromFile("res/buildings.png");
	textureResourcesVec[(int)ResourcesEnum::GUI_T].loadFromFile("res/GUI.png");
	textureResourcesVec[(int)ResourcesEnum::ITEMSLISTITEM_T].loadFromFile("res/ItemBar.png");
	textureResourcesVec[(int)ResourcesEnum::INDICATORLINE_T].loadFromFile("res/IndicatorLine.png");
	textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T].loadFromFile("res/statusIcons.png");
	textureResourcesVec[(int)ResourcesEnum::ITEMS_T].loadFromFile("res/Items.png");
	textureResourcesVec[(int)ResourcesEnum::ACTIONPANEL_T].loadFromFile("res/actionPanel.png");
	textureResourcesVec[(int)ResourcesEnum::GUN_AK_T].loadFromFile("res/gun.png");
	textureResourcesVec[(int)ResourcesEnum::BULLET_T].loadFromFile("res/bullet.png");
	////////////////////////////////////////////

	if (!guiFont1.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;


}

