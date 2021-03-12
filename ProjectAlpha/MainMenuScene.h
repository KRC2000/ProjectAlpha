#pragma once
#include "PrecompiledHeaders.h"
#include "Scene.h"
#include "Button.h"

/*
Inherited from class Scene
When active = true - updates and renders
Contains main menu content like buttons to go to other scenes, like game scene or options menu scene*/
class MainMenuScene : public Scene
{

	Button play_b;
	View view;
public:
	MainMenuScene();
	void load();
	SceneType update(IEC& iec, RenderWindow& window, VideoMode videoMode);
	void draw(RenderWindow& window, VideoMode videoMode);

	void unload();
};

