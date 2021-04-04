#include "GUI_ItemsListItem.h"

GUI_ItemsListItem::GUI_ItemsListItem(ItemsEnum itemId, int amount, bool reusable, int condition):
	itemId(itemId), amount(amount), reusable(reusable), condition(condition)
{
	
}

void GUI_ItemsListItem::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* textureResVec)
{
	s_box.setTexture(uiResVec[UiResEnum::GUI_ITEMSLISTITEM_CANVAS]);
	s_image.setTexture(textureResVec->at(ResourcesEnum::ITEMS_T));
	s_image.setTextureRect(IntRect(itemId * 100, 0, 100, 100));
	s_image.setScale({ 0.4, 0.4 });
	//if (!f.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;

	itemNameText.setFont(fontsVec->at(UiFontsEnum::PIXELATED_3D_DEFAULT));
	itemNameText.setString(getItemNameString(itemId));
	itemNameText.setCharacterSize(100);
	itemNameText.setScale({ 0.3, 0.3 });
	itemNameText.setFillColor(sf::Color::White);

	amountText.setFont(fontsVec->at(UiFontsEnum::PIXELATED_3D_DEFAULT));
	amountText.setString("x" + to_string(amount));
	amountText.setCharacterSize(100);
	amountText.setScale({ 0.25, 0.25 });
	amountText.setFillColor(sf::Color::White);

	conditionText.setFont(fontsVec->at(UiFontsEnum::PIXELATED_3D_DEFAULT));
	conditionText.setString(to_string(condition) + "%");
	conditionText.setCharacterSize(100);
	conditionText.setScale({ 0.2, 0.2 });
	conditionText.setFillColor(sf::Color::White);
}

bool GUI_ItemsListItem::update(IEC& iec, RenderWindow& window, View& view)
{
	return false;
}

void GUI_ItemsListItem::draw(RenderTarget& target, RenderStates states) const
{
	if (visible)
	{
		target.draw(s_box);

		target.draw(itemNameText);
		target.draw(amountText);
		target.draw(conditionText);
		target.draw(s_image);
	}
}


//void GUI_ItemsListItem::load(vector<Texture>& textureResourcesVec, Font* font)
//{
//	s_box.setTexture(textureResourcesVec.at(ResourcesEnum::ITEMSLISTITEM_T));
//	s_image.setTexture(textureResourcesVec.at(ResourcesEnum::ITEMS_T));
//	s_image.setTextureRect(IntRect(itemId * 100, 0, 100, 100));
//	s_image.setScale({ 0.4, 0.4 });
//	//if (!f.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;
//
//	itemNameText.setFont(*font);
//	itemNameText.setString(getItemNameString(itemId));
//	itemNameText.setCharacterSize(100);
//	itemNameText.setScale({ 0.3, 0.3 });
//	itemNameText.setFillColor(sf::Color::White);
//
//	amountText.setFont(*font);
//	amountText.setString("x" + to_string(amount));
//	amountText.setCharacterSize(100);
//	amountText.setScale({ 0.25, 0.25 });
//	amountText.setFillColor(sf::Color::White);
//
//	conditionText.setFont(*font);
//	conditionText.setString(to_string(condition) + "%");
//	conditionText.setCharacterSize(100);
//	conditionText.setScale({ 0.2, 0.2 });
//	conditionText.setFillColor(sf::Color::White);
//}

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

void GUI_ItemsListItem::setPos(Vector2f pos)
{
	s_box.setPosition(pos);
	s_image.setPosition(pos);
	itemNameText.setPosition({ pos.x + s_image.getGlobalBounds().width, pos.y });
	amountText.setPosition({ pos.x + s_box.getGlobalBounds().width - amountText.getGlobalBounds().width, pos.y});
	conditionText.setPosition({ pos.x + s_box.getGlobalBounds().width - conditionText.getGlobalBounds().width, 
								pos.y + s_box.getGlobalBounds().height - conditionText.getGlobalBounds().height - 6});
}

void GUI_ItemsListItem::move(Vector2f vector)
{
	s_box.move(vector);
	s_image.move(vector);
	itemNameText.move(vector);
	amountText.move(vector);
	conditionText.move(vector);
}

void GUI_ItemsListItem::setTransparencyFade(int alpha)
{
	s_box.setColor({ 255, 255, 255, (Uint8)alpha });
	itemNameText.setFillColor({ 255, 255, 255, (Uint8)alpha });
	amountText.setFillColor({ 255, 255, 255, (Uint8)alpha });
	conditionText.setFillColor({ 255, 255, 255, (Uint8)alpha });
}

void GUI_ItemsListItem::increaseTransparencyFade(int alpha)
{
	int res = s_box.getColor().a + alpha;
	if (res > 255) res = 255; if (res < 0) res = 0;
	s_box.setColor({ 255, 255, 255, (Uint8)res });
	itemNameText.setFillColor({ 255, 255, 255, (Uint8)res });
	amountText.setFillColor({ 255, 255, 255, (Uint8)res });
	conditionText.setFillColor({ 255, 255, 255, (Uint8)res });
}

int GUI_ItemsListItem::getAlpha()
{
	return s_box.getColor().a;
}

Sprite* GUI_ItemsListItem::getSpriteBox()
{
	return &s_box;
}

string GUI_ItemsListItem::getItemNameString(ItemsEnum itemId)
{
	string str;
	switch (itemId)
	{
	case ItemsEnum::TUNA:
		str = "Canned tuna";
		break;
	case ItemsEnum::MUSHROOM:
		str = "Mushroom";
		break;
	case ItemsEnum::CORN:
		str = "Corn";
		break;
	case ItemsEnum::BEER:
		str = "Bottle of beer";
		break;
	case ItemsEnum::PILLSJAR:
		str = "Jar of pills";
		break;
	default:
		str = "Unknown Item";
		break;
	}

	return str;
}
