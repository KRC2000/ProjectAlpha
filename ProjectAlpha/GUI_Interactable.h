#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Transform.h"

using namespace sf;
using namespace std;

class GUI_Interactable
{
	vector<GUI_Transform> parentsTransformsVec;
protected: 
	bool applyTransform = false;
public:	
	void applyTransformOnInteraction(vector<GUI_Transform> transformVec)
	{
		parentsTransformsVec.clear();
		parentsTransformsVec = transformVec;
	};

	bool getIsCursorInsideOwnerRenderTexture(Vector2f pos)
	{
		if (parentsTransformsVec.size() > 0)
		{
			for (int i = 0; i < parentsTransformsVec.size() - 1; i++)
			{
				pos -= parentsTransformsVec[i].render_tHolder->getPosition();
				pos = parentsTransformsVec[i].render_t->mapPixelToCoords((Vector2i)pos);
			}
			if (parentsTransformsVec.back().render_tHolder->getGlobalBounds().contains(pos)) return true;
			else return false;
		}
		else
		{
			return true;
		}
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

	void setApplyTransform(bool applyTransform) { this->applyTransform = applyTransform; };

	vector<GUI_Transform> getTransforms() { return parentsTransformsVec; };
};

