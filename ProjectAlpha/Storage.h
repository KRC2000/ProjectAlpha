#pragma once
#include "PrecompiledHeaders.h"
#include "Item.h"

// Represents a vector of class Item, and interface for interacting
class Storage
{
	vector<Item> itemsVec{0};
public:
	Storage();

	// push_back an item to the items vector
	void addItem(Item item);

	// erasing an item from vector on index
	void deleteItem(int itemIndex);


	////////// GETTERS

	vector<Item>* getItemsVec();
	Item* getItem(int index);

	//////////////////
};

