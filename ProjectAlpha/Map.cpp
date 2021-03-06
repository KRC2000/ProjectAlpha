#include "Map.h"

Map::Map()
{
	i.loadFromFile("res/map0x0.png");
	t.loadFromImage(i);
	s.setTexture(t);

	
	loadPointers(mapCfgPathsVec[0]);
	
}

void Map::loadTextures(vector<Texture>* textureResourcesVec)
{
	for (int i = 0; i < pointersVec.size(); i++)
	{
		pointersVec[i].loadTextures(textureResourcesVec);
	}
}

vector<Pointer> * Map::getPointersVec()
{
	return & pointersVec;
}

Image* Map::getMapImage()
{
	return &i;
}

void Map::update(IEC& iec, RenderWindow& window)
{
	if (iec.getMouseWheelDelta() != 0)
	{
		for (int i = 0; i < pointersVec.size(); i++)
		{
			pointersVec[i].zoom({ 1 - (float)iec.getMouseWheelDelta() / 10, 1 - (float)iec.getMouseWheelDelta() / 10 });
		}
	}
}

void Map::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(s);
	for (auto& pointer : pointersVec)
	{
		target.draw(pointer);
	}
}

void Map::loadPointers(string cfgFilePath)
{
	readCfgObj.open(cfgFilePath);

	string s;

	do
	{
		readCfgObj >> s;
	} while (s != "PointersData");

	int pointerType_i;
	Vector2i pointerPos;

	readCfgObj >> s >> pointersAmount;
	for (int i = 0; i < pointersAmount; i++)
	{
		readCfgObj >> pointerPos.x >> pointerPos.y >> pointerType_i;
		Pointer p(static_cast<PointersEnum> (pointerType_i), { (float)pointerPos.x, (float)pointerPos.y });
		pointersVec.push_back(p);
	}

	readCfgObj.close();
}
