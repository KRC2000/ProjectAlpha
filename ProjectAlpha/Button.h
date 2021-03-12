#pragma once
#include "PrecompiledHeaders.h"

class Button
{
private:
	Texture t;
	Sprite spriteIdle;
	string texturePath;
	string name = "Unnamed";
public:
	Button();
	void load(string texturePath, string name);

	// Returns true when button was clicked
	bool update(IEC& iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void setScale(Vector2f factor);
	void setPosition(Vector2f pos);

	FloatRect getGlobalBounds();
	string getName();
};

