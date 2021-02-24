#include "Scene.h"

Scene::Scene()
{
	sceneView.setSize({ 1920, 1080 });
}



void Scene::draw()
{
}

bool Scene::isActive()
{
	return active;
}

void Scene::setActive(bool active, RenderWindow & window)
{
	this->active = active;
	window.setView(sceneView);
}
