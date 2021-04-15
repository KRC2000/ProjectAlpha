#include "GUI_ActionPanel.h"

void GUI_ActionPanel::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec)
{
	uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].setRepeated(true);

	s_head.setTexture(uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS]);
	s_head.setTextureRect(IntRect(0, uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().y / 2,
		uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().x / 2, uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().y / 2));

	s_body.setTexture(uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS]);
	s_body.setTextureRect(IntRect(0, 0, 0, uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().y / 2));

	s_tail.setTexture(uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS]);
	s_tail.setTextureRect(IntRect(uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().x / 2, uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().y / 2,
		uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().x / 2, uiResVec[(int)UiResEnum::GUI_ACTIONPANEL_CANVAS].getSize().y / 2));
}

bool GUI_ActionPanel::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		for (unsigned int i = 0; i < buttonsVec.size(); i++)
		{
			if (buttonsVec[i].update(iec, window, view))
			{
				usedButton = &buttonsVec[i];
				return true;
			}
		}
	}
	return false;
}

void GUI_ActionPanel::draw(RenderTarget& target, RenderStates states) const
{
	if (active)
	{
		target.draw(s_head);
		target.draw(s_body);
		target.draw(s_tail);
		for (unsigned int i = 0; i < buttonsVec.size(); i++)
		{
			target.draw(buttonsVec[i]);
		}
	}
}

GUI_Button& GUI_ActionPanel::getActivatedButton()
{
	for (auto& btn : buttonsVec)
	{
		if (btn.getIsActivated()) return btn;
	}
}

void GUI_ActionPanel::addActionButton(vector<Texture>& uiResVec, UiResEnum buttonType, string buttonName)
{
	GUI_Button b(buttonType, buttonName);
	//cout << "size" << buttonsVec.size() << endl;
	buttonsVec.push_back(b);
	buttonsVec.back().assignRes(uiResVec);
	//cout << "width" << buttonsVec.back().getGlobalBounds().width << endl;
	buttonsVec.back().setScale({ 0.4, 0.4 });
	buttonsVec.back().setPosition({ s_head.getPosition().x + buttonsVec.back().getGlobalBounds().width * (buttonsVec.size() - 1), s_head.getPosition().y + 6 });
	//buttonsVec.back().setPosition({ pos.x, pos.y });

	s_body.setTextureRect(IntRect(0, 0, s_body.getTextureRect().width + 50, s_body.getTextureRect().height));
}

void GUI_ActionPanel::setActive(bool isActive)
{
	active = isActive;
}

void GUI_ActionPanel::setPos(Vector2f newPos)
{
	s_head.setPosition(newPos);
	s_body.setPosition({ newPos.x + s_head.getGlobalBounds().width, newPos.y });
	s_tail.setPosition({ newPos.x + s_head.getGlobalBounds().width + s_body.getGlobalBounds().width, newPos.y });
	/*pos.x = newPos.x - 33;
	pos.y = newPos.y - 71;*/
	for (unsigned int i = 0; i < buttonsVec.size(); i++)
	{
		buttonsVec[i].setPosition({ s_head.getPosition().x + 15 + (buttonsVec.back().getGlobalBounds().width + 17) * i, s_head.getPosition().y + 6 });
	}
}

bool GUI_ActionPanel::getIsActive()
{
	return active;
}
