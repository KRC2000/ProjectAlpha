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
	upListButton.load("res/upListButton.png");
	downListButton.load("res/downListButton.png");
	slider.load({ (float)resourcesVec->at(ResourcesEnum::GUI_T).getSize().x + 3, upListButton.getGlobalBounds().height},
		(float)resourcesVec->at(ResourcesEnum::GUI_T).getSize().y -
		(upListButton.getGlobalBounds().height + downListButton.getGlobalBounds().height ));

	for (int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, font);
	}
	
	setPosition(pos);
}


void GUI_ItemsList::assignStorage(Storage* storage)
{
	assignedStorage = storage;

	// Clear items-list items vector from items-list items that represent items from past assigned storage
	itemsVec.clear();

	// For each item in new storage create related items-list item 
	for (int i = 0; i < assignedStorage->getItemsVec()->size(); i++)
	{
		itemsVec.push_back(GUI_ItemsListItem(assignedStorage->getItemsVec()->at(i).getId(), assignedStorage->getItemsVec()->at(i).getAmount(),
			assignedStorage->getItemsVec()->at(i).getIsReusable(), assignedStorage->getItemsVec()->at(i).getCondition()));

	}

	// initializing and load() of all just created items-list items
	for (int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, guiFont1);
		itemsVec[i].setPos({ s_border.getPosition().x + 6, 
			s_border.getPosition().y + i * (resourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y + distanceBetweenItems) + 21});
	}

	
	recalculateItemListLenght();
	
}

void GUI_ItemsList::moveItems(Vector2f factor)
{
	for (int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].move(factor);
	}
}


void GUI_ItemsList::update(IEC& iec, RenderWindow& window, View& view)
{
	if (active)
	{
		// Moving content according to slider, and slider according to content
		// Reading and updating buttons
		if (itemsVec.size() > 1)
		{
			if (!isBorderIntersectsWithItem(0) || !isBorderIntersectsWithItem(itemsVec.size() - 1))
			{
				if (slider.update(iec, window, view))
				{
					setPositionPercent(slider.getPositionPercent());
				}
				slider.setPositionPercent(getPositionPercent());

				if (upListButton.update(iec, window, view)) scrollUp();
				if (downListButton.update(iec, window, view)) scrollDown();
			}
		}
		
		// Updating every items-list item
		for (int i = 0; i < itemsVec.size(); i++)
		{
			itemsVec[i].update(iec);
		}
		
		

		// Pretty retarded system of moving content on mouse scroll
		if (s_border.getGlobalBounds().contains(iec.getMousePos(window, view)))
		{
			if (itemsVec.size() > 1)
			{
				if (iec.mouseWheelDelta != 0 &&
					!(isBorderIntersectsWithItem(0) &&
						isBorderIntersectsWithItem(itemsVec.size() - 1)))
				{
					moveItems({ 0, iec.mouseWheelDelta * 15.f });

					
					// This piece of crap kind of stabilizing items if they were
					// scrolled down/up not enough, and few pixels out so that
					// these items is not fading in, but they are on the edge,
					// so it's too easy to visually lose them. This code pops
					// them back little bit, but enough for them to fade in
					if (isBorderIntersectsWithItem(0))
					{
						while (isBorderIntersectsWithItem(0))
						{
							moveItems({ 0, -1 });
						}

						moveItems({ 0, 1 });
					}
					else if (isBorderIntersectsWithItem(itemsVec.size() - 1))
					{
						while (isBorderIntersectsWithItem(itemsVec.size() - 1))
						{
							moveItems({ 0, +1 });

						}
						moveItems({ 0, -1 });
					}

					
					
				}


				if (isBorderIntersectsWithItem(0) && isBorderIntersectsWithItem(itemsVec.size() - 1))
				{
					while (isBorderIntersectsWithItem(0))
					{
						moveItems({ 0, -1 });
					}

					moveItems({ 0, 1 });
				}

			}
			
			iec.mouseWheelDelta = 0;

			

			
		}

		// If items-list items are intersect with background sprite - fade in
		// otherwise - fade out
		for (int i = 0; i < itemsVec.size(); i++)
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

		for (int i = 0; i < itemsVec.size(); i++)
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
	if (itemListLenght < 0) itemListLenght = 0;
}

bool GUI_ItemsList::deleteItem(Item* item, float itemSizeY, Vector2f mousePos)
{

	if (itemsVec.size() >= 1)
	{
		//cout << itemsVec[0].getSpriteBox()->getGlobalBounds().contains(mousePos) << endl;
		for (int i = 0; i < itemsVec.size(); i++)
		{
			//cout << itemsVec[i].getSpriteBox()->getGlobalBounds().contains(mousePos) << endl;
			if (itemsVec[i].getSpriteBox()->getGlobalBounds().contains(mousePos))
			{
				itemsVec.erase(itemsVec.begin() + i);
				*item = *assignedStorage->getItem(i);
				assignedStorage->deleteItem(i);

				for (int k = i; k < itemsVec.size(); k++)
				{
					itemsVec[k].move({ 0, -(itemSizeY + distanceBetweenItems) });
				}
				recalculateItemListLenght();
				return true;
			}
		}
	}
	return false;
}

void GUI_ItemsList::addItem(Item newItem)
{
	if (newItem.getId() >= ItemsEnum::UNKNOWN && newItem.getId() < ItemsEnum::ITEMS_AMOUNT)
	{
		//assignedStorage->addItem(newItem);

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
			/*itemsVec[itemsVec.size() - 1].getSpriteBox()->getPosition().y + item.getSpriteBox()->getGlobalBounds().height
			+ distanceBetweenItems });*/
		}

		itemsVec.push_back(item);

		cout << "VECTOR SIZE -" << itemsVec.size() << endl;
		cout << itemListLenght << endl;
		recalculateItemListLenght();
		cout << itemListLenght << endl;

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
	if ((int)getPositionPercent() < (int)percent)
	{
		while ((int)getPositionPercent() != (int)percent)
		{
			moveItems({ 0, -1 });
		}
	}
	else if ((int)getPositionPercent() > (int)percent)
	{
		while ((int)getPositionPercent() != (int)percent)
		{
			moveItems({ 0, 1 });
		}
	}
	
	if (percent < 1)
	{
		while (!isBorderIntersectsWithItem(0))
		{
			moveItems({ 0, 1 });
		}
	}
	if (percent > 99)
	{
		while (isBorderIntersectsWithItem(itemsVec.size() - 1))
		{
			moveItems({ 0, 1 });
		}
		if(!isBorderIntersectsWithItem(itemsVec.size() - 1)) moveItems({ 0, -1 });
	}


}


Sprite* GUI_ItemsList::getBorderSprite()
{
	return &s_border;
}

Storage* GUI_ItemsList::getAssignedStorage()
{
	return assignedStorage;
}

float GUI_ItemsList::getPositionPercent()
{
	float passed =(s_border.getPosition().y + 21) - itemsVec[0].getSpriteBox()->getPosition().y;
	//cout << passed << endl;
	float inOnePercent = (itemListLenght - (s_border.getGlobalBounds().height - 21 * 2)) / 100.f;
	float percentsPassed = passed / inOnePercent;
	return percentsPassed;
}

bool GUI_ItemsList::isBorderIntersectsWithItem(int itemVectorIndex)
{
	if (itemsVec[itemVectorIndex].getSpriteBox()->getGlobalBounds().intersects(FloatRect(
		s_border.getPosition().x,
		s_border.getPosition().y + fadeGap,
		s_border.getGlobalBounds().width,
		s_border.getGlobalBounds().height - fadeGap * 2)))
		return true;
	else return false;
}




