#pragma once
//#include "PrecompiledHeaders.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "IEC.h"

class GUI_Element: public sf::Drawable
{
public:
	GUI_Element() {};
	virtual ~GUI_Element() {};

	virtual void assignTextureRes(std::vector<sf::Texture>& textureResourcesVec) = 0;
	virtual void update(IEC& iec, sf::RenderWindow& window, sf::View& view) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

