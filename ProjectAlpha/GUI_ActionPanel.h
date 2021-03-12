#pragma once
#include "PrecompiledHeaders.h"
#include "Button.h"

class GUI_ActionPanel
{
	Vector2f pos{ 0,0 };
	Sprite s_body;
	vector<Button> buttonsVec;

	bool active = false;
public:
	GUI_ActionPanel();
	void load(vector<Texture>& textureResourcesVec);

	/*Returns pointer to a button that was clicked inside of a panel
	Otherwise returns nullptr
	Use like this: 
	Button* temp = update();
	if (temp != nullptr)
	if (temp->getName() == "yourName") action();*/
	Button* update(IEC & iec, RenderWindow & window, View & view);

	/*Widening widget bounds, creating and adding new button to it in a row*/
	void addActionButton(string texturePath, string buttonName);
	void draw(RenderWindow& window);

	/*Set to true to allow updating and drawing*/
	void setActive(bool isActive);
};
