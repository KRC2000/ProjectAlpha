#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	currentScenePtr = &gameScene;


	//window.create(VideoMode(1280, 1024), "Game", Style::None);
	window.create(videoMode, "Game", Style::Default);
	//window.setFramerateLimit(30);
	
	//mainMenuScene.load();
	gameScene.load(window);

	//mainMenuScene.setActive(true, window);
	gameScene.setActive(true, window);
	
	
}

void Game::processing()
{
	while (window.isOpen())
	{
		update();
		draw();
	}
}

////////////////////////////////////////
////-Private functions-/////////////////
////////////////////////////////////////

void Game::update()
{
	while (window.pollEvent(iec.event))
	{
		if (iec.event.type == Event::Closed)
			window.close();
		if (iec.event.type == Event::MouseWheelMoved)
		{
			iec.receiveMouseWheelInput(iec.event.mouseWheel.delta);
		}
		if (iec.event.type == Event::MouseButtonPressed)
		{
			iec.receiveMouseInput(iec.event.mouseButton.button, IEC::KeyState::JUSTPRESSED);
		}
		if (iec.event.type == Event::MouseButtonReleased)
		{
			iec.receiveMouseInput(iec.event.mouseButton.button, IEC::KeyState::JUSTRELEASED);
		}
		if (iec.event.type == Event::KeyPressed)
		{
			iec.receiveKeyboardInput(iec.event.key.code, IEC::KeyState::JUSTPRESSED);
		}
		if (iec.event.type == Event::KeyReleased)
		{
			iec.receiveKeyboardInput(iec.event.key.code, IEC::KeyState::JUSTRELEASED);
		}

	}

	//if (iec._Esc && currentScenePtr != &mainMenuScene) goToScene(MAINMENU_SCENE);
	if (iec.getKeyboardKeyState(Keyboard::Escape) && 
		currentScenePtr != &mainMenuScene) goToScene(SceneType::MAINMENU_SCENE);

	goToScene(gameScene.update(iec, window, videoMode));
	goToScene(mainMenuScene.update(iec, window, videoMode));

	iec.eventUpdate();
}

void Game::draw()
{
	window.clear();

	gameScene.draw(window, videoMode);
	mainMenuScene.draw(window, videoMode);


	window.display();
}

void Game::goMainMenuScene()
{
	//currentScenePtr->unload();
	currentScenePtr->setActive(false, window);
	mainMenuScene.setActive(true, window);
	currentScenePtr = &mainMenuScene;
	
}

void Game::goGameScene()
{
	//currentScenePtr->unload();
	currentScenePtr->setActive(false, window);
	gameScene.setActive(true, window);
	currentScenePtr = &gameScene;
	
}

void Game::goToScene(SceneType scene)
{
	switch (scene)
	{
	case SceneType::NONE_SCENE:
		break;
	case SceneType::MAINMENU_SCENE:
		goMainMenuScene();
		break;
	case SceneType::GAME_SCENE:
		goGameScene();
		break;
	default:
		break;
	}
}
