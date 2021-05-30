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
		Vector2f mousePos;
		if (applyTransform) mousePos = getTransformedMousePos(iec.getMousePos(window, view));
		else mousePos = iec.getMousePos(window, view);

		if (spriteIdle.getGlobalBounds().contains(mousePos))
			spriteIdle.setTextureRect(IntRect(spriteIdle.getTexture()->getSize().x / 2, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));
		else spriteIdle.setTextureRect(IntRect(0, 0, spriteIdle.getTexture()->getSize().x / 2, spriteIdle.getTexture()->getSize().y));

		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (spriteIdle.getGlobalBounds().contains(mousePos))
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
