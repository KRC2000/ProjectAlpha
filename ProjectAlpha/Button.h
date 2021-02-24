#pragma once
#include "PrecompiledHeaders.h"

class Button
{
private:
	Texture t;
	Sprite spriteIdle;
	string texturePath;
public:
	Button();
	void load(string texturePath);
	bool update(IEC& iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void setScale(Vector2f factor);
	void setPosition(Vector2f pos);

	FloatRect getGlobalBounds();
};

