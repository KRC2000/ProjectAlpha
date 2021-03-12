#include "GUI_ItemsList.h"

GUI_ItemsList::GUI_ItemsList()
{
	
}

void GUI_ItemsList::load(vector<Texture>* texturesResourcesVec, Vector2f pos, Font* font)
{
	resourcesVec = texturesResourcesVec;
	guiFont1 = font;

	s_border.setTexture(resourcesVec->at(ResourcesEnum::GUI_T));

	// load() underlying objects: buttons, slider, items-list items(if they are)
	upListButton.load("res/upListButton.png", "goUpList");
	downListButton.load("res/downListButton.png", "goDownList");
	slider.load({ (float)resourcesVec->at(ResourcesEnum::GUI_T).getSize().x + 3, upListButton.getGlobalBounds().height},
		(float)resourcesVec->at(ResourcesEnum::GUI_T).getSize().y -
		(upListButton.getGlobalBounds().height + downListButton.getGlobalBounds().height ));

	for (unsigned int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, font);
	}

	setPosition(pos);
	
	baseUpperEdgePoint = { s_border.getPosition().x + 6, s_border.getPosition().y + fadeGap };
	baseDownEdgePoint = { s_border.getPosition().x + 6, s_border.getPosition().y + s_border.getGlobalBounds().height - fadeGap };
}


void GUI_ItemsList::assignStorage(Storage* storage)
{
	assignedStorage = storage;

	// Clear items-list items vector from items-list items that represent items from past assigned storage
	itemsVec.clear();

	// For each item in new storage create related items-list item 
	for (unsigned int i = 0; i < assignedStorage->getItemsVec()->size(); i++)
	{
		itemsVec.push_back(GUI_ItemsListItem(assignedStorage->getItemsVec()->at(i).getId(), assignedStorage->getItemsVec()->at(i).getAmount(),
			assignedStorage->getItemsVec()->at(i).getIsReusable(), assignedStorage->getItemsVec()->at(i).getCondition()));

	}

	// initializing and load() of all just created items-list items
	for (unsigned int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, guiFont1);
		itemsVec[i].setPos({ baseUpperEdgePoint.x, 
			baseUpperEdgePoint.y + i * (resourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y + distanceBetweenItems)});
	}

	recalculateItemListLenght();
}

void GUI_ItemsList::moveItems(Vector2f factor)
{
	for (unsigned int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].move(factor);
	}
}

void GUI_ItemsList::setItemsPos(Vector2f newPos)
{
	for (unsigned int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].setPos({newPos.x, newPos.y + i * (itemsVec[i].getSpriteBox()->getGlobalBounds().height + distanceBetweenItems) });
	}
}

void GUI_ItemsList::liftItemsTale(unsigned int taleStartIndex)
{
	for (unsigned int i = taleStartIndex; i < itemsVec.size(); i++)
	{
		itemsVec[i].move({ 0, -(itemSizeY + distanceBetweenItems) });
	}
	recalculateItemListLenght();
}


void GUI_ItemsList::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		// Moving content according to slider, and slider according to content
		// Reading and updating buttons
		if (itemsVec.size() > 1)
		{
			if (itemListLenght > baseDownEdgePoint.y - baseUpperEdgePoint.y)
			{
				if (slider.update(iec, window, view))
				{
					setPositionPercent(slider.getPositionPercent());
				}
				slider.setPositionPercent(getPositionPercent());

				if (downListButton.update(iec, window, view)) scrollDown();
				if (upListButton.update(iec, window, view)) scrollUp();
			}
		}
		
		// Updating every items-list item
		for (unsigned int i = 0; i < itemsVec.size(); i++)
		{
			itemsVec[i].update(iec);
		}
		
		
		// System of moving content on mouse scroll
		if (s_border.getGlobalBounds().contains(iec.getMousePos(window, view)))
		{
			if (itemsVec.size() > 1)
			{
				if (iec.mouseWheelDelta != 0)
				{
					if (iec.mouseWheelDelta == 1)
					{
						if (itemsVec[0].getSpriteBox()->getPosition().y < baseUpperEdgePoint.y)
						{
							moveItems({ 0, 15 });
						}
					}
					if (iec.mouseWheelDelta == -1)
					{
						if (itemsVec[itemsVec.size()-1].getSpriteBox()->getPosition().y + itemsVec[itemsVec.size() - 1].getSpriteBox()->getGlobalBounds().height > baseDownEdgePoint.y)
						{
							moveItems({ 0, -15 });
						}
					}
				}
			}
			iec.mouseWheelDelta = 0;
		}

		// Can't scroll out of bounds, stables
		if (itemsVec.size() > 1)
		{
			if (itemListLenght > baseDownEdgePoint.y - baseUpperEdgePoint.y)
			{
				if (itemsVec[0].getSpriteBox()->getPosition().y > baseUpperEdgePoint.y)
				{
					setItemsPos({ baseUpperEdgePoint.x, baseUpperEdgePoint.y });
					cout << "Happened";
				}
				if (itemsVec[itemsVec.size() - 1].getSpriteBox()->getPosition().y + itemsVec[itemsVec.size() - 1].getSpriteBox()->getGlobalBounds().height < baseDownEdgePoint.y)
				{
					setItemsPos({ baseUpperEdgePoint.x, baseUpperEdgePoint.y - (itemListLenght - (baseDownEdgePoint.y - baseUpperEdgePoint.y)) });
				}
			}
		}

		// If items-list items are intersect with background sprite - fade in
		// otherwise - fade out
		for (unsigned int i = 0; i < itemsVec.size(); i++)
		{
			if (!isBorderIntersectsWithItem(i))
			{
				itemsVec[i].fadeOut();
			}
			else
			{
				itemsVec[i].fadeIn();
			}
		}
	}
}

void GUI_ItemsList::draw(RenderWindow& window)
{
	if (active)
	{
		window.draw(s_border);

		for (unsigned int i = 0; i < itemsVec.size(); i++)
		{
			itemsVec[i].draw(window);
		}

		// Drawing slider and buttons only if they are not fitting in background sprite
		if (itemsVec.size() > 1)
		{
			if (!isBorderIntersectsWithItem(0) || !isBorderIntersectsWithItem(itemsVec.size() - 1))
			{
				upListButton.draw(window);
				downListButton.draw(window);
				slider.draw(window);
			}
		}
	}
}


void GUI_ItemsList::scrollUp()
{
	if (!isBorderIntersectsWithItem(0))
	{
		moveItems({ 0, +3*10 });

		if (isBorderIntersectsWithItem(0))
		{
			while (isBorderIntersectsWithItem(0))
			{
				moveItems({ 0, -1 });
			}
			moveItems({ 0, 1 });
		}
	}
}

void GUI_ItemsList::scrollDown()
{
	if (!isBorderIntersectsWithItem(itemsVec.size() - 1))
	{
		moveItems({ 0, -3*10 });

		if (isBorderIntersectsWithItem(itemsVec.size() - 1))
		{
			while (isBorderIntersectsWithItem(itemsVec.size() - 1))
			{
				moveItems({ 0, +1 });
			}
			moveItems({ 0, -1 });
		}
	}

}

void GUI_ItemsList::recalculateItemListLenght()
{
	itemListLenght = itemsVec.size() * (float)resourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y +
		(itemsVec.size() - 1) * distanceBetweenItems ;
	cout << itemsVec.size() << endl;
	//if (itemListLenght < 0) itemListLenght = 0;
}

Item GUI_ItemsList::deleteItem(unsigned int itemVecIndex)
{
	itemsVec.erase(itemsVec.begin() + itemVecIndex);
	Item returnItem = *assignedStorage->getItem(itemVecIndex);
	assignedStorage->deleteItem(itemVecIndex);

	liftItemsTale(itemVecIndex);
	return returnItem;
}



void GUI_ItemsList::addItem(Item newItem)
{
	if (newItem.getId() >= ItemsEnum::UNKNOWN && newItem.getId() < ItemsEnum::ITEMS_AMOUNT)
	{
		GUI_ItemsListItem item(newItem.getId(), newItem.getAmount(), newItem.getIsReusable(), newItem.getCondition());
		item.load(*resourcesVec, guiFont1);

		if (itemsVec.size() >= 1)
		{
			item.setPos({ itemsVec[itemsVec.size() - 1].getSpriteBox()->getPosition().x,
				itemsVec[itemsVec.size() - 1].getSpriteBox()->getPosition().y + item.getSpriteBox()->getGlobalBounds().height
				+ distanceBetweenItems });
		}
		else
		{
			item.setPos({ s_border.getPosition().x + 6, s_border.getPosition().y + 21 });
		}

		itemsVec.push_back(item);

		recalculateItemListLenght();
	}


}



void GUI_ItemsList::setPosition(Vector2f pos)
{
	s_border.setPosition(pos);
	upListButton.setPosition({ s_border.getPosition().x + s_border.getGlobalBounds().width + 3, s_border.getPosition().y});
	downListButton.setPosition({ 
		s_border.getPosition().x + s_border.getGlobalBounds().width + 3, 
		s_border.getPosition().y + s_border.getGlobalBounds().height - downListButton.getGlobalBounds().height });
	slider.setPosition({ pos.x + s_border.getGlobalBounds().width + 3,
		pos.y + upListButton.getGlobalBounds().height});
}

void GUI_ItemsList::setActive(bool active)
{
	this->active = active;
}

void GUI_ItemsList::setPositionPercent(float percent)
{
	setItemsPos({ baseUpperEdgePoint.x, baseUpperEdgePoint.y - percent * onePercentLenght });

	/*if (getPositionPercent() < percent)
	{
		while (getPositionPercent() != percent)
		{
			moveItems({ 0, -1 });
		}
	}
	else if (getPositionPercent() > percent)
	{
		while (getPositionPercent() != percent)
		{
			moveItems({ 0, 1 });
		}
	}*/
	
}


Sprite* GUI_ItemsList::getBorderSprite()
{
	return &s_border;
}

Storage* GUI_ItemsList::getAssignedStorage()
{
	return assignedStorage;
}

bool GUI_ItemsList::isCursorPointingAtItem(unsigned int& itemVecIndex, Vector2f mousePos)
{
	for (unsigned int i = 0; i < itemsVec.size(); i++)
	{
		if (itemsVec[i].getSpriteBox()->getGlobalBounds().contains(mousePos))
		{
			itemVecIndex = i;
			return true;
		}
	}
	return false;
}

float GUI_ItemsList::getPositionPercent()
{
	float passed = baseUpperEdgePoint.y - itemsVec[0].getSpriteBox()->getPosition().y;
	onePercentLenght = (itemListLenght - (baseDownEdgePoint.y - baseUpperEdgePoint.y)) / 100;
	float percentsPassed = passed / onePercentLenght;
	return percentsPassed;
}

bool GUI_ItemsList::isBorderIntersectsWithItem(int itemVectorIndex)
{
	if (itemsVec[itemVectorIndex].getSpriteBox()->getPosition().y >= baseUpperEdgePoint.y
		&& itemsVec[itemVectorIndex].getSpriteBox()->getPosition().y <= baseDownEdgePoint.y
		&& itemsVec[itemVectorIndex].getSpriteBox()->getPosition().y + itemsVec[itemVectorIndex].getSpriteBox()->getGlobalBounds().height >= baseUpperEdgePoint.y
		&& itemsVec[itemVectorIndex].getSpriteBox()->getPosition().y + itemsVec[itemVectorIndex].getSpriteBox()->getGlobalBounds().height <= baseDownEdgePoint.y)
		return true;
	else return false;
}




