#include "GUIelement.h"


GUIelement::GUIelement()
{
}


void GUIelement::draw(RenderWindow& window)
{
	for (int i = 0; i < sVec.size(); i++)
	{
		window.draw(sVec[i]);
	}
}
