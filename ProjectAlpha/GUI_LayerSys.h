#pragma once
#include "GUI_Element.h"

class GUI_LayerSys : public Drawable
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
		for (int i = layers_dynamic.size() - 1; i >= 0; i--)
		{
			layers_dynamic[i]->update(iec, window, view);

			if (layers_dynamic[i]->isActive())
			{
				if (iec.getMouseButtonState(Mouse::Left) == IEC::KeyState::JUSTPRESSED)
				{
					if (layers_dynamic[i]->getGlobalElementBounds().contains(iec.getMousePos(window, view)))
					{
						iec.eventExpire(Mouse::Left);
						GUI_Element* interacted = layers_dynamic[i];
						for (int k = i; k < layers_dynamic.size()-1; k++)
						{
							layers_dynamic[k] = layers_dynamic[k + 1];
						}
						layers_dynamic.back() = interacted;
					}
				}
			}
		}
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
		}
		return false;
	};

	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const override
	{
		for (auto& static_element : layers_static)
		{
			target.draw(*static_element);
		}
		for (auto& dynamic_element : layers_dynamic)
		{
			target.draw(*dynamic_element);
		}
	};

};

