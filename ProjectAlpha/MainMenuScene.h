#pragma once
#include "PrecompiledHeaders.h"
#include "Scene.h"
#include "Button.h"

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

