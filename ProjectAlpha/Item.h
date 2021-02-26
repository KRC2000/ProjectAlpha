#pragma once
#include "PrecompiledHeaders.h"

// Logical reference of in-game inventory item. 
class Item
{
	// See ItemsEnum.h
	ItemsEnum itemId = ItemsEnum::UNKNOWN;
	int amount = 1;

	// If true - item can be used multiple times, involve condition var.
	bool reusable = false;

	// In use only if reusable = true. Describes percentage : 0 - 100% 
	int condition = 100;
public:
	Item();
	// Temporary!!! if new item used to be reusable, amount must = 1
	Item(ItemsEnum itemId, int amount = 1, bool reusable = false, int condition = 100);

	////////// SETTERS

	void setAmount(int newAmount);
	void setCondition(int newCondition);

	//////////////////


	////////// GETTERS

	ItemsEnum getId();
	//Only if item is NOT reusable
	int getAmount();
	bool getIsReusable();

	//Only if item IS reusable
	int getCondition();

	//////////////////

};

