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
	}
	void Start() override;
	void AddCallback(std::function<void()> callback);
	void RemoveCallback(std::function<void()> callback);
	bool CheckIfClicked(int x, int y);
	virtual void Click();
	void OnDestroyed() override;
private:
	std::shared_ptr<Sprite> sprite;
	std::vector<std::function<void()>> callbacks;
};

