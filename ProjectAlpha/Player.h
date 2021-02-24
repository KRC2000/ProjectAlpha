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

	bool inside = false, moving = false, targetIsInside;
	Vector2f normilizedTravelVec;

	float groundWalkingSpeed = 0.8f / 10000;
	float dirtRoadWalkingSpeed = 1.f / 10000;
	float forestWalkingSpeed = 0.6f / 10000;
	float buildingWalkingSpeed = 0.5f / 10000;
	float waterWalkingSpeed = 0.2f / 10000;

	//leftToTravel - updated dinamically
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

	Vector2f getPos();
};

