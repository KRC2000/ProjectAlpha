#include "Player.h"

Player::Player(Vector2f spawnPos)
{
	pos = spawnPos;
	playerSprite.setPosition(pos);
	playerSprite.setOrigin(50, 110);
	targetPointSprite.setOrigin(50, 70);
	targetPointSprite.setColor({ 255, 255, 255, 0 });
	targetPointSprite.setScale({0.8f, 0.8f});

	timeIncreaseTimer.restart();

	storage.addItem(Item(ItemsEnum::BEER, 1));
	storage.addItem(Item(ItemsEnum::CORN, 2));
	storage.addItem(Item(ItemsEnum::MUSHROOM, 3));
	storage.addItem(Item(ItemsEnum::PILLSJAR, 4));
	storage.addItem(Item(ItemsEnum::TUNA, 6));
	storage.addItem(Item(ItemsEnum::UNKNOWN, 7));
	storage.addItem(Item(ItemsEnum::TUNA, 9));
	storage.addItem(Item(ItemsEnum::CORN, 10));
	/*storage.addItem(Item(ItemsEnum::KNIFE, 8));
	storage.addItem(Item(ItemsEnum::BRICK, 11));

	storage.addItem(Item(ItemsEnum::BRICK, 12));
	storage.addItem(Item(ItemsEnum::SHIRT, 13));
	storage.addItem(Item(ItemsEnum::SHIRT, 14));
	storage.addItem(Item(ItemsEnum::BRICK, 15));
	storage.addItem(Item(ItemsEnum::KNIFE, 2));
	storage.addItem(Item(ItemsEnum::SHIRT, 5));
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
	playerSprite.setTexture(textureResourcesVec[(int)ResourcesEnum::PLAYERICON_T]);
	playerSprite.setTextureRect(IntRect(1 * 100, 0, 100, 120));
	targetPointSprite.setTexture(textureResourcesVec[(int)ResourcesEnum::TARGETPOINT_T]);

	ui.getInventoryItemList()->assignStorage(&storage);
}

void Player::update(IEC& iec, RenderWindow& window, Map & map, UI & ui)
{
	setSpeedToPixel(&map);

	// If LMB clicked
	if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
	{
		// If inventory is closed
		if (!ui.getPlayerInventoryIsOpened())
		{
			int pointerIndex;
			// If clicked on or out of any pointer 
			if (isCursorOnPointer(pointerIndex, map, iec, window))
			{
				// If clicked on other/same pointer as that one that player is in
				if (!map.getPointersVec()->at(pointerIndex).getPlayerIsInside())
				{
					targetIsInside = true;
					if (inside) relatedPointer->setPlayerIsInside(false);
					relatedPointer = &map.getPointersVec()->at(pointerIndex);
					goalPos = map.getPointersVec()->at(pointerIndex).getPos();

					recalculateNormalizedTravelVec();
					ableToTravel = true;
				}
			}
			else
			{
				targetIsInside = false;
				goalPos = iec.getMousePos(window, window.getView());
				if (inside) relatedPointer->setPlayerIsInside(false);

				recalculateNormalizedTravelVec();
				ableToTravel = true;
			}
		}
	}

	// Target sprite manipulations
	if (ableToTravel)
	{
		targetPointSprite.setPosition(goalPos);
		targetPointSprite.setColor({ 255, 255, 255, 255 });
	}
	else targetPointSprite.setColor({ 255, 255, 255, 0 });

	if (ableToTravel) travel(&iec);
	if (traveling) inside = false;

	// Travel stop conditions
	if (iec.getKeyboardKeyState(Keyboard::Space)) stopTravel();
	if (ui.getPlayerInventoryIsOpened()) stopTravel();

	// Time control
	if (traveling)
	{
		if (timeIncreaseTimer.getElapsedTime().asSeconds() >= 0.25)
		{
			ui.getClocks()->addMinutes(1);
			timeIncreaseTimer.restart();
		}
	}

	// Player sprite change when moving or not, inside or not
	if (traveling) playerSprite.setTextureRect(IntRect(0 * 100, 0, 100, 120));
		else playerSprite.setTextureRect(IntRect(1 * 100, 0, 100, 120));
	if (inside) playerSprite.setColor({ 255, 255, 255, 0 });
		else playerSprite.setColor({ 255, 255, 255, 255 });

	// Reaching the target point
	if (traveling && leftToTravel <= 5)
	{
		stopTravel();

		// Snap player to the exact goal position
		setPos(goalPos);

		if (targetIsInside)
		{
			inside = true;
			relatedPointer->setPlayerIsInside(true);
			ui.getLocationItemList()->assignStorage(relatedPointer->getStorage());
		}
	}

	// Mouse wheel scaling
	if (iec.getMouseWheelDelta() != 0)
	{
		playerSprite.scale({ 1 - iec.getMouseWheelDelta() / 10.f, 1 -(float)iec.getMouseWheelDelta() / 10.f });
		targetPointSprite.scale({ 1 - iec.getMouseWheelDelta() / 10.f, 1 -(float)iec.getMouseWheelDelta() / 10.f });
	}
	
	
	if (lastSleepIncreaseTime + sleepIncreaseMinFreq <= ui.getClocks()->getMinutesOverall())
	{
		if (sleep < 100) sleep += 1;
		if (sleep > 100) sleep = 100;
		lastSleepIncreaseTime = ui.getClocks()->getMinutesOverall();
	}
	if (lastThirstIncreaseTime + thirstIncreaseMinFreq <= ui.getClocks()->getMinutesOverall())
	{
		if (thirst < 100) thirst += 1;
		if (thirst > 100) thirst = 100;
		lastThirstIncreaseTime = ui.getClocks()->getMinutesOverall();
	}
	if (lastHungerIncreaseTime + hungerIncreaseMinFreq <= ui.getClocks()->getMinutesOverall())
	{
		if (hunger < 100) hunger += 1;
		if (hunger > 100) hunger = 100;
		lastHungerIncreaseTime = ui.getClocks()->getMinutesOverall();
	}


	ui.setPlayerIsInsideLocation(inside);
	ui.updatePlayerStatusLines(health, sleep, temperature, thirst, hunger);
}

void Player::draw(RenderWindow& window)
{
	if (pos.y >= goalPos.y) window.draw(targetPointSprite);
	window.draw(playerSprite);
	if (pos.y <= goalPos.y) window.draw(targetPointSprite);

}

void Player::setPos(Vector2f newPos)
{
	pos = newPos;
	playerSprite.setPosition(pos);
}

Vector2f Player::getPos()
{
	return pos;

}

void Player::travel(IEC* iec)
{
	traveling = true;
	pos.x += normilizedTravelVec.x * speed * (float)iec->getCycleTime().asMicroseconds();
	pos.y += normilizedTravelVec.y * speed * (float)iec->getCycleTime().asMicroseconds();

	playerSprite.setPosition(pos);

	recalculateLeftToTraveDist();
}

void Player::stopTravel()
{
	traveling = false;
	ableToTravel = false;
}

void Player::recalculateLeftToTraveDist()
{
	float dx, dy;
	dx = goalPos.x - pos.x;
	dy = goalPos.y - pos.y;
	leftToTravel = sqrt(dx * dx + dy * dy);
}

void Player::recalculateNormalizedTravelVec()
{
	float dx, dy;
	dx = goalPos.x - pos.x;
	dy = goalPos.y - pos.y;
	leftToTravel = sqrt(dx * dx + dy * dy);
	normilizedTravelVec.x = dx / leftToTravel;
	normilizedTravelVec.y = dy / leftToTravel;
}

void Player::setSpeedToPixel(Map* map)
{
	pickedColor = map->getMapImage()->getPixel(pos.x, pos.y);
	if (pickedColor == c_ground) speed = groundWalkingSpeed;
	if (pickedColor == c_forest) speed = forestWalkingSpeed;
	if (pickedColor == c_dirtRoad) speed = dirtRoadWalkingSpeed;
	if (pickedColor == c_building) speed = buildingWalkingSpeed;
	if (pickedColor == c_water) speed = waterWalkingSpeed;
}

bool Player::isCursorOnPointer(int& returnedPointerIndex, Map& map, IEC& iec, RenderWindow& window)
{
	for (int i = 0; i < map.getPointersVec()->size(); i++)
	{
		if (map.getPointersVec()->at(i).getBackSpriteBoundaries().contains(iec.getMousePos(window, window.getView())))
		{
			returnedPointerIndex = i;
			return true;
		}
	}
	return false;
}

















