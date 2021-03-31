#pragma once
#include "PrecompiledHeaders.h"

class GUI_Element: public Drawable
{
	
public:
	GUI_Element() {};
	virtual ~GUI_Element() {};

	//virtual void load(View& view) = 0;
	virtual bool update(IEC & iec, RenderWindow & window) = 0;

	virtual void  draw(RenderTarget& target, RenderStates states) const override = 0;
};

