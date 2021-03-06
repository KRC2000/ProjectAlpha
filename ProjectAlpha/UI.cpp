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

	for (auto &element : guiElementsVec)
	{
		element->assignRes(uiResVec, &uiFontsVec, texturesResVecPtr);
	}
}

void UI::update(IEC& iec, RenderWindow& window)
{
	/*for (auto& element : guiElementsVec)
		element->update(iec, window, view);*/
	layerSys.update(iec, window, view);
}

void UI::draw(RenderWindow& window)
{
	/*Temporary saving current view, to apply it back after 
	drawing UI stuff in local UI view(see end of method)*/
	tempView = window.getView();

	window.setView(view);
	///////////////////////////

	/*for (auto& element : guiElementsVec)
	{
		window.draw(*element);
	}*/

	window.draw(layerSys);

	///////////////////////////

	/* Applying saved view back, so further drawing logics of other modules
	 can't be ruined*/
	window.setView(tempView);
}

GUI_Element& UI::addGuiElement(GUI_Element* newElement, string name)
{
	newElement->setName(name);
	guiElementsVec.push_back(newElement);
	return *guiElementsVec.back();
}

void UI::loadUiRes()
{
	for (int i = 0; i < (int)UiResEnum::RES_AMOUNT; i++)
		uiResVec.push_back(Texture());

	uiResVec[(int)UiResEnum::MAINMENU_BUTTON_DEFAULT].loadFromFile("res/mainMenuDefaultButton.png");
	uiResVec[(int)UiResEnum::GAMESCENE_BUTTON_BACKPACK].loadFromFile("res/bagButton.png");
	uiResVec[(int)UiResEnum::BUTTON_CLOSE].loadFromFile("res/button_close.png");
	uiResVec[(int)UiResEnum::BUTTON_UP].loadFromFile("res/button_up.png");
	uiResVec[(int)UiResEnum::BUTTON_DOWN].loadFromFile("res/button_down.png");
	uiResVec[(int)UiResEnum::GUI_INDICATORLINE].loadFromFile("res/IndicatorLine.png");
	uiResVec[(int)UiResEnum::GUI_ITEMLIST].loadFromFile("res/GUI_List.png");
	uiResVec[(int)UiResEnum::GUI_ITEMLIST_BUTTON_UPLIST].loadFromFile("res/upListButton.png");
	uiResVec[(int)UiResEnum::GUI_ITEMLIST_BUTTON_DOWNLIST].loadFromFile("res/downListButton.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].loadFromFile("res/actionPanel.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_INFO].loadFromFile("res/info.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_EAT].loadFromFile("res/eating.png");
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_BUTTON_USE].loadFromFile("res/hand.png");
	uiResVec[(int)UiResEnum::GUI_ITEMSLISTITEM_CANVAS].loadFromFile("res/ItemBar.png");
	uiResVec[(int)UiResEnum::GUI_SLIDER].loadFromFile("res/slider.png");
	uiResVec[(int)UiResEnum::GUI_WINDOW_BORDERS].loadFromFile("res/GUI_Window_bounds.png");
	uiResVec[(int)UiResEnum::GUI_WINDOW_BACKGR].loadFromFile("res/GUI_Window_background.png");

	for (int i = 0; i < (int)UiFontsEnum::FONTS_AMOUNT; i++)
		uiFontsVec.push_back(Font());

	uiFontsVec[(int)UiFontsEnum::KARMAFUTURE].loadFromFile("res/fonts/KarmaFuture.ttf");
	uiFontsVec[(int)UiFontsEnum::SPECIALELITE].loadFromFile("res/fonts/SpecialElite.ttf");
	uiFontsVec[(int)UiFontsEnum::VINTAGEONE].loadFromFile("res/fonts/VintageOne.ttf");
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
