#pragma once
#include "PrecompiledHeaders.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

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

