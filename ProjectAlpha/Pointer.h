#pragma once
#include "PrecompiledHeaders.h"
#include "Storage.h"

class Pointer
{
	bool playerIsInside = false;

	PointersEnum pointerType = PointersEnum::HUT;;
	Vector2f pos;
	Sprite sprite, back;
	vector<Texture>* textureResourcesVec_p;
	Storage storage;
public:
	Pointer();
	Pointer(PointersEnum pointerType, Vector2f pos);
	void loadTextures(vector<Texture>* textureResourcesVec);
	void zoom(Vector2f factor);
	void draw(RenderWindow& window);

	Storage* getStorage();
	FloatRect getBackSpriteBoundaries();
	Vector2f getPos();

	void setPlayerIsInside(bool isInside);
};

