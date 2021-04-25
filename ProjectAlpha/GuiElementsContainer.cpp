#include "GuiElementsContainer.h"

void GuiElementsContainer::assignResToElements(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec)
{
	for (auto& element : elementsVec)
	{
		element->assignRes(uiResVec, fontsVec, texturesResVec);
	}
}

void GuiElementsContainer::updateElements(IEC& iec, RenderWindow& window, View& view)
{
	for (auto& element : elementsVec)
	{
		element->update(iec, window, view);
	}
}

void GuiElementsContainer::drawElements(RenderTarget& target, RenderStates states) const
{
	GuiElementsContainer::draw(target, states);
}

void GuiElementsContainer::draw(RenderTarget& target, RenderStates states) const
{
	for (auto& element : elementsVec)
	{
		target.draw(*element);
	}
}

void GuiElementsContainer::addGuiElement(GUI_Element* newElement, string name)
{

	newElement->setName(name);
	elementsVec.push_back(newElement);
}
