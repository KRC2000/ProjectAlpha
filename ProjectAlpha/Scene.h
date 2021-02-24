#pragma once
#include "PrecompiledHeaders.h"

class Scene
{
protected:
	View sceneView;
	bool active = false;
public:
	Scene();

	void draw();
	virtual void unload() = 0;
	bool isActive();
	void setActive(bool active, RenderWindow& window);
};

