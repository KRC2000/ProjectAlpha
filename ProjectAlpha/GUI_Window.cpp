#include "GUI_Window.h"

GUI_Window::GUI_Window(GUI_Element* owner): 
	GUI_Element(GUIElementsEnum::GUI_WINDOW, owner),
	GUI_RenderTextureContainer(rt, rts)
{
	sVec.reserve((int)WindowSegments::AMOUNT);


	if (rt.create(2000, 2000)) cout << "CREATED\n";
	rts.setTexture(rt.getTexture());
	rts.setTextureRect(IntRect(0, 0, backgrSize.x - rightSideGap, backgrSize.y));
	defaultViewPos = { 0, 0 };

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

	b_close.setApplyTransform(true);
	b_up.setApplyTransform(true);
	b_down.setApplyTransform(true);
	slider.setApplyTransform(true);
	GUI_RenderTextureContainer* owner_rtc = dynamic_cast<GUI_RenderTextureContainer*>(GUI_Element::owner);
	if (owner_rtc)
	{
		b_close.applyTransformOnInteraction(owner_rtc->getParentalTransforms());
		b_up.applyTransformOnInteraction(owner_rtc->getParentalTransforms());
		b_down.applyTransformOnInteraction(owner_rtc->getParentalTransforms());
		slider.applyTransformOnInteraction(owner_rtc->getParentalTransforms());
	}

	recalculateContentOccupySize();
}


void GUI_Window::normalizeOutOfBoundsView()
{
	if (getVerticalPosPercent() < 0) setVerticalPosPercent(0);
	if (getVerticalPosPercent() > 100) setVerticalPosPercent(100);
}

void GUI_Window::recalculateContentOccupySize()
{
	Vector2f occupySize{0, 0};
	for (auto& element : GuiElementsContainer::getElementsVec())
	{
		if (element->isActive())
		{
			FloatRect bounds = element->getGlobalElementBounds();
			if (bounds.left + bounds.width > occupySize.x)
				occupySize.x = bounds.left + bounds.width;
			if (bounds.top + bounds.height > occupySize.y)
				occupySize.y = bounds.top + bounds.height;
		}
	}
	contentOccupySize = occupySize;

	slider.setPositionPercent(getVerticalPosPercent());
}

bool GUI_Window::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		if (b_close.update(iec, window, view))
			setActive(false);

		if (b_up.update(iec, window, view))
		{
			IntRect rect = { rts.getTextureRect().left, rts.getTextureRect().top - 30, rts.getTextureRect().width, rts.getTextureRect().height };
			rts.setTextureRect(rect);
			//rtView.move(0, -30);
			normalizeOutOfBoundsView();
			slider.setPositionPercent(getVerticalPosPercent());
		}
		if (b_down.update(iec, window, view))
		{
			IntRect rect = { rts.getTextureRect().left, rts.getTextureRect().top + 30, rts.getTextureRect().width, rts.getTextureRect().height };
			rts.setTextureRect(rect);
			//rtView.move(0, 30);
			normalizeOutOfBoundsView();
			slider.setPositionPercent(getVerticalPosPercent());
		}

		if (slider.update(iec, window, view))
			setVerticalPosPercent(slider.getPositionPercent());

		if (beingScrolled) slider.setPositionPercent(getVerticalPosPercent());

		if (timer.getElapsedTime().asMilliseconds() > 100)
		{
			timer.restart();
			float posPercent = getVerticalPosPercent();
			if (posPercent > 100)
			{
				setVerticalPosPercent(posPercent - 1);
				slider.setPositionPercent(getVerticalPosPercent());
			}
			if (posPercent > 99 && posPercent < 101)
				setVerticalPosPercent(100);

			recalculateContentOccupySize();
		}

		if (contentOccupySize.y > backgrSize.y)
		{
			b_up.setActive(true);
			b_down.setActive(true);
			slider.setActive(true);
		}
		else
		{
			b_up.setActive(false);
			b_down.setActive(false);
			slider.setActive(false);
			rts.setTextureRect({ 0, 0, rts.getTextureRect().width, rts.getTextureRect().height });
		}

		//if (getGlobalElementBounds().contains(iec.getMousePos(window, view)))
		updateElements(iec, window, view);
		//Transform t =  rtView.getTransform();
		 
		//View v;
		//v.reset({ rts.getPosition().x, rts.getPosition().y, (float)rt.getSize().x, (float)rt.getSize().y });

		//rtView.setViewport({(pos.x + borderSize) / view.getSize().x, (pos.y + borderSize) / view.getSize().y, backgrSize.x / view.getSize().x, backgrSize.y / view.getSize().y });


		/*if (getGuiElement<GUI_Button>("but_close")->getIsActivated())
			setActive(false);*/

		//if (getGuiElement<GUI_Button>("but_close")->getIsActivated())
			//setActive(false);

		/*if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (!getGlobalElementBounds().contains(iec.getMousePos(window, view)))
				setActive(false);
			
			iec.eventExpire(Mouse::Left);
		}*/

		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (sVec[(int)WindowSegments::DOWNRIGHT_C].getGlobalBounds().contains(getTransformedMousePos(iec.getMousePos(window, view))))
			{
				resized = true;
				grabOffset = getTransformedMousePos(iec.getMousePos(window, view)) - sVec[(int)WindowSegments::DOWNRIGHT_C].getPosition();
			}

		}

		if (resized)
		{
			Vector2f border{ (float)borderSize, (float)borderSize };
			Vector2f newSize = getTransformedMousePos(iec.getMousePos(window, view)) - (pos + border) - grabOffset;
			setSize(newSize);
			cout << newSize.x << " \\\ " << newSize.y << endl;
		}

		
		
		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
		{
			if (sVec[(int)WindowSegments::UP].getGlobalBounds().contains(getTransformedMousePos(iec.getMousePos(window, view))))
			{
				grabbed = true;
				grabOffset = getTransformedMousePos(iec.getMousePos(window, view)) - pos;
			}

		}

		if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTRELEASED)
		{
			if (grabbed) grabbed = false;
			if (resized) resized = false;
		}

		if (grabbed)
		{
			setPos(getTransformedMousePos(iec.getMousePos(window, view)) - grabOffset);
			if (owner)
			{
				dynamic_cast<GUI_Window*>(owner)->recalculateContentOccupySize();
			}
		}

		beingScrolled = false;
		if (getGlobalElementBounds().contains(iec.getMousePos(window, view)))
		{
			if (iec.getMouseWheelDelta() != 0)
			{
				//if (contentOccupySize.y > rtView.getSize().y)
				if (contentOccupySize.y > rts.getTextureRect().height)
				{
					IntRect rect = { rts.getTextureRect().left, rts.getTextureRect().top + 10 * -iec.getMouseWheelDelta(), rts.getTextureRect().width, rts.getTextureRect().height };
					rts.setTextureRect(rect);
				}
					//rtView.move(0, 10 * -iec.getMouseWheelDelta());
				iec.expireMouseWheelDelta();
				beingScrolled = true;
				normalizeOutOfBoundsView();
			}
		}


		//rt.setView(rtView);
		rt.setRepeated(false);
		rt.clear({0, 0, 0, 0});
		drawElements(rt);
		rt.display();

		rts.setTexture(rt.getTexture());
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

		target.draw(rts);
		//View temp = target.getView();
		//target.setView(windowView);
		

		//drawElements(rt);

		//target.setView(temp);
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

	b_close.setPosition({ pos.x + borderSize + backgrSize.x - b_close.getGlobalBounds().width, pos.y + borderSize });
	b_up.setPosition({ b_close.getGlobalBounds().left, b_close.getGlobalBounds().top + b_close.getGlobalBounds().height + 5 });
	b_down.setPosition({ b_close.getGlobalBounds().left, pos.y + backgrSize.y + borderSize - b_down.getGlobalBounds().height });
	slider.setPosition({ b_up.getGlobalBounds().left, b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5 });
	slider.setPathLenght((b_down.getGlobalBounds().top - 5) - (b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5));
	slider.setPositionPercent(getVerticalPosPercent());

	rts.setPosition({ pos.x + borderSize, pos.y + borderSize });

	recalculateContentOccupySize();

	GUI_Window* ownerWindow = dynamic_cast<GUI_Window*>(owner);
	if (ownerWindow) ownerWindow->recalculateContentOccupySize();
}

void GUI_Window::setSize(Vector2f newSize)
{
	backgrSize = newSize;
	
	rts.setTextureRect(IntRect(rts.getTextureRect().left, rts.getTextureRect().top, backgrSize.x - rightSideGap, backgrSize.y));

	//if (rt.create(backgrSize.x - rightSideGap, backgrSize.y)) cout << "CREATED\n";
	//rtView.setSize(rt.getSize().x, rt.getSize().y);
	//defaultViewPos = { (float)rt.getSize().x / 2, (float)rt.getSize().y / 2 };
	//rtView.setCenter(defaultViewPos);


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
	sVec[(int)WindowSegments::RIGHT].setOrigin(0, borderSize);

	sVec[(int)WindowSegments::BACKGR].setTextureRect(IntRect(0, 0, backgrSize.x, backgrSize.y));

	b_close.setPosition({ pos.x + borderSize + backgrSize.x - b_close.getGlobalBounds().width, (float)borderSize });
	b_up.setPosition({ b_close.getGlobalBounds().left, b_close.getGlobalBounds().top + b_close.getGlobalBounds().height + 5 });
	b_down.setPosition({ b_close.getGlobalBounds().left, backgrSize.y + borderSize - b_down.getGlobalBounds().height });
	slider.setPosition({ b_up.getGlobalBounds().left, b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5 });
	slider.setPathLenght((b_down.getGlobalBounds().top - 5) - (b_up.getGlobalBounds().top + b_up.getGlobalBounds().height + 5));
	slider.setPositionPercent(getVerticalPosPercent());

	setPos(pos);

	recalculateContentOccupySize();

	

	GUI_Window* ownerWindow = dynamic_cast<GUI_Window*>(owner);
	if (ownerWindow) ownerWindow->recalculateContentOccupySize();
}

void GUI_Window::setActive(bool isActive)
{
	if (owner)
	{
		GUI_Window* win = dynamic_cast<GUI_Window*>(owner);
		if (win)
		{
			win->recalculateContentOccupySize();
		}
	}
	this->active = isActive;
}


FloatRect GUI_Window::getGlobalElementBounds()
{
	return { pos.x, pos.y, backgrSize.x + 2 * borderSize, backgrSize.y + 2 * borderSize };
}

void GUI_Window::setVerticalPosPercent(float percent)
{
	//float endPoint = contentOccupySize.y - rtView.getSize().y / 2;
	float endPoint = contentOccupySize.y - rts.getTextureRect().height;
	float allPath = endPoint - defaultViewPos.y;
	float percentOfPath = allPath / 100;
	IntRect rect = { (int)defaultViewPos.x , (int)(defaultViewPos.y + percentOfPath * percent), rts.getTextureRect().width, rts.getTextureRect().height };
	rts.setTextureRect(rect);
	//rtView.setCenter(defaultViewPos.x, defaultViewPos.y + percentOfPath * percent);
}

float GUI_Window::getVerticalPosPercent()
{
	//if (contentOccupySize.y <= rtView.getSize().y)
	if (contentOccupySize.y <= rts.getTextureRect().height)
	{
		return 0.f;
	}
	else
	{
		//return (rtView.getCenter().y - defaultViewPos.y) / (((contentOccupySize.y - rtView.getSize().y / 2) - defaultViewPos.y) / 100);
		return (rts.getTextureRect().top / ((contentOccupySize.y - rts.getTextureRect().height) / 100));
	}
}