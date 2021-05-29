#pragma once
#include <SFML/Graphics.hpp>
#include "GUI_Transform.h"

using namespace sf;
using namespace std;

class GUI_RenderTextureContainer
{
	GUI_Transform transform;
	vector<GUI_Transform> parentsTransformsVec;
public:
	GUI_RenderTextureContainer(RenderTexture& render_t, Sprite& render_tHolder):
		transform(render_t, render_tHolder)
	{
		parentsTransformsVec.push_back(transform);
	};

	void applyParentalTransforms(vector<GUI_Transform> parentsTransformsVec)
	{
		parentsTransformsVec.clear();
		this->parentsTransformsVec = parentsTransformsVec;
		this->parentsTransformsVec.push_back(transform);
	}

	vector<GUI_Transform> getParentalTransforms()
	{
		return parentsTransformsVec;
	}
};

