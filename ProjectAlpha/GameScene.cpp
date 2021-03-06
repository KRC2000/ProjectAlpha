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

	GUI_Element* win0_element = &ui.addGuiElement(new GUI_Window(), "win0");
	ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Window(win0_element), "win1");
	ui.addGuiElement(new GUI_Window(), "win2");

	GUI_Window* win0 = ui.getGuiElement<GUI_Window>("win0");
	GUI_Window* win1 = win0->getGuiElement<GUI_Window>("win1");
	//win1->setActive(true);

	win1->applyParentalTransforms(win0->getParentalTransforms());
	win1->applyTransformOnInteraction(win0->getParentalTransforms());

	win0->addGuiElement(new GUI_Button(), "but0");
	win0->getGuiElement<GUI_Button>("but0")->setActive(true);
	win1->addGuiElement(new GUI_Button(), "but0");
	win1->getGuiElement<GUI_Button>("but0")->setActive(true);
	win1->addGuiElement(new GUI_Button(), "but1");
	win1->getGuiElement<GUI_Button>("but1")->setActive(true);


	win0->getGuiElement<GUI_Button>("but0")->applyTransformOnInteraction(win0->getParentalTransforms());
	win1->getGuiElement<GUI_Button>("but0")->applyTransformOnInteraction(win1->getParentalTransforms());
	win1->getGuiElement<GUI_Button>("but1")->applyTransformOnInteraction(win1->getParentalTransforms());

	
	//GUI_Element* secondWindow = &ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Window(mainWindow), "win1");
	/*ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Window(mainWindow), "win1");
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Window>("win1")->addGuiElement(new GUI_Button(), "but0");*/
	//ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Button(), "but0");
	
	/*ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Button(), "but1");
	ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Button(), "but2");
	ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_Button(), "but3");
	ui.getGuiElement<GUI_Window>("win0")->addGuiElement(new GUI_TextDisplay(), "txt0");*/

	//ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but0")->setPosition({0, 0});
	//ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but0")->setActive(true);
	/*ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but1")->setPosition({0, 200});
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but1")->setActive(true);
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but2")->setPosition({ 50, 700 });
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but2")->setActive(true);
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but3")->setPosition({ 0, 1200 });
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but3")->setActive(true);
	ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_TextDisplay>("txt0")->setActive(true);*/
}

void GameScene::load(RenderWindow& window)
{
	view.reset(FloatRect(0, 0, 1920, 1080));
	view.zoom(1);

	loadResources();
	ui.load(&textureResourcesVec, window, &guiFont1);
	//////////////////////////////////////

	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_Clocks>("clocks"));
	ui.getGuiElement<GUI_Clocks>("clocks")->setColor({32, 70, 49, 255});

	GUI_Button* backPack_b = ui.getGuiElement<GUI_Button>("button_backpack");
	ui.layerSys.addStaticLayer(*backPack_b);
	backPack_b->setScale({ 0.2, 0.2 });
	backPack_b->setPosition({ ui.getView().getSize().x / 2 - ui.getGuiElement<GUI_Button>("button_backpack")->getGlobalBounds().width / 2,
		ui.getView().getSize().y - ui.getGuiElement<GUI_Button>("button_backpack")->getGlobalBounds().height });
	backPack_b->setActive(true);
	

	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_IndicatorLine>("health_line"));
	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_IndicatorLine>("sleep_line"));
	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_IndicatorLine>("temperature_line"));
	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_IndicatorLine>("thirst_line"));
	ui.layerSys.addStaticLayer(*ui.getGuiElement<GUI_IndicatorLine>("hunger_line"));
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


	ui.layerSys.addDynamicLayer(*ui.getGuiElement<GUI_ItemsList>("player_inventory"));
	ui.layerSys.addDynamicLayer(*ui.getGuiElement<GUI_ItemsList>("location_inventory"));
	ui.getGuiElement<GUI_ItemsList>("player_inventory")->setPosition({ ui.getView().getSize().x / 2 + 40, ui.getView().getSize().y / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().y / 2 });
	ui.getGuiElement<GUI_ItemsList>("location_inventory")->setPosition({ ui.getView().getSize().x / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().x - 40,
		ui.getView().getSize().y / 2 - (float)textureResourcesVec[(int)ResourcesEnum::GUI_T].getSize().y / 2 });

	ui.getGuiElement<GUI_ItemsList>("player_inventory")->assignStorage(player.getStoragePtr());

	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO, "info");
	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_USE, "use");
	ui.getGuiElement<GUI_ActionPanel>("inv_panel")->addActionButton(ui.getUiResVec(), UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT, "eat");

	GUI_Window* win0 = ui.getGuiElement<GUI_Window>("win0");
	GUI_Window* win1 = ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Window>("win1");
	//win0->setSize({ 300, 300 });
	//win1->setSize({ 200, 900 });
	//win1->setPos({ 50, 0 });
	//win1->setActive(true);
	Vector2f v = ui.getGuiElement<GUI_Window>("win0")->getContentOccupySize();
	//cout << v.x << " |||||" << v.y << endl;
	
	//win1->applyParentalTransforms(win0->getParentalTransforms());
	//cout << win0->getParentalTransforms().size() << endl;
	//cout << win1->getParentalTransforms().size() << endl;

	/*win0->getGuiElement<GUI_Button>("but0")->applyTransformOnInteraction(win0->getParentalTransforms());
	win1->getGuiElement<GUI_Button>("but0")->applyTransformOnInteraction(win1->getParentalTransforms());*/

	win0->getGuiElement<GUI_Button>("but0")->setApplyTransform(true);
	win1->getGuiElement<GUI_Button>("but0")->setApplyTransform(true);
	win1->getGuiElement<GUI_Button>("but1")->setApplyTransform(true);
	win1->getGuiElement<GUI_Button>("but1")->setPosition({200, 1300});
	//win0->setSize({ 1000, 700 });
	win0->setPos({ 100, 0 });
	win1->setPos({ -100, 400 });
	win1->setSize({ 300, 400 });

	//win1->getGuiElement<GUI_Button>("but0")->getTransformedMousePos()
	//win1->applyTransformOnInteraction(win0->getParentalTransforms());

	ui.layerSys.addDynamicLayer(*win0);
	ui.layerSys.addDynamicLayer(*ui.getGuiElement<GUI_Window>("win2"));
	win0->setActive(true);
	win1->setActive(true);
	ui.getGuiElement<GUI_Window>("win2")->setActive(true);
	/////////////////////////////////////
	player.load(textureResourcesVec, ui);
	map.loadTextures(&textureResourcesVec);

}

SceneType GameScene::update(IEC& iec, RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		//Vector2f pos = ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Window>("win1")->getGuiElement<GUI_Button>("but0")->getTransformedMousePos(iec.getMousePos(window, ui.getView()));
		//Vector2f pos = ui.getGuiElement<GUI_Window>("win0")->getGuiElement<GUI_Button>("but0")->getTransformedMousePos(iec.getMousePos(window, ui.getView()));
		//cout << pos.x << " \\\ " << pos.y << endl;

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
				}
				if (button->getName() == "use") {}
				if (button->getName() == "info")
				{
					//ui.getGuiElement<GUI_Window>("win0")->setActive(true);
					inv_panel->setActive(false);
				}
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

