#pragma once
#include "UIComponent.h"
#include "Rect2.h"
#include "Camera.h"
#include <functional>

class Sprite;

class Button : public UIComponent
{
public:
	Button() : UIComponent()
	{
		UIManager::AddButton(this);
		std::cout << "Button added\n";
	}
	~Button() override
	{
		UIComponent::~UIComponent();
		UIManager::RemoveButton(this);
		std::cout << "Button removed\n";
	}
	void Start() override;
	void AddCallback(std::function<void()> callback);
	void RemoveCallback(std::function<void()> callback);
	bool CheckIfClicked(int x, int y);
	virtual void Click();
private:
	std::shared_ptr<Sprite> sprite;
	std::vector<std::function<void()>> callbacks;
};

