#include "GUI_Button.h"

void GUI_Button::assignRes(vector<Texture>& uiResVec, std::vector<Font>* fontsVec, vector<Texture>* textureResVec)
{
	spriteIdle.setTexture(uiResVec[(int)buttonType]);
	spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
}

bool GUI_Button::update(IEC& iec, RenderWindow &window, View &view)
{
	if (active)
	{
		if (!applyTransform && spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)) ||
			applyTransform && spriteIdle.getGlobalBounds().contains(getTransformedMousePos(iec.getMousePos(window, view))))
			spriteIdle.setTextureRect(IntRect(spriteIdle.getTexture()->getSize().x / 2, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
		else spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));

		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (!applyTransform && spriteIdle.getGlobalBounds().contains(iec.getMousePos(window, view)) ||
				applyTransform && spriteIdle.getGlobalBounds().contains(getTransformedMousePos(iec.getMousePos(window, view))))
			{
				activated = true;
				iec.eventExpire(Mouse::Left);
				return true;
			}
		}
		activated = false;
	}
	return false;
}

void GUI_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (active)
	{
		target.draw(spriteIdle);
	}
}

FloatRect GUI_Button::getGlobalElementBounds()
{
	return spriteIdle.getGlobalBounds();
}
