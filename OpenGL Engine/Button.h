#pragma once
#include "UIComponent.h"
#include "Rect2.h"
#include "Camera.h"

class Sprite;

class Button : public UIComponent
{
public:
	Button() : UIComponent()
	{
		UIManager::AddButton(this);
	}
	~Button() override
	{
		UIComponent::~UIComponent();
		UIManager::RemoveButton(this);
	}
	void Start() override;
	bool CheckIfClicked(int x, int y);
	virtual void Click();
private:
	std::shared_ptr<Sprite> sprite;
};

