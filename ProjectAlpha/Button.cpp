#include "Button.h"

Button::Button()
{

}

void Button::load(string texturePath)
{
	t.loadFromFile(texturePath);
	spriteIdle.setTexture(t);
	spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
	
}

bool Button::update(IEC& iec, RenderWindow &window, View &view)
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

void Button::draw(RenderWindow& window)
{
	window.draw(spriteIdle);
}

void Button::setScale(Vector2f factor)
{
	spriteIdle.setScale(factor);
}

void Button::setPosition(Vector2f pos)
{
	spriteIdle.setPosition(pos);
}

FloatRect Button::getGlobalBounds()
{
	return spriteIdle.getGlobalBounds();
}
