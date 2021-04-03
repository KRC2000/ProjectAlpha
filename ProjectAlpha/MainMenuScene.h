#pragma once
#include "PrecompiledHeaders.h"
#include "Scene.h"
#include "GUI_Button.h"

#include "UiResEnum.h"
/*
Inherited from class Scene
When active = true - updates and renders
Contains main menu content like buttons to go to other scenes, like game scene or options menu scene*/
class MainMenuScene : public Scene
{

	GUI_Button play_b{UiResEnum::MAINMENU_BUTTON_DEFAULT, "play"};
	View view;
public:
	MainMenuScene();
	void load();
	SceneType update(IEC& iec, RenderWindow& window, VideoMode videoMode);
	void draw(RenderWindow& window, VideoMode videoMode);

	void unload();
};

