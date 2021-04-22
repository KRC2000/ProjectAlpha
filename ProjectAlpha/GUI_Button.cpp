#include "GUI_Button.h"

void GUI_Button::assignRes(vector<Texture>& uiResVec, std::vector<Font>* fontsVec, vector<Texture>* textureResVec)
{
	spriteIdle.setTexture(uiResVec[(int)buttonType]);
	cout << uiResVec[(int)buttonType].getSize().x << endl;
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
			activated = true;
			iec.eventExpire(Mouse::Left);
<<<<<<< HEAD
			//cout << "You missed!\n";
=======
			cout << "You missed!\n";
>>>>>>> 39f7a4c96ffe9a380f7c26f1e43e7bf22f57c5c7
			return true;
		}
	}
	activated = false;
	return false;
}

void GUI_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spriteIdle);
	//cout << "You drew correct shit!\n";
}
