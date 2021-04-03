#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_ItemsListItem.h"
#include "GUI_Button.h"

class GUI_ActionPanel
{
	Vector2f pos{ 0,0 };
	Sprite s_body;
	vector<GUI_Button> buttonsVec;

	bool active = false;
	GUI_ItemsListItem* itemPointer;
public:
	GUI_ActionPanel();
	void load(vector<Texture>& textureResourcesVec);

	/*Returns pointer to a button that was clicked inside of a panel
	Otherwise returns nullptr
	Use like this: 
	GUI_Button* temp = update();
	if (temp != nullptr)
	if (temp->getName() == "yourName") action();*/
	GUI_Button* update(IEC & iec, RenderWindow & window, View & view);

	/*Widening widget bounds, creating and adding new button to it in a row*/
	void addActionButton(vector<Texture>& uiResVec, UiResEnum buttonType, string buttonName);
	void draw(RenderWindow& window);

	/*Set to true to allow updating and drawing*/
	void setActive(bool isActive);
	void setPos(Vector2f newPos);

	bool getIsActive();
};

