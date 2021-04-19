#pragma once
#include "PrecompiledHeaders.h"
#include "Map.h"
#include "Pointer.h"
#include "UI.h"
#include "Storage.h"
#include "Item.h"

class Player: public Drawable
{
	Vector2f pos, goalPos;
	Sprite playerSprite, targetPointSprite;

	bool inside = false, traveling = false, targetIsInside = false;
	bool ableToTravel = false;
	Vector2f normilizedTravelVec;

	int lastSleepIncreaseTime{0};
	int lastThirstIncreaseTime{0};
	int lastHungerIncreaseTime{0};
	int sleepIncreaseMinFreq = 40;
	int thirstIncreaseMinFreq = 40;
	int hungerIncreaseMinFreq = 300;

	float survivalParameters[(int)SurvivalParametersEnum::AMOUNT]{ 50,50,50,50,50 };
	int consumablesEffectsData[(int)ItemsEnum::CONSUMABLE_ITEMS_AMOUNT][(int)SurvivalParametersEnum::AMOUNT];

	const float groundWalkingSpeed = 0.8f / 10000;
	const float dirtRoadWalkingSpeed = 1.f / 10000;
	const float forestWalkingSpeed = 0.6f / 10000;
	const float buildingWalkingSpeed = 0.5f / 10000;
	const float waterWalkingSpeed = 0.2f / 10000;

	float leftToTravel = 0, speed = groundWalkingSpeed;
	
	Clock timeIncreaseTimer;
	Pointer * relatedPointer = NULL;
	Color pickedColor;

	Storage storage;
public:
	Player(Vector2f spawnPos);
	void load(vector<Texture>& textureResourcesVec, UI& ui);
	void update(IEC & iec, RenderWindow & window, Map & map, UI & ui);
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	void loadConsumableItemsData();

	void applyEffectOnSurvivalParametr(SurvivalParametersEnum parametr, float valueToAdd);
	void consume(Item item);

	void setPos(Vector2f newPos);

	Pointer* getRelatedPointerPtr() { return relatedPointer; };
	float getStateIndicatorNum(SurvivalParametersEnum indicationType) { return survivalParameters[(int)indicationType]; };
	bool getIsInside() { return inside; };
	Vector2f getPos() {return pos; };
	Storage* getStoragePtr() { return &storage; };

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

