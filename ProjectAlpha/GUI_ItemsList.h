#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_ItemsListItem.h"
#include "Button.h"
#include "Storage.h"
#include "Slider.h"
#include "GUI_ItemsListItem.h"

// This class was invented by nazis as a practical joke, to torture every soul that
// will try to understand it. You may try to understand it, but only if diameter 
// of your balls is more than 35cm. Otherwise can't say where you'll end up.
// Extremely needs to be re-write. But until then... 
class GUI_ItemsList
{
	// Global textures storage reference to spread among object's load() functions
	vector<Texture> * resourcesVec;

	// Items list background canvas sprite
	Sprite s_border;

	// The gap that s_border bounds are modified with, when checking 
	// if items list item is intersects with s_border. It exists so 
	// items list items fade-in and fad-out not on the edge, but inside of s_boder
	// So far used only in isBorderIntersectsWithItem()
	float fadeGap = 80;

	// If "true" - item list allowed to update and draw itself
	bool active = false;


	Button upListButton, downListButton;
	Slider slider;

	// Font reference to spread among object's load() functions(those who got drawable Text objects)
	Font* guiFont1;

	// Reference to Storage object that contains items that should be displayed by items list
	// If == nullptr then items list display nothing
	Storage* assignedStorage;

	vector<GUI_ItemsListItem> itemsVec;

	// Gap between items-list items background sprites
	float distanceBetweenItems = 2;

	// Pixel length from top of first items-list item to bottom of last one
	// including distanceBetweenItems gaps
	float itemListLenght;
public:
	GUI_ItemsList();
	void load(vector<Texture>* texturesResourcesVec, Vector2f pos, Font* font);
	
	// Clears items-list items vector, and creates new items according to storage
	void assignStorage(Storage* storage);

	void moveItems(Vector2f factor);

	void update(IEC & iec, RenderWindow& window, View& view);
	void draw(RenderWindow& window);

	void scrollUp();
	void scrollDown();

	// Must be called after any items-list length change: adding or deleting items so
	// scrolling and slider can work properly
	void recalculateItemListLenght();

	// Returns same item as deleted one.
	Item deleteItem(float itemSizeY, Vector2f mousePos);

	void addItem(Item newItem);

	////////// SETTERS

	void setPosition(Vector2f pos);
	void setActive(bool active);

	// Scrolling content for "percent" percents of all content list length
	// Slider passes how much percents he is scrolled, and with this function
	// content get scrolled same amount of percents
	void setPositionPercent(float percent);

	//////////////////

	////////// GETTERS

	// Reference to background sprite
	Sprite* getBorderSprite();
	Storage* getAssignedStorage();

	// See setPositionPercent(). Used when content is scrolled with mouse wheel,
	// so it's sliders turn to move on same related distance as content moved
	float getPositionPercent();

	// Advanced shortcut for s_border.getGlobalBounds().intersects(itemsVec[i].getSprite()->getGlobalBounds)
	// with a little bounds tweak
	bool isBorderIntersectsWithItem(int itemVectorIndex);

	//////////////////


};

