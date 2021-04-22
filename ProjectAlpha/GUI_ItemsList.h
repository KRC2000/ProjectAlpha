#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_ItemsListItem.h"
#include "GUI_Button.h"
#include "GUI_Element.h"
#include "Storage.h"
#include "GUI_Slider.h"
#include "UiFontsEnum.h"

// This class was invented by nazis as a practical joke, to torture every soul that
// will try to understand it. You may try to understand it, but only if diameter 
// of your balls is more than 35cm. Otherwise can't say where you'll end up.
// Extremely needs to be re-write. But until then... 
// Update: Now its actually pretty good :/
class GUI_ItemsList: public GUI_Element
{
	// Global textures storage reference to spread among object's load() functions
	vector<Texture>* textureResVec = nullptr;
	vector<Texture>* uiResVec = nullptr;

	// Items list background canvas sprite
	Sprite s_border;

	// The gap that s_border bounds are modified with, when checking 
	// if items list item is intersects with s_border. It exists so 
	// items list items fade-in and fad-out not on the edge, but inside of s_boder
	// So far used only in isBorderIntersectsWithItem()
	float fadeGap = 10;

	// If "true" - item list allowed to update and draw itself
	bool active = false;


	GUI_Button upListButton{ UiResEnum::GUI_ITEMLIST_BUTTON_UPLIST, "Up" };
	GUI_Button downListButton{ UiResEnum::GUI_ITEMLIST_BUTTON_DOWNLIST, "Down" };
	GUI_Slider slider;

	float onePercentLenght{ 0 };

	// Font reference to spread among object's load() functions(those who got drawable Text objects)
	vector<Font>* uiFontsVec = nullptr;
	//Font* guiFont1 = nullptr;

	// Reference to Storage object that contains items that should be displayed by items list
	// If == nullptr then items list display nothing
	Storage* assignedStorage = nullptr;

	vector<GUI_ItemsListItem> itemsVec;

	Vector2f baseUpperEdgePoint, baseDownEdgePoint;

	Vector2f createPos;

	// Gap between items-list items background sprites
	float distanceBetweenItems = 2;

	float itemSizeY = 60;

	bool beingScrolled = false;

	// Pixel length from top of first items-list item to bottom of last one
	// including distanceBetweenItems gaps
	float itemListLenght{0};
public:
	GUI_ItemsList():GUI_Element(GUIElementsEnum::GUI_ITEMLIST) {};
	virtual ~GUI_ItemsList() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* textureResVec = nullptr) override;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;



	//void load(vector<Texture>* texturesResourcesVec, vector<Texture>& uiResVec, Vector2f pos, vector<Font>* uiFontsVec);
	
	// Clears items-list items vector, and creates new items according to storage
	void assignStorage(Storage* storage);

	void moveItems(Vector2f factor);
	void setItemsPos(Vector2f newPos);

	/* Call after deleting item from list.
	 Lifts all Items after deleted one by 1 * itemHeight
	 taleStartIndex - all next, including this, will be lifted
	 recalculateItemListLenght() called inside, no need to repeat*/
	void liftItemsTale(unsigned int taleStartIndex);

	//void update(IEC & iec, RenderWindow& window, View& view);
	//void draw(RenderWindow& window);

	void scrollUp();
	void scrollDown();

	/* Must be called after any items-list length change: adding or deleting items so
	 scrolling and GUI_Slider can work properly*/
	void recalculateItemListLenght();

	/*itemVecIndex - index of the item in both GUI_ItemsListItem and assignedStorage vectors.
	Deletes both GUI_ItemsListItem and Item, from assigned to item list storage*/
	Item deleteItem(unsigned int itemVecIndex);
	Item deleteItem(GUI_ItemsListItem* listItem);

	/*Creating new GUI_ItemListItem that represents passed Item newItem*/
	void addItem(Item& newItem);

	/* See setPositionPercent(). Used when content is scrolled with mouse wheel,
	 so it's sliders turn to move on same related distance as content moved.
	 This function returns this distance in percents*/
	float getPositionPercent();
	
	/*If cursor is on item inside a item list - returns true*/
	bool isCursorPointingAtItem(Vector2f mousePos);

	/* Advanced shortcut for s_border.getGlobalBounds().intersects(itemsVec[i].getSprite()->getGlobalBounds)
	 with a little bounds tweak*/
	bool isBorderIntersectsWithItem(int itemVectorIndex) const;

private:
	void reassignListItemsToStorageItems();
public:

	////////// SETTERS

	void setPosition(Vector2f pos);
	void setActive(bool active) { this->active = active; };

	/* Scrolling content for "percent" percents of all content list length
	 GUI_Slider passes how much percents he is scrolled, and with this function
	 content get scrolled same amount of percents*/
	void setPositionPercent(float percent);

	//////////////////

	////////// GETTERS

	bool getIsActive() { return active; };

	// Reference to background sprite
	Sprite* getBorderSprite() { return &s_border; };
	Storage* getAssignedStorage() { return assignedStorage; };

	bool isBeingScrolled() { return beingScrolled; };

	vector<GUI_ItemsListItem>& getItemsVec() { return itemsVec; };

	unsigned int getItemIndexCursorPointingAt(Vector2f mousePos);

	//////////////////


};

