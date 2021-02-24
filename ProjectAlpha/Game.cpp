#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	currentScenePtr = &mainMenuScene;


	//window.create(VideoMode(1280, 1024), "Game", Style::None);
	window.create(videoMode, "Game", Style::Default);
	//window.setFramerateLimit(30);
	
	mainMenuScene.load();
	gameScene.load(window);

	mainMenuScene.setActive(true, window);
	
	
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
	
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseWheelMoved)
		{
			iec.mouseWheelScrolling(event.mouseWheel.delta);
			//cout << iec.mouseWheelDelta << endl;
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Left) iec.LMBclick();
			if (event.key.code == Mouse::Right) iec.RMBclick();
		}
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left) iec.LMBrelease();
			if (event.key.code == Mouse::Right) iec.RMBrelease();
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up) iec.pressUp();
			if (event.key.code == Keyboard::Down) iec.pressDown();
			if (event.key.code == Keyboard::Left) iec.pressLeft();
			if (event.key.code == Keyboard::Right) iec.pressRight();
			if (event.key.code == Keyboard::Escape) iec.pressEscape();
			if (event.key.code == Keyboard::W) iec.pressW();
			if (event.key.code == Keyboard::A) iec.pressA();
			if (event.key.code == Keyboard::S) iec.pressS();
			if (event.key.code == Keyboard::D) iec.pressD();
			if (event.key.code == Keyboard::R) iec.pressR();
			if (event.key.code == Keyboard::K) iec.pressK();
			if (event.key.code == Keyboard::X) iec.pressX();
			if (event.key.code == Keyboard::Space) iec.pressSpace();
			if (event.key.code == Keyboard::LShift) iec.pressLShift();
			if (event.key.code == Keyboard::F5) iec.pressF5();
			if (event.key.code == Keyboard::F6) iec.pressF6();
			if (event.key.code == Keyboard::F11) iec.pressF11();
			if (event.key.code == Keyboard::F12) iec.pressF12();
			if (event.key.code == Keyboard::Equal) iec.pressEqual();
			if (event.key.code == Keyboard::Dash) iec.pressDash();
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Up) iec.releaseUp();
			if (event.key.code == Keyboard::Down) iec.releaseDown();
			if (event.key.code == Keyboard::Left) iec.releaseLeft();
			if (event.key.code == Keyboard::Right) iec.releaseRight();
			if (event.key.code == Keyboard::Escape) iec.releaseEscape();
			if (event.key.code == Keyboard::W) iec.releaseW();
			if (event.key.code == Keyboard::A) iec.releaseA();
			if (event.key.code == Keyboard::S) iec.releaseS();
			if (event.key.code == Keyboard::D) iec.releaseD();
			if (event.key.code == Keyboard::R) iec.releaseR();
			if (event.key.code == Keyboard::K) iec.releaseK();
			if (event.key.code == Keyboard::X) iec.releaseX();
			if (event.key.code == Keyboard::Space) iec.releaseSpace();
			if (event.key.code == Keyboard::LShift) iec.releaseLShift();
			if (event.key.code == Keyboard::F5) iec.releaseF5();
			if (event.key.code == Keyboard::F6) iec.releaseF6();
			if (event.key.code == Keyboard::F11) iec.releaseF11();
			if (event.key.code == Keyboard::F12) iec.releaseF12();
			if (event.key.code == Keyboard::Equal) iec.releaseEqual();
			if (event.key.code == Keyboard::Dash) iec.releaseDash();
		}

	}
	if (iec._Esc && currentScenePtr != &mainMenuScene) goToScene(MAINMENU_SCENE);

	goToScene(gameScene.update(iec, window, videoMode));
	goToScene(mainMenuScene.update(iec, window, videoMode));

	iec.eventUpdate();
}

void Game::draw()
{
	window.clear(Color::Green);

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
	cout << "Switched to Game scene!" << endl;
	
}

void Game::goToScene(SceneType scene)
{
	switch (scene)
	{
	case NONE_SCENE:
		break;
	case MAINMENU_SCENE:
		goMainMenuScene();
		break;
	case GAME_SCENE:
		goGameScene();
		break;
	default:
		break;
	}
}
