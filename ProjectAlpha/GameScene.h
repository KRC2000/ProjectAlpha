#pragma once
#include "PrecompiledHeaders.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "GUI_Button.h"
#include "GUI_Clocks.h"
#include "GUI_IndicatorLine.h"
#include "GUI_ItemsList.h"
#include "GUI_ActionPanel.h"
#include "GUI_Window.h"
#include "GUI_TextDisplay.h"

/*
Inherited from class Scene
When active = true - updates and renders
Contains game content like map, player, UI, resources*/
class GameScene: public Scene
{
	//bool active = false;
	View view;
	Vector2f viewCenterPos_f{0, 0};

	vector<Texture> textureResourcesVec;
	Font guiFont1;
	//vector<Texture>* textureResourcesVec_p;

	Player player;
	Map map;
	UI ui;
	
public:
	GameScene();
	void load(RenderWindow& window);

	SceneType update(IEC& iec, RenderWindow& window, VideoMode videoMode);
	void draw(RenderWindow& window, VideoMode videoMode);

	void unload();

private:
	void loadResources();

};

