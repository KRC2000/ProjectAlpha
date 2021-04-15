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
		if (iec.getMouseWheelDelta() != 0) view.zoom(1 - (float)iec.getMouseWheelDelta() / 10);
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
	for (int i = 0; i < (int)ResourcesEnum::RESOURCES_AMOUNT; i++)
	{
		Texture t;
		textureResourcesVec.push_back(t);
	}

	///////////// Loading textures /////////////
	textureResourcesVec[(int)ResourcesEnum::PLAYERICON_T].loadFromFile("res/playerIcon.png");
	textureResourcesVec[(int)ResourcesEnum::TARGETPOINT_T].loadFromFile("res/impact-point.png");
	textureResourcesVec[(int)ResourcesEnum::POINTERS_T].loadFromFile("res/buildings.png");
	textureResourcesVec[(int)ResourcesEnum::GUI_T].loadFromFile("res/GUI.png");
	textureResourcesVec[(int)ResourcesEnum::ITEMSLISTITEM_T].loadFromFile("res/ItemBar.png");
	textureResourcesVec[(int)ResourcesEnum::INDICATORLINE_T].loadFromFile("res/IndicatorLine.png");
	textureResourcesVec[(int)ResourcesEnum::STATUSICONS_T].loadFromFile("res/statusIcons.png");
	textureResourcesVec[(int)ResourcesEnum::ITEMS_T].loadFromFile("res/Items.png");
	textureResourcesVec[(int)ResourcesEnum::ACTIONPANEL_T].loadFromFile("res/actionPanel.png");
	textureResourcesVec[(int)ResourcesEnum::GUN_AK_T].loadFromFile("res/gun.png");
	textureResourcesVec[(int)ResourcesEnum::BULLET_T].loadFromFile("res/bullet.png");
	////////////////////////////////////////////

	if (!guiFont1.loadFromFile("res/KarmaFuture.ttf")) cout << ">>>>>Font loading failed!" << endl;


}

