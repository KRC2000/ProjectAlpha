#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Transform.h"

using namespace sf;
using namespace std;

/*
Parental class for GUI_Element's that require mouse position for proper functionality
To get mouse position inside such elements class use getTransformedMousePos
*/
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
			bool contains = true;
			Vector2f transitionalPos = pos;
			for (int i = 0; i < parentsTransformsVec.size(); i++)
			{
				if (i == 0) transitionalPos = pos;
				else
				{
					transitionalPos -= parentsTransformsVec[i-1].render_tHolder->getPosition();
					transitionalPos += {0, (float)parentsTransformsVec[i-1].render_tHolder->getTextureRect().top};
				}

				if (!parentsTransformsVec[i].render_tHolder->getGlobalBounds().contains(transitionalPos)) contains = false;

			}
			return contains;
		}
		else return true;
		//return true;
	};

	Vector2f getTransformedMousePos(Vector2f pos)
	{
		for (auto& transform : parentsTransformsVec)
		{
			pos -= transform.render_tHolder->getPosition();
			pos += {0 , (float)transform.render_tHolder->getTextureRect().top };
		}
		return pos;
	};

	void setApplyTransform(bool applyTransform) { this->applyTransform = applyTransform; };

	vector<GUI_Transform> getTransforms() { return parentsTransformsVec; };
};

