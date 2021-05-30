#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Transform.h"

using namespace sf;
using namespace std;

class GUI_Interactable
{
	vector<GUI_Transform> parentsTransformsVec;
public:
	void applyTransformOnInteraction(vector<GUI_Transform> transformVec)
	{
		parentsTransformsVec.clear();
		parentsTransformsVec = transformVec;
	};

	Vector2f getTransformedMousePos(Vector2f pos)
	{
		for (auto& transform : parentsTransformsVec)
		{
			pos -= transform.render_tHolder->getPosition();
			pos = transform.render_t->mapPixelToCoords((Vector2i)pos);
		}
		return pos;
	};

	vector<GUI_Transform> getTransforms() { return parentsTransformsVec; };
};

