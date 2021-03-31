#pragma once
#include "PrecompiledHeaders.h"

class GUI_Button
{
private:
	Texture t;
	Sprite spriteIdle;
	string texturePath;
	string name = "Unnamed";
public:
	GUI_Button();
	void load(string texturePath, string name);

	// Returns true when button was clicked
	bool update(IEC& iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void setScale(Vector2f factor);
	void setPosition(Vector2f pos);

	FloatRect getGlobalBounds();
	string getName();
};

