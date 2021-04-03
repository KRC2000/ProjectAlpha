#include "GUI_ActionPanel.h"

GUI_ActionPanel::GUI_ActionPanel()
{
}

void GUI_ActionPanel::load(vector<Texture>& textureResourcesVec)
{
	s_body.setTexture(textureResourcesVec[ResourcesEnum::ACTIONPANEL_T]);
	s_body.setPosition(pos);
	buttonsVec.reserve(10);
}


GUI_Button* GUI_ActionPanel::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		for (unsigned int i = 0; i < buttonsVec.size(); i++)
		{
			if (buttonsVec[i].update(iec, window, view)) return &buttonsVec[i];
		}
	}
	return nullptr;
}

void GUI_ActionPanel::addActionButton(vector<Texture>& uiResVec, UiResEnum buttonType, string buttonName)
{
	GUI_Button b(buttonType, buttonName);
	//cout << "size" << buttonsVec.size() << endl;
	buttonsVec.push_back(b);
	buttonsVec.back().assignTextureRes(uiResVec);
	//cout << "width" << buttonsVec.back().getGlobalBounds().width << endl;
	buttonsVec.back().setScale({ 0.4, 0.4 });
	buttonsVec.back().setPosition({ pos.x + 15 + (buttonsVec.back().getGlobalBounds().width + 17) * (buttonsVec.size() - 1), pos.y + 6 });
	//buttonsVec.back().setPosition({ pos.x, pos.y });
}


void GUI_ActionPanel::draw(RenderWindow& window)
{
	if (active)
	{
		s_body.setPosition(pos);
		s_body.setTextureRect(IntRect(0, 51, 59, 71));
		window.draw(s_body);
		s_body.setTextureRect(IntRect(0, 0, 59, 51));

		for (unsigned int i = 0; i < buttonsVec.size(); i++)
		{
			if (i != 0)
			{
				s_body.setPosition(pos.x + 59 * i, pos.y);
				window.draw(s_body);
			}

			//buttonsVec[i].load("res/info.png");
			window.draw(buttonsVec[i]);
			//buttonsVec[i].draw(window);
		}

		if (buttonsVec.size() > 1)
		{
			
			s_body.setPosition(pos.x + 59 * buttonsVec.size(), pos.y);
			
		}
		else s_body.setPosition(pos.x + 59 , pos.y);

		s_body.setTextureRect(IntRect(59, 51, 11, 71));
		window.draw(s_body);
	}
}


void GUI_ActionPanel::setActive(bool isActive)
{
	active = isActive;
}

void GUI_ActionPanel::setPos(Vector2f newPos)
{
	pos.x = newPos.x - 33;
	pos.y = newPos.y - 71;
	for (unsigned int i = 0; i < buttonsVec.size(); i++)
	{
		buttonsVec[i].setPosition({ pos.x + 15 + (buttonsVec.back().getGlobalBounds().width + 17) * i, pos.y + 6 });
	}
}

bool GUI_ActionPanel::getIsActive()
{
	return active;
}
