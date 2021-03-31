#include "GUI_Button.h"

GUI_Button::GUI_Button()
{

}

void GUI_Button::load(string texturePath, string name)
{
	this->name = name;
	this->texturePath = texturePath;
	t.loadFromFile(texturePath);
	spriteIdle.setTexture(t);
	spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
	
}


bool GUI_Button::update(IEC& iec, RenderWindow &window, View &view)
{
	if (spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)))
		spriteIdle.setTextureRect(IntRect(spriteIdle.getTexture()->getSize().x / 2, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
	else spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));

	if (iec._LMB)
	{
		if (spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)))
		{
			iec._LMB = false;
			return true;
		}
	}
	return false;
}

void GUI_Button::draw(RenderWindow& window)
{
	window.draw(spriteIdle);
}

void GUI_Button::setScale(Vector2f factor)
{
	spriteIdle.setScale(factor);
}

void GUI_Button::setPosition(Vector2f pos)
{
	spriteIdle.setPosition(pos);
}

FloatRect GUI_Button::getGlobalBounds()
{
	return spriteIdle.getGlobalBounds();
}

string GUI_Button::getName()
{
	return name;
}
