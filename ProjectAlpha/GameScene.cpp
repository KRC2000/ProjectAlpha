#include "GameScene.h"

GameScene::GameScene():
	player({ 300, 200 })
	
{
	
}

void GameScene::load(RenderWindow& window)
{
	view.reset(FloatRect(0, 0, 1920, 1080));
	view.zoom(1);

	loadResources();

	ui.load(&textureResourcesVec, window, &guiFont1);

	player.load(textureResourcesVec, ui);
	map.loadTextures(&textureResourcesVec);

	

	cout << "Game scene loaded!" << endl;
}

SceneType GameScene::update(IEC& iec, RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		ui.update(iec, window);

		player.update(iec, window, map, ui);
		view.setCenter(player.getPos());

		map.update(iec, window);
		

		//if (iec._LMB) { cout << iec.getMousePos(window, window.getView()).x << "  " << iec.getMousePos(window, window.getView()).y << endl; }
		if (iec.mouseWheelDelta != 0) view.zoom(1 - (float)iec.mouseWheelDelta / 10);
	}
	return NONE_SCENE;
}

void GameScene::draw(RenderWindow& window, VideoMode videoMode)
{
	if (active)
	{
		window.setView(view);

		map.draw(window);
		player.draw(window);

		ui.draw(window);
		
		
	}
}

void GameScene::unload()
{
	cout << "Game scene UNloaded!" << endl;
}



void GameScene::loadResources()
{
	for (int i = 0; i < RESOURCES_AMOUNT; i++)
	{
		Texture t;
		textureResourcesVec.push_back(t);
	}

	///////////// Loading textures /////////////
	textureResourcesVec[PLAYERICON_T].loadFromFile("res/playerIcon.png");
	textureResourcesVec[TARGETPOINT_T].loadFromFile("res/impact-point.png");
	textureResourcesVec[POINTERS_T].loadFromFile("res/buildings.png");
	textureResourcesVec[GUI_T].loadFromFile("res/GUI.png");
	textureResourcesVec[ITEMSLISTITEM_T].loadFromFile("res/ItemBar.png");
	textureResourcesVec[INDICATORLINE_T].loadFromFile("res/IndicatorLine.png");
	textureResourcesVec[LEGS_T].loadFromFile("res/legs.png");
	textureResourcesVec[LEGS_ZOMBIE_T].loadFromFile("res/legsZombie.png");
	textureResourcesVec[PISTOL_TT_T].loadFromFile("res/pistol.png");
	textureResourcesVec[GUN_AK_T].loadFromFile("res/gun.png");
	textureResourcesVec[BULLET_T].loadFromFile("res/bullet.png");
	////////////////////////////////////////////

	if (!guiFont1.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;


}

