#pragma once
#include "PrecompiledHeaders.h"

class Item
{
	ItemsEnum itemId;
	int amount = 1;
	bool reusable;
	// 1-100% 
	int condition = 100;
public:
	Item(ItemsEnum itemId, int amount = 1, bool reusable = false, int condition = 100);

	void setAmount(int newAmount);
	void setCondition(int newCondition);

	ItemsEnum getId();

	//Only if item is NOT reusable
	int getAmount();

	bool getIsReusable();

	//Only if item IS reusable
	int getCondition();
};

