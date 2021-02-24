#pragma once
#include "PrecompiledHeaders.h"
#include "Item.h"

class Storage
{
	vector<Item> itemsVec;
public:
	Storage();
	void addItem(Item item);
	void deleteItem(int itemIndex);

	vector<Item>* getItemsVec();
	Item* getItem(int index);
};

