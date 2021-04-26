#include "GUI_Window.h"

GUI_Window::GUI_Window(): GUI_Element(GUIElementsEnum::GUI_WINDOW)
{
	sVec.reserve((int)WindowSegments::AMOUNT);

	defaultViewPos = { 0 + (backgrSize.x - rightSideGap) / 2, 0 + backgrSize.y / 2 };
	windowView.setSize(backgrSize.x - rightSideGap, backgrSize.y);
	windowView.setCenter(defaultViewPos);

	/*addGuiElement(new GUI_Button(UiResEnum::BUTTON_CLOSE), "but_close");
	addGuiElement(new GUI_Button(UiResEnum::BUTTON_UP), "but_up");
	addGuiElement(new GUI_Button(UiResEnum::BUTTON_DOWN), "but_down");*/
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

	assignResToElements(uiResVec, fontsVec, texturesResVec);

	b_close.assignRes(uiResVec);
	b_close.setActive(true);
	b_up.assignRes(uiResVec);
	b_down.assignRes(uiResVec);
	slider.assignRes(uiResVec);

	b_close.setPosition({ pos.x + borderSize + backgrSize.x - b_close.getGlobalBounds().width, (float)borderSize });
	b_up.setPosition({ b_close.getGlobalBounds().left, b_close.getGlobalBounds().top + b_close.getGlobalBounds().height + 5 });
	b_down.setPosition({ b_close.getGlobalBounds().left, backgrSize.y + borderSize - b_down.getGlobalBounds().height});
	slider.setPosition({ b_up.getGlobalBounds().left, b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5 });
	slider.setPathLenght((b_down.getGlobalBounds().top - 5) - (b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5));


	calculateContentOccupySize();
}

void GUI_Window::viewportUpdate(View uiView)
{
	FloatRect rect{ (pos.x + borderSize) / uiView.getSize().x, (pos.y + borderSize) / uiView.getSize().y, (backgrSize.x - rightSideGap) / uiView.getSize().x, backgrSize.y / uiView.getSize().y };
	windowView.setViewport(rect);
}

void GUI_Window::setVerticalPosPercent(float percent)
{
	float endPoint = contentOccupySize.y - windowView.getSize().y / 2;
	float allPath = endPoint - defaultViewPos.y;
	float percentOfPath = allPath / 100;
	windowView.setCenter(defaultViewPos.x, defaultViewPos.y + percentOfPath * percent);
}

float GUI_Window::getVerticalPosPercent()
{
	if (contentOccupySize.y <= windowView.getSize().y)
	{
		return 0.f;
	}
	else
	{
		return (windowView.getCenter().y - defaultViewPos.y) / (((contentOccupySize.y - windowView.getSize().y / 2) - defaultViewPos.y) / 100);
	}
}

void GUI_Window::normalizeOutOfBoundsView()
{
	if (getVerticalPosPercent() < 0) setVerticalPosPercent(0);
	if (getVerticalPosPercent() > 100) setVerticalPosPercent(100);
}

void GUI_Window::calculateContentOccupySize()
{
	for (auto& element : GuiElementsContainer::getElementsVec())
	{
		FloatRect bounds = element->getGlobalElementBounds();
		if (bounds.left + bounds.width > contentOccupySize.x)
			contentOccupySize.x = bounds.left + bounds.width;
		if (bounds.top + bounds.height > contentOccupySize.y)
			contentOccupySize.y = bounds.top + bounds.height;
	}
}

bool GUI_Window::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		viewportUpdate(view);

		if (b_close.update(iec, window, view))
			setActive(false);

		if (b_up.update(iec, window, view))
		{
			windowView.move(0, -30);
			normalizeOutOfBoundsView();
			slider.setPositionPercent(getVerticalPosPercent());
		}
		if (b_down.update(iec, window, view))
		{
			windowView.move(0, 30);
			normalizeOutOfBoundsView();
			slider.setPositionPercent(getVerticalPosPercent());
		}

		if (slider.update(iec, window, view))
			setVerticalPosPercent(slider.getPositionPercent());

		if (beingScrolled) slider.setPositionPercent(getVerticalPosPercent());


		if (contentOccupySize.y > backgrSize.y)
		{
			b_up.setActive(true);
			b_down.setActive(true);
			slider.setActive(true);
		}

		if (getGlobalElementBounds().contains(iec.getMousePos(window, view)))
			updateElements(iec, window, windowView);

		if (getGuiElement<GUI_Button>("but_close")->getIsActivated())
			setActive(false);

		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (!getGlobalElementBounds().contains(iec.getMousePos(window, view)))
				setActive(false);
			
			iec.eventExpire(Mouse::Left);
		}

		beingScrolled = false;
		if (getGlobalElementBounds().contains(iec.getMousePos(window, view)))
		{
			if (iec.getMouseWheelDelta() != 0)
			{
				if (contentOccupySize.y > windowView.getSize().y)
					windowView.move(0, 10 * -iec.getMouseWheelDelta());
				iec.expireMouseWheelDelta();
				beingScrolled = true;
				normalizeOutOfBoundsView();
			}
		}
	}
	return false;
}


void GUI_Window::draw(RenderTarget& target, RenderStates states) const
{
	if (active)
	{
		for (auto& s : sVec)
		{
			target.draw(s);
		}

		target.draw(b_close);
		target.draw(b_up);
		target.draw(b_down);
		target.draw(slider);

		View temp = target.getView();
		target.setView(windowView);

		drawElements(target, states);

		target.setView(temp);
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


FloatRect GUI_Window::getGlobalElementBounds()
{
	return { pos.x, pos.y, backgrSize.x + 2 * borderSize, backgrSize.y + 2 * borderSize };
}
