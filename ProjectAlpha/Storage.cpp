#include "Storage.h"

Storage::Storage()
{
	itemsVec.reserve(20);
}

void Storage::addItem(Item item)
{
	itemsVec.push_back(item);
}

void Storage::deleteItem(int itemIndex)
{
	itemsVec.erase(itemsVec.begin() + itemIndex );
}

vector<Item>* Storage::getItemsVec()
{
	return &itemsVec;
}

Item* Storage::getItem(int index)
{
	return &itemsVec[index];
}
