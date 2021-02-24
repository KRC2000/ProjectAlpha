#pragma once
#include "PrecompiledHeaders.h"
#include "Pointer.h"

class Map
{
	Sprite s;
	Image i;
	Texture t;

	int pointersAmount;

	//Here is all maps cfg file names
	vector<string> mapCfgPathsVec
	{
		"res/map0x0.txt"
	};

	ifstream readCfgObj;

	vector<Pointer> pointersVec;
	
public:
	Map();
	void loadTextures(vector<Texture>* textureResourcesVec);
	void update(IEC & iec, RenderWindow& window);
	void draw(RenderWindow& window);

	vector<Pointer> * getPointersVec();
	Image * getMapImage();
private:
	void loadPointers(string cfgFilePath);
};

