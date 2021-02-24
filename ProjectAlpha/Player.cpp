#include "Player.h"

Player::Player(Vector2f spawnPos)
{
	pos = spawnPos;
	playerSprite.setPosition(pos);
	playerSprite.setOrigin(50, 110);
	targetPointSprite.setOrigin(50, 70);
	targetPointSprite.setColor({ 255, 255, 255, 0 });
	targetPointSprite.setScale({0.8, 0.8});

	timeIncreaseTimer.restart();

	storage.addItem(Item(ItemsEnum::KNIFE, 1));
	storage.addItem(Item(ItemsEnum::SHIRT, 2));
	storage.addItem(Item(ItemsEnum::BRICK, 3));
	storage.addItem(Item(ItemsEnum::KNIFE, 4));
	storage.addItem(Item(ItemsEnum::SHIRT, 6));
	storage.addItem(Item(ItemsEnum::BRICK, 7));
	/*storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::KNIFE, 8));
	storage.addItem(Item(ItemsEnum::SHIRT, 9));
	storage.addItem(Item(ItemsEnum::SHIRT, 10));
	storage.addItem(Item(ItemsEnum::BRICK, 11));
	storage.addItem(Item(ItemsEnum::BRICK, 12));
	storage.addItem(Item(ItemsEnum::SHIRT, 13));
	storage.addItem(Item(ItemsEnum::SHIRT, 14));
	storage.addItem(Item(ItemsEnum::BRICK, 15));
	storage.addItem(Item(ItemsEnum::KNIFE, 2));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::KNIFE, 69));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::KNIFE, 2));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::KNIFE, 2));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::KNIFE, 2));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
	storage.addItem(Item(ItemsEnum::BRICK, 1, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));*/
	
}

void Player::load(vector<Texture>& textureResourcesVec, UI& ui)
{
	playerSprite.setTexture(textureResourcesVec[ResourcesEnum::PLAYERICON_T]);
	playerSprite.setTextureRect(IntRect(1 * 100, 0, 100, 120));
	targetPointSprite.setTexture(textureResourcesVec[ResourcesEnum::TARGETPOINT_T]);

	ui.getInventoryItemList()->assignStorage(&storage);
}

void Player::update(IEC& iec, RenderWindow& window, Map & map, UI & ui)
{
	float dx, dy;
	if (iec._LMB && !ui.getPlayerInventoryIsOpened()) 
	{
		targetIsInside = false;

		//cout << map.getPointersVec()->at(0).getBackSpriteBoundaries().left << endl;
		for (int i = 0; i < map.getPointersVec()->size(); i++)
		{
			if (map.getPointersVec()->at(i).getBackSpriteBoundaries().contains(iec.getMousePos(window, window.getView())))
			{
				targetIsInside = true;
				goalPos = map.getPointersVec()->at(i).getPos();
				if (relatedPointer != NULL) relatedPointer->setPlayerIsInside(false);
				relatedPointer = &map.getPointersVec()->at(i);

				//cout << map.getPointersVec()->at(i).getStorage()->getItemsVec()->size() << endl;
				//cout << relatedPointer->getStorage()->getItemsVec()->size() << endl; 
				break;
			}
		}
		
		if (!targetIsInside)
		{
			goalPos = iec.getMousePos(window, window.getView());
		}

		moving = true;
		playerSprite.setTextureRect(IntRect(0 * 100, 0, 100, 120));

		//Calculations 
		
		dx = goalPos.x - pos.x;
		dy = goalPos.y - pos.y;
		leftToTravel = sqrt(dx * dx + dy * dy);
		normilizedTravelVec.x = dx / leftToTravel;
		normilizedTravelVec.y = dy / leftToTravel;
		//Debug
		//cout << normilizedTravelVec.x << endl;
		//cout << normilizedTravelVec.y << endl << endl;

		targetPointSprite.setPosition(goalPos);
		targetPointSprite.setColor({ 255, 255, 255, 255 });

		
	}
	
	if (ui.getPlayerInventoryIsOpened())
	{
		playerSprite.setTextureRect(IntRect(1 * 100, 0, 100, 120));
		moving = false;

		targetPointSprite.setColor({ 255, 255, 255, 0 });
	}

	if (moving)
	{
		inside = false;

		dx = goalPos.x - pos.x;
		dy = goalPos.y - pos.y;
		leftToTravel = sqrt(dx * dx + dy * dy);
		pos.x += normilizedTravelVec.x * speed * (float)iec.cycleTime.asMicroseconds();
		pos.y += normilizedTravelVec.y * speed * (float)iec.cycleTime.asMicroseconds();
		//cout << iec.cycleTime.asMilliseconds() << endl;
		//cout << pos.x << endl;
		//cout << pos.y << endl << endl;
		playerSprite.setPosition(pos);

		if (timeIncreaseTimer.getElapsedTime().asSeconds() >= 0.5)
		{
			timeIncreaseTimer.restart();
			ui.getClocks()->addMinutes(5);
		}
	}

	if (leftToTravel <= 1)
	{
		playerSprite.setTextureRect(IntRect(1 * 100, 0, 100, 120));
		moving = false;

		targetPointSprite.setColor({ 255, 255, 255, 0 });

		if (targetIsInside) 
		{
			inside = true;

			if (relatedPointer != NULL)
			{
				if (ui.getLocationItemList()->getAssignedStorage() != relatedPointer->getStorage())
				{
					cout << "Items - " << relatedPointer->getStorage()->getItemsVec()->size() << endl;
					ui.getLocationItemList()->assignStorage(relatedPointer->getStorage());
					//cout << "A";
				}
			}
		}

		
	}

	if (inside)
	{
		playerSprite.setColor({ 255, 255, 255, 0 });
		if (relatedPointer != NULL) relatedPointer->setPlayerIsInside(true);
	}
	else
	{
		playerSprite.setColor({ 255, 255, 255, 255 });
		if (relatedPointer != NULL) relatedPointer->setPlayerIsInside(false);
	}
	
	if (iec.mouseWheelDelta != 0)
	{
		playerSprite.scale({ 1 - iec.mouseWheelDelta / 10.f, 1 -(float)iec.mouseWheelDelta / 10.f });
		targetPointSprite.scale({ 1 - iec.mouseWheelDelta / 10.f, 1 -(float)iec.mouseWheelDelta / 10.f });
	}

	pickedColor = map.getMapImage()->getPixel(pos.x, pos.y);
	if (pickedColor == c_ground) speed = groundWalkingSpeed;
	if (pickedColor == c_forest) speed = forestWalkingSpeed;
	if (pickedColor == c_dirtRoad) speed = dirtRoadWalkingSpeed;
	if (pickedColor == c_building) speed = buildingWalkingSpeed;
	if (pickedColor == c_water) speed = waterWalkingSpeed;

	ui.setPlayerIsInsideLocation(inside);

}

void Player::draw(RenderWindow& window)
{
	if (pos.y > goalPos.y) window.draw(targetPointSprite);
	window.draw(playerSprite);
	if (pos.y < goalPos.y) window.draw(targetPointSprite);
}

Vector2f Player::getPos()
{
	return pos;

}

















