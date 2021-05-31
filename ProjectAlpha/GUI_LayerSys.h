#pragma once
#include "GUI_Element.h"

class GUI_LayerSys
{
	vector<GUI_Element*> layers_dynamic;
	vector<GUI_Element*> layers_static;
public:
	void addDynamicLayer(GUI_Element& element)
	{
		layers_dynamic.push_back(&element);
	};

	void addStaticLayer(GUI_Element& element)
	{
		layers_static.push_back(&element);
	};

	bool update(IEC& iec, RenderWindow& window, View& view)
	{
		for (int i = layers_static.size()-1; i >= 0; i--)
		{
			layers_static[i]->update(iec, window, view);

			if (layers_static[i]->isActive())
			{
				if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
				{
					if (layers_static[i]->getGlobalElementBounds().contains(iec.getMousePos(window, view)))
						iec.eventExpire(Mouse::Left);
				}
			}
			/*s_element->update(iec, window, view);
			if (s_element->getGlobalElementBounds().contains(iec.getMousePos(window, view)));
				iec.eventExpire(Mouse::Left);*/
		}
		return false;
	};
};

