#include "GUI_ItemsListItem.h"

GUI_ItemsListItem::GUI_ItemsListItem(ItemsEnum itemId, int amount, bool reusable, int condition):
	itemId(itemId), amount(amount), reusable(reusable), condition(condition)
{
	
}


void GUI_ItemsListItem::load(vector<Texture>& textureResourcesVec, Font* font)
{
	boxSprite.setTexture(textureResourcesVec.at(ResourcesEnum::ITEMSLISTITEM_T));
	//if (!f.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;

	itemNameText.setFont(*font);
	itemNameText.setString(getItemNameString(itemId));
	itemNameText.setCharacterSize(100);
	itemNameText.setScale({ 0.3, 0.3 });
	itemNameText.setFillColor(sf::Color::White);

	amountText.setFont(*font);
	amountText.setString("x" + to_string(amount));
	amountText.setCharacterSize(100);
	amountText.setScale({ 0.25, 0.25 });
	amountText.setFillColor(sf::Color::White);

	conditionText.setFont(*font);
	conditionText.setString(to_string(condition) + "%");
	conditionText.setCharacterSize(100);
	conditionText.setScale({ 0.2, 0.2 });
	conditionText.setFillColor(sf::Color::White);
}

void GUI_ItemsListItem::fadeIn()
{
	visible = true;
	if (getAlpha() < 255)
	{
		if (fadeTimer.getElapsedTime().asMilliseconds() > 10)
		{
			increaseTransparencyFade(8);
			fadeTimer.restart();
		}
	}
	else setTransparencyFade(255);
}

void GUI_ItemsListItem::fadeOut()
{
	
	if (getAlpha() > 0)
	{
		if (fadeTimer.getElapsedTime().asMilliseconds() > 10)
		{
			increaseTransparencyFade(-15);
			fadeTimer.restart();
		}
	}
	else
	{
		setTransparencyFade(0);
		visible = false;
	}
}

void GUI_ItemsListItem::update(IEC& iec)
{
}

void GUI_ItemsListItem::draw(RenderWindow& window)
{
	if (visible)
	{
		window.draw(boxSprite);

		window.draw(itemNameText);
		window.draw(amountText);
		window.draw(conditionText);
	}
}

void GUI_ItemsListItem::setPos(Vector2f pos)
{
	boxSprite.setPosition(pos);
	itemNameText.setPosition(pos);
	amountText.setPosition({ pos.x + boxSprite.getGlobalBounds().width - amountText.getGlobalBounds().width, pos.y});
	conditionText.setPosition({ pos.x + boxSprite.getGlobalBounds().width - conditionText.getGlobalBounds().width, 
								pos.y + boxSprite.getGlobalBounds().height - conditionText.getGlobalBounds().height - 6});
}

void GUI_ItemsListItem::move(Vector2f vector)
{
	boxSprite.move(vector);
	itemNameText.move(vector);
	amountText.move(vector);
	conditionText.move(vector);
}

void GUI_ItemsListItem::setTransparencyFade(int alpha)
{
	boxSprite.setColor({ 255, 255, 255, (Uint8)alpha });
	itemNameText.setFillColor({ 255, 255, 255, (Uint8)alpha });
	amountText.setFillColor({ 255, 255, 255, (Uint8)alpha });
	conditionText.setFillColor({ 255, 255, 255, (Uint8)alpha });
}

void GUI_ItemsListItem::increaseTransparencyFade(int alpha)
{
	int res = boxSprite.getColor().a + alpha;
	if (res > 255) res = 255; if (res < 0) res = 0;
	boxSprite.setColor({ 255, 255, 255, (Uint8)res });
	itemNameText.setFillColor({ 255, 255, 255, (Uint8)res });
	amountText.setFillColor({ 255, 255, 255, (Uint8)res });
	conditionText.setFillColor({ 255, 255, 255, (Uint8)res });
}

int GUI_ItemsListItem::getAlpha()
{
	return boxSprite.getColor().a;
}

Sprite* GUI_ItemsListItem::getSpriteBox()
{
	return &boxSprite;
}

string GUI_ItemsListItem::getItemNameString(ItemsEnum itemId)
{
	string str;
	switch (itemId)
	{
	case ItemsEnum::KNIFE:
		str = "Knife";
		break;
	case ItemsEnum::BRICK:
		str = "Brick";
		break;
	case ItemsEnum::SHIRT:
		str = "Shirt";
		break;
	default:
		str = "Unknown Item";
		break;
	}

	return str;
}
