#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::load()
{
	//play_b.load("res/playButton.png", "play");
	//play_b.assignTextureRes();
	cout << "Main menu scene loaded!" << endl;
}

SceneType MainMenuScene::update(IEC& iec, RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		if (play_b.update(iec, window, view)) return SceneType::GAME_SCENE;
		
		
	}
	return NONE_SCENE;
}

void MainMenuScene::draw(RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		View temp;
		temp = window.getView();
		window.setView(view);

		window.draw(play_b);
		//play_b.draw(window);

		window.setView(temp);
	}
}

void MainMenuScene::unload()
{
	cout << "Main menu scene UNloaded!" << endl;
}
