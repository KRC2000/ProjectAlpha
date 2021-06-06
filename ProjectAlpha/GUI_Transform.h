#pragma once
#include <SFML/Graphics.hpp>

using namespace sf; 

/*
*/
struct GUI_Transform
{
	RenderTexture* render_t = nullptr;
	Sprite* render_tHolder = nullptr;

	GUI_Transform(RenderTexture& render_t, Sprite& render_tHolder)
		: render_t(&render_t), render_tHolder(&render_tHolder)
	{};
};