#pragma once
#include "PrecompiledHeaders.h"

/*
Scene class. Contains all content of the scene, like player, map, UI, etc.
If active = true scene is updating and rendering*/
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

