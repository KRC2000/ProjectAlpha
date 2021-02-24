#include "Slider.h"

Slider::Slider()
{
}

void Slider::load(Vector2f basePoint, float pathLenght)
{
	t_slider.loadFromFile("res/listScrollBar.png");
	s_slider.setTexture(t_slider);
	s_slider.setPosition(basePoint);

	this->basePoint = basePoint;
	this->pathLenght = pathLenght - s_slider.getGlobalBounds().height;
}

bool Slider::update(IEC& iec, RenderWindow& window, View& view)
{
	if (iec._LMB && s_slider.getGlobalBounds().contains(iec.getMousePos(window, view)))
	{
		grabbed = true;
		cursorOffset.y = iec.getMousePos(window, view).y - s_slider.getPosition().y;

		iec._LMB = false;
	}
	if (iec.LMB_) grabbed = false;
		

	if (grabbed && s_slider.getPosition().y >= basePoint.y && s_slider.getPosition().y <= basePoint.y + pathLenght)
	{
		s_slider.setPosition({ s_slider.getPosition().x, iec.getMousePos(window, view).y - cursorOffset.y });
		if (s_slider.getPosition().y < basePoint.y) 
			s_slider.setPosition({ s_slider.getPosition().x, basePoint.y });
		if (s_slider.getPosition().y > basePoint.y + pathLenght) 
			s_slider.setPosition({ s_slider.getPosition().x, basePoint.y + pathLenght});
		return true;
	}
	return false;
}

void Slider::draw(RenderWindow& window)
{
	window.draw(s_slider);
}

void Slider::setPositionPercent(float percent)
{
	if ((int)getPositionPercent() > (int)percent)
	{
		s_slider.move(0, -1);
	}
	if ((int)getPositionPercent() < (int)percent)
	{
		s_slider.move(0, 1);
	}

	if (percent < 1)
	{
		s_slider.setPosition(basePoint);
	}
	if (percent > 99)
	{
		s_slider.setPosition({ basePoint.x, basePoint.y + pathLenght});
	}
	
}


float Slider::getPositionPercent()
{ 
	return (s_slider.getPosition().y - basePoint.y) / (pathLenght / 100);
}

Sprite* Slider::getS_slider()
{
	return &s_slider;
}
