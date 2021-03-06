#pragma once
#include <vector>

#include "GUI_Element.h"


/*
Parental class for GUI_Element-s that contain multiple GUI_Element.
In GUI_Element that contains 
*/
class GuiElementsContainer: public Drawable
{
	vector<GUI_Element*> elementsVec;

private:
	void draw(RenderTarget& target, RenderStates states) const;

public:
	GuiElementsContainer() {};
	virtual ~GuiElementsContainer() {};

	void assignResToElements(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec);

	void updateElements(IEC& iec, RenderWindow& window, View& view);

	void drawElements(RenderTarget& target, RenderStates states = RenderStates::Default) const;

	GUI_Element& addGuiElement(GUI_Element* newElement, string name);

	vector<GUI_Element*>& getElementsVec() { return elementsVec; };

	template <class Element> Element* getGuiElement(string guiElementName);
};

template<class Element>
inline Element* GuiElementsContainer::getGuiElement(string guiElementName)
{
	for (auto& element : elementsVec)
	{
		if (element->getName() == guiElementName)
		{
			return dynamic_cast<Element*>(element);
		}
	}
	return nullptr;
}