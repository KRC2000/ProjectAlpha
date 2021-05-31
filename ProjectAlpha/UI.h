#pragma once
#include "PrecompiledHeaders.h"

#include "GUI_Element.h"
#include "GUI_LayerSys.h"
#include "UiResEnum.h"
#include "UiFontsEnum.h"

class UI
{
public:
	GUI_LayerSys layerSys;
private:
	vector<GUI_Element*> guiElementsVec;

	/*Global textures storage reference to spread among object's load() functions*/
	vector<Texture>* texturesResVecPtr;
	vector<Texture> uiResVec;
	vector<Font> uiFontsVec;

	/* Own view for objects, that should be aligned to center of the screen
	 and not to global world*/
	View view;

	/* Used to store and restore window view that disconnects when assigning UI's own 
	 view to the window to draw UI content*/
	View tempView;

	bool playerInventoryIsOpened = false;
	bool playerIsInsideLocation = false;

	/* Font reference to spread among object's load() functions(those who got drawable Text objects)*/
	Font* guiFont1 = nullptr;

public:
	UI();

	// Sets view, loads resources to all gui elements
	void load(vector<Texture>* texturesResourcesVec, RenderWindow& window, Font* font);

	GUI_Element& addGuiElement(GUI_Element* newElement, string name);

	void update(IEC& iec, RenderWindow& window);
	void draw(RenderWindow& window);

	////////// SETTERS

	void setPlayerInventoryIsOpened(bool isOpened);
	void setPlayerIsInsideLocation(bool isInside);

	//////////////////

	////////// GETTERS

	template <class Element> Element* getGuiElement(string guiElementName);
	vector<Texture>& getUiResVec() { return uiResVec; };
	vector<GUI_Element*>& getGuiElementsVec() {return guiElementsVec;};
	bool getPlayerInventoryIsOpened();
	const View& getView() { return view; };

	//////////////////

	// Functions for use only inside the class
private:

	void loadUiRes();
};

template<class Element>
inline Element* UI::getGuiElement(string guiElementName)
{
	for (auto& element : guiElementsVec)
	{
		if (element->getName() == guiElementName)
		{
			return dynamic_cast<Element*>(element);
		}
	}
}
