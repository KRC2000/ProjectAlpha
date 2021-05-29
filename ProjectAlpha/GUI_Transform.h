#pragma once
#include <SFML/Graphics.hpp>

using namespace sf; 

struct GUI_Transform
{
	RenderTexture* render_t = nullptr;
	Sprite* render_tHolder = nullptr;;

	GUI_Transform(RenderTexture& render_t, Sprite& render_tHolder)
		: render_t(&render_t), render_tHolder(&render_tHolder)
	{};

	Vector2f applyTransform(Vector2f point)
	{
		point -= render_tHolder->getPosition();
		point = render_t->mapPixelToCoords((Vector2i)point);
		return point;
	}
};