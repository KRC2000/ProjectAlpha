#pragma once
#include "PrecompiledHeaders.h"
#include "GameScene.h"
#include "MainMenuScene.h"


class Game
{
	RenderWindow window;
	//VideoMode videoMode{ 1920, 1080 };
	VideoMode videoMode{ 1366, 768 };
	//VideoMode videoMode{ 1440, 900 };

	IEC iec;
	
	// Scenes
	Scene* currentScenePtr;
	MainMenuScene mainMenuScene;
	GameScene gameScene;


public:
	Game();
	void processing();
private:
	void update();
	void draw();

	void goMainMenuScene();
	void goGameScene();
	void goToScene(SceneType scene);
};

