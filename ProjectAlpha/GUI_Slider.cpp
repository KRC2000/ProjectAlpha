#include "GUI_Slider.h"

void GUI_Slider::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec)
{
	s_slider.setTexture(uiResVec[(int)UiResEnum::GUI_SLIDER]);
	s_slider.setPosition(basePoint);
}

bool GUI_Slider::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		if (getIsCursorInsideOwnerRenderTexture(iec.getMousePos(window, view)))
		{
			Vector2f mousePos;
			if (applyTransform) mousePos = getTransformedMousePos(iec.getMousePos(window, view));
			else mousePos = iec.getMousePos(window, view);

			if ((iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED) &&
				s_slider.getGlobalBounds().contains(mousePos))
			{
				grabbed = true;
				cursorOffset.y = mousePos.y - s_slider.getPosition().y;

				iec.eventExpire(Mouse::Left);
			}

			if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTRELEASED) grabbed = false;


			if (grabbed && s_slider.getPosition().y >= basePoint.y && s_slider.getPosition().y <= basePoint.y + pathLenght)
			{
				s_slider.setPosition({ s_slider.getPosition().x, mousePos.y - cursorOffset.y });
				if (s_slider.getPosition().y < basePoint.y)
					s_slider.setPosition({ s_slider.getPosition().x, basePoint.y });
				if (s_slider.getPosition().y > basePoint.y + pathLenght)
					s_slider.setPosition({ s_slider.getPosition().x, basePoint.y + pathLenght });
				return true;
			}
		}

	}
	return false;
}

void GUI_Slider::draw(RenderTarget& target, RenderStates states) const
{
	if (active)
	{
		target.draw(s_slider);
	}
}

void GUI_Slider::setPositionPercent(float percent)
{
	if (percent >= 0 && percent <= 100)
		s_slider.setPosition({ basePoint.x, basePoint.y + (pathLenght / 100) * percent });
}

void GUI_Slider::setPosition(Vector2f newPos)
{
	s_slider.setPosition(newPos);
	basePoint = newPos;
}


float GUI_Slider::getPositionPercent()
{ 
	return (s_slider.getPosition().y - basePoint.y) / (pathLenght / 100);
}

Sprite* GUI_Slider::getS_slider()
{
	return &s_slider;
}
