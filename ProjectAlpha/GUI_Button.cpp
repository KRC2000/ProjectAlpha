#include "GUI_Button.h"

GUI_Button::GUI_Button(UiResEnum buttonType, string name):
	name(name), 
	buttonType(buttonType)
{
}

void GUI_Button::assignRes(vector<Texture>& uiResVec, std::vector<sf::Font>* fontsVec)
{
	spriteIdle.setTexture(uiResVec[buttonType]);
	spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
}

bool GUI_Button::update(IEC& iec, RenderWindow &window, View &view)
{
	if (spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)))
		spriteIdle.setTextureRect(IntRect(spriteIdle.getTexture()->getSize().x / 2, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
	else spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));

	if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
	{
		if (spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)))
		{
			iec.eventExpire(Mouse::Left);
			return true;
		}
	}
	return false;
}

void GUI_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spriteIdle);
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
