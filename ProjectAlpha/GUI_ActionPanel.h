#pragma once
#include "PrecompiledHeaders.h"
#include "GUI_Button.h"
#include "GUI_Element.h"

class GUI_ActionPanel: public GUI_Element
{
	Vector2f pos{ 0,0 };
	Sprite s_head, s_body, s_tail;
	vector<GUI_Button> buttonsVec;

	bool active = false;
	GUI_Button* usedButton = nullptr;
	//GUI_ItemsListItem* itemPointer;
public:
	GUI_ActionPanel() : GUI_Element(GUIElementsEnum::GUI_ACTIONPANEL) {};
	virtual ~GUI_ActionPanel() {};

	virtual void assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec = nullptr, vector<Texture>* texturesResVec = nullptr) override;
	virtual bool update(IEC& iec, RenderWindow& window, View& view) override;
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override;


	//void load(vector<Texture>& textureResourcesVec);

	/*Returns pointer to a button that was clicked inside of a panel*/
	GUI_Button& getActivatedButton();


	/*Widening widget bounds, creating and adding new button to it in a row*/
	void addActionButton(vector<Texture>& uiResVec, UiResEnum buttonType, string buttonName);


	/*Set to true to allow updating and drawing*/
	void setActive(bool isActive);
	void setPos(Vector2f newPos);

	bool getIsActive();
};

