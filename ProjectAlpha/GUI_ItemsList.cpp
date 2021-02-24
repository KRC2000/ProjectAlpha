#include "GUI_ItemsList.h"

GUI_ItemsList::GUI_ItemsList()
{
	
}

void GUI_ItemsList::load(vector<Texture>* texturesResourcesVec, Vector2f pos, Font* font)
{
	resourcesVec = texturesResourcesVec;
	guiFont1 = font;

	s_border.setTexture(resourcesVec->at(ResourcesEnum::GUI_T));

	upListButton.load("res/upListButton.png");
	downListButton.load("res/downListButton.png");
	setPosition(pos);
	
	slider.load({ s_border.getPosition().x + s_border.getGlobalBounds().width + 3, 
		s_border.getPosition().y + upListButton.getGlobalBounds().height},
		s_border.getGlobalBounds().height - 
		(upListButton.getGlobalBounds().height + downListButton.getGlobalBounds().height ));


	//s_border window.getSize().x
	for (int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, font);
	}
	
}


void GUI_ItemsList::assignStorage(Storage* storage)
{
	assignedStorage = storage;

	//cout << "Items - " << assignedStorage->getItemsVec()->size() << endl;



	itemsVec.clear();

	for (int i = 0; i < assignedStorage->getItemsVec()->size(); i++)
	{
		itemsVec.push_back(GUI_ItemsListItem(assignedStorage->getItemsVec()->at(i).getId(), assignedStorage->getItemsVec()->at(i).getAmount(),
			assignedStorage->getItemsVec()->at(i).getIsReusable(), assignedStorage->getItemsVec()->at(i).getCondition()));

	}

	//if (itemsVec)

	for (int i = 0; i < itemsVec.size(); i++)
	{
		itemsVec[i].load(*resourcesVec, guiFont1);
		itemsVec[i].setPos({ s_border.getPosition().x + 6, 
			s_border.getPosition().y + i * (resourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y + distanceBetweenItems) + 21});
	}
	cout << resourcesVec->at(ResourcesEnum::ITEMSLISTITEM_T).getSize().y << endl;
	recalculateItemListLenght();
	cout << "Items list lenght: " << itemListLenght << endl;
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
		


		//cout << slider.getPositionPercent() << endl;


		//cout << getPositionPercent() << endl;
		//cout << itemsVec[0].getSpriteBox()->getGlobalBounds().height << endl;

		for (int i = 0; i < itemsVec.size(); i++)
		{
			itemsVec[i].update(iec);
		}
		
		


		if (s_border.getGlobalBounds().contains(iec.getMousePos(window, view)))
		{
			if (itemsVec.size() > 1)
			{
				if (iec.mouseWheelDelta != 0 &&
					!(isBorderIntersectsWithItem(0) &&
						isBorderIntersectsWithItem(itemsVec.size() - 1)))
				{
					moveItems({ 0, iec.mouseWheelDelta * 15.f });

				
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

Item GUI_ItemsList::deleteItem(float itemSizeY, Vector2f mousePos)
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
				Item tempItem(*assignedStorage->getItem(i));
				assignedStorage->deleteItem(i);

				for (int k = i; k < itemsVec.size(); k++)
				{
					itemsVec[k].move({ 0, -(itemSizeY + distanceBetweenItems) });
				}
				recalculateItemListLenght();
				return tempItem;
			}
		}
	}

	
}

void GUI_ItemsList::addItem(Item newItem)
{
	if (newItem.getId() >= ItemsEnum::UNKNOWN && newItem.getId() < ItemsEnum::ITEMS_AMOUNT)
	{
		assignedStorage->addItem(newItem);

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

	/*if (isBorderIntersectsWithItem(0))
	{
		while (isBorderIntersectsWithItem(0))
		{
			moveItems({ 0, -1 });
		}

		moveItems({ 0, 1 });
	}
	if (isBorderIntersectsWithItem(itemsVec.size() - 1))
	{

		while (isBorderIntersectsWithItem(itemsVec.size() - 1))
		{
			moveItems({ 0, +1 });

		}
		moveItems({ 0, -1 });
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




