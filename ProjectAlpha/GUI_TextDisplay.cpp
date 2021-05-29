#include "GUI_TextDisplay.h"

GUI_TextDisplay::GUI_TextDisplay() : GUI_Element(GUIElementsEnum::GUI_TEXTDISPLAY)
{
	boundsRectShape.setFillColor({ 0, 0, 0, 30});
}

void GUI_TextDisplay::assignRes(vector<Texture>& uiResVec, vector<Font>* fontsVec, vector<Texture>* texturesResVec)
{
	text.setFont(fontsVec->at((int)UiFontsEnum::KARMAFUTURE));
	text.setString("Text here");
}

bool GUI_TextDisplay::update(IEC& iec, RenderWindow& window, View& view)
{
	/*FloatRect rect{ (pos.x + borderSize) / uiView.getSize().x, (pos.y + borderSize) / uiView.getSize().y, (backgrSize.x - rightSideGap) / uiView.getSize().x, backgrSize.y / uiView.getSize().y };
	windowView.setViewport(rect)*/;

	return false;
}

void GUI_TextDisplay::draw(RenderTarget& target, RenderStates states) const
{
	if (active)
	{
		target.draw(boundsRectShape);

		View temp = target.getView();
		target.setView(windowView);

		target.draw(text);

		target.setView(temp);
	}
}

FloatRect GUI_TextDisplay::getGlobalElementBounds()
{
	return {boundsRectShape.getPosition().x, boundsRectShape.getPosition().y, boundsRectShape.getSize().x, boundsRectShape.getSize().y };
}
