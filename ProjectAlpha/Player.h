#pragma once
#include "PrecompiledHeaders.h"
#include "Map.h"
#include "Pointer.h"
#include "UI.h"
#include "Storage.h"
#include "Item.h"

class Player
{
	Vector2f pos, goalPos;
	Sprite playerSprite, targetPointSprite;

	bool inside = false, traveling = false, targetIsInside = false;
	bool ableToTravel = false;
	Vector2f normilizedTravelVec;

	float groundWalkingSpeed = 0.8f / 10000;
	float dirtRoadWalkingSpeed = 1.f / 10000;
	float forestWalkingSpeed = 0.6f / 10000;
	float buildingWalkingSpeed = 0.5f / 10000;
	float waterWalkingSpeed = 0.2f / 10000;

	float leftToTravel = 0, speed = groundWalkingSpeed;
	
	Clock timeIncreaseTimer;
	Pointer * relatedPointer = NULL;
	Color pickedColor;

	Storage storage;
public:
	Player(Vector2f spawnPos);
	void load(vector<Texture>& textureResourcesVec, UI& ui);
	void update(IEC & iec, RenderWindow & window, Map & map, UI & ui);
	void draw(RenderWindow& window);

	void setPos(Vector2f newPos);

	Vector2f getPos();

private:
	void travel(IEC* iec);
	void stopTravel();
	void recalculateLeftToTraveDist();
	void recalculateNormalizedTravelVec();

	// Sets movement speed according to pixel color that player is on
	void setSpeedToPixel(Map* map);

	// Passed variable will be = to index of clicked pointer in the pointers vector
	bool isCursorOnPointer(int& returnedPointerIndex, Map& map, IEC& iec, RenderWindow& window);

};

