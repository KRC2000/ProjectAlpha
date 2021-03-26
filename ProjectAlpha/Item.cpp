#include "Item.h"

Item::Item(ItemsEnum itemId, int amount, bool reusable, int condition):
	itemId(itemId), amount(amount), reusable(reusable), condition(condition)
{
}

void Item::applyItemConsumeEffect(float& health, float& sleep, float& temperature, float& thirst, float& hunger)
{
	readFileObj.open(effectsInfoFile);

	string s;

	do
	{
		readFileObj >> s;
	} while (s != "ID" + ' ' + itemId);

	cout << s << endl;
}

