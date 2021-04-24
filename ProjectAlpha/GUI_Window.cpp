#include "GUI_Window.h"

GUI_Window::GUI_Window(): GUI_Element(GUIElementsEnum::GUI_WINDOW)
{
	sVec.reserve((int)WindowSegments::AMOUNT);
}


void GUI_Window::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec)
{
	Texture* back = &uiResVec[(int)UiResEnum::GUI_WINDOW_BACKGR];
	Texture* borders = &uiResVec[(int)UiResEnum::GUI_WINDOW_BORDERS];

	borderSize = borders->getSize().y / 2;

	back->setRepeated(true);
	borders->setRepeated(true);

	for (int i = 0; i < (int)WindowSegments::AMOUNT; i++)
	{
		sVec.push_back(Sprite());
		if (i != (int)WindowSegments::BACKGR)
			sVec.back().setTexture(*borders);
		else
			sVec.back().setTexture(*back);
	}
	
	sVec[(int)WindowSegments::UPLEFT_C].setTextureRect(IntRect(0, 0, borderSize, borderSize));
	sVec[(int)WindowSegments::UPRIGHT_C].setTextureRect(IntRect(borderSize, 0, -borderSize, borderSize));
	sVec[(int)WindowSegments::DOWNLEFT_C].setTextureRect(IntRect(0, borderSize, borderSize, -borderSize));
	sVec[(int)WindowSegments::DOWNRIGHT_C].setTextureRect(IntRect(borderSize, borderSize, -borderSize, -borderSize));

	sVec[(int)WindowSegments::UP].setTextureRect(IntRect(0, borderSize, backgrSize.x, borderSize));
	sVec[(int)WindowSegments::DOWN].setTextureRect(IntRect(0, borderSize * 2, backgrSize.x, -borderSize));

	sVec[(int)WindowSegments::LEFT].setTextureRect(IntRect(0, borderSize, backgrSize.y, borderSize));
	sVec[(int)WindowSegments::LEFT].setRotation(-90);
	sVec[(int)WindowSegments::LEFT].setOrigin(backgrSize.y, 0);

	sVec[(int)WindowSegments::RIGHT].setTextureRect(IntRect(0, borderSize, backgrSize.y, borderSize));
	sVec[(int)WindowSegments::RIGHT].setRotation(90);
	sVec[(int)WindowSegments::RIGHT].setOrigin( 0, borderSize);

	sVec[(int)WindowSegments::BACKGR].setTextureRect(IntRect(0, 0, backgrSize.x, backgrSize.y));

	setPos(pos);
}

void GUI_Window::draw(RenderTarget& target, RenderStates states) const
{
	for (auto& s : sVec)
	{
		target.draw(s);
	}
}

void GUI_Window::setPos(Vector2f newPos)
{
	pos = newPos;
	sVec[(int)WindowSegments::UPLEFT_C].setPosition(pos);
	sVec[(int)WindowSegments::UP].setPosition(pos.x + borderSize, pos.y);
	sVec[(int)WindowSegments::RIGHT].setPosition(pos.x + borderSize + backgrSize.x, pos.y + borderSize);
	sVec[(int)WindowSegments::LEFT].setPosition(pos.x, pos.y + borderSize);
	sVec[(int)WindowSegments::UPRIGHT_C].setPosition(pos.x + borderSize + backgrSize.x, pos.y);
	sVec[(int)WindowSegments::DOWNLEFT_C].setPosition(pos.x, pos.y + borderSize + backgrSize.y);
	sVec[(int)WindowSegments::DOWN].setPosition(pos.x + borderSize, pos.y + borderSize + backgrSize.y);
	sVec[(int)WindowSegments::DOWNRIGHT_C].setPosition(pos.x + borderSize + backgrSize.x, pos.y + borderSize + backgrSize.y);
	sVec[(int)WindowSegments::BACKGR].setPosition(pos.x + borderSize, pos.y + borderSize);
}

