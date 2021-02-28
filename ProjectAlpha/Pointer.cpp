#include "Pointer.h"

Pointer::Pointer()
{
	pos = { 0, 0 };
	

	/*storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));*/
	//cout << "I have - " << storage.getItemsVec()->size() << endl;
}

Pointer::Pointer(PointersEnum pointerType, Vector2f pos) : pointerType(pointerType), pos(pos)
{
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	/*storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));
	storage.addItem(Item(ItemsEnum::BRICK, 666, true, 75));*/

	//Pointer();
	sprite.setTextureRect(IntRect(pointerType * 100, 0, 100, 100));
	sprite.setOrigin({ 50, 120 });
	sprite.setPosition(pos);
	sprite.setScale({ 0.8, 0.8 });
	back.setTextureRect(IntRect(0 * 130, 100, 130, 130));
	back.setOrigin({65, 128});
	back.setPosition(pos);
	back.setScale({ 0.8, 0.8 });
}

void Pointer::loadTextures(vector<Texture>* textureResourcesVec)
{
	sprite.setTexture(textureResourcesVec->at(ResourcesEnum::POINTERS_T));
	back.setTexture(textureResourcesVec->at(ResourcesEnum::POINTERS_T));
}

void Pointer::zoom(Vector2f factor)
{
	sprite.scale(factor);
	back.scale(factor);
}

void Pointer::draw(RenderWindow& window)
{
	window.draw(back);
	window.draw(sprite);
}

Storage* Pointer::getStorage()
{
	return &storage;
}

FloatRect Pointer::getBackSpriteBoundaries()
{
	return back.getGlobalBounds();
}

Vector2f Pointer::getPos()
{
	return pos;
}

bool Pointer::getPlayerIsInside()
{
	return playerIsInside;
}

void Pointer::setPlayerIsInside(bool isInside)
{
	playerIsInside = isInside;

	if (playerIsInside) back.setTextureRect(IntRect(1 * 130, 100, 130, 130));
	else back.setTextureRect(IntRect(0 * 130, 100, 130, 130));
}
