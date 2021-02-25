#include "Item.h"


Item::Item(ItemsEnum itemId, int amount, bool reusable, int condition):
	itemId(itemId), amount(amount), reusable(reusable), condition(condition)
{
}


void Item::setAmount(int newAmount)
{
	amount = newAmount;
}

void Item::setCondition(int newCondition)
{
	condition = newCondition;
}


ItemsEnum Item::getId()
{
	return itemId;
}

int Item::getAmount()
{
	return amount;
}

bool Item::getIsReusable()
{
	return reusable;
}

int Item::getCondition()
{
	return condition;
}
