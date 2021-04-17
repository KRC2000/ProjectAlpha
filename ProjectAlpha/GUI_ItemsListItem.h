#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Element.h"
#include "UiResEnum.h"
#include "UiFontsEnum.h"

class GUI_ItemsListItem: public GUI_Element
{
	Sprite s_box, s_image;
	Text itemNameText, amountText, conditionText;

	Clock fadeTimer;

	ItemsEnum itemId;
	int amount, condition;
	bool reusable;
	bool visible = true;
public:
	GUI_ItemsListItem(ItemsEnum itemId, int amount, bool reusable, int condition) :
		GUI_Element(GUIElementsEnum::GUI_ITEMLISTITEM), 
		itemId(itemId), amount(amount), reusable(reusable), condition(condition) {};

	virtual ~GUI_ItemsListItem() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* textureResVec = nullptr) override;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	void fadeIn();
	void fadeOut();

	void setPos(Vector2f pos);
	void move(Vector2f vector);

	// Basically sets alpha RGBA component, but in percents
	void setTransparencyFade(int percent);

	// Basically increments alpha RGBA component, but in percents
	void increaseTransparencyFade(int percent);

	int getAlpha();
	Vector2f getPos() { return s_box.getPosition(); };
	const Sprite* getSpriteBox() const;

private:
	string getItemNameString(ItemsEnum itemId);
};

