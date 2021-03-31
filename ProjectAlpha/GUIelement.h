#pragma once
#include "PrecompiledHeaders.h"

class GUIelement: public Drawable
{
	
public:
	GUIelement() {};
	virtual ~GUIelement() {};

	//virtual void load(View& view) = 0;
	virtual bool update(IEC & iec, RenderWindow & window) = 0;

	virtual void  draw(RenderTarget& target, RenderStates states) const override = 0;
};

