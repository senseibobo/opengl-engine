#pragma once
#include <vector>

class Button;
class UIComponent;

class UIManager
{
public:
	UIManager() = delete;
	static void AddUIComponent(UIComponent* component);
	static void RemoveUIComponent(UIComponent* component);
	static void AddButton(Button* button);
	static void RemoveButton(Button* button);
	static void CheckClick(int x, int y);
private:
	static std::vector<UIComponent*> uiComponents;
	static std::vector<Button*> buttons;
	
};

