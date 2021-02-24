#pragma once
#include "PrecompiledHeaders.h"

class GUIelement
{
protected:
	vector<Sprite> sVec;
public:
	GUIelement();
	virtual void load(View& view) = 0;
	virtual bool update(IEC & iec, RenderWindow & window) = 0;
	void draw(RenderWindow & window);
};

