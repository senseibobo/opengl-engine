#include "UIManager.h"
#include "Button.h"

std::vector<UIComponent*> UIManager::uiComponents;
std::vector<Button*> UIManager::buttons;

void UIManager::AddUIComponent(UIComponent* component)
{
	uiComponents.push_back(component);
}

void UIManager::RemoveUIComponent(UIComponent* component)
{
	auto begin = uiComponents.begin();
	auto end = uiComponents.end();
	auto it = std::find(begin, end, component);
	uiComponents.erase(it);
}

void UIManager::AddButton(Button* button)
{
	buttons.push_back(button);
}

void UIManager::RemoveButton(Button* button)
{
	auto begin = buttons.begin();
	auto end = buttons.end();
	auto it = std::find(begin, end, button);
	buttons.erase(it);
}

void UIManager::CheckClick(int x, int y)
{
	for (auto button : buttons)
	{
		if (button->CheckIfClicked(x, y))
			break;
	}
}
