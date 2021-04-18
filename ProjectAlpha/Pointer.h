#pragma once
#include "PrecompiledHeaders.h"
#include "Storage.h"


class Pointer: public Drawable
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
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;

	Storage* getStorage();
	FloatRect getBackSpriteBoundaries();
	Vector2f getPos();
	bool getPlayerIsInside();


	void setPlayerIsInside(bool isInside);
};

