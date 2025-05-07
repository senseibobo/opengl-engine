#include "Button.h"
#include "GameObject.h"
#include "Sprite.h"

void Button::Start()
{
	std::cout << "Component here!";
}

void Button::AddCallback(std::function<void()> callback)
{
	callbacks.push_back(callback);
}

void Button::RemoveCallback(std::function<void()> callback)
{
	// TODO
}

bool Button::CheckIfClicked(int x, int y)
{
	std::cout << GetGameObject()->GetComponents().size();
	Vector2 clickPoint = Vector2(x, y);
	clickPoint -= Vector2(400, 300);
	if(Camera::GetCurrentCamera())
		clickPoint += Camera::GetCurrentCamera()->GetGameObject()->GetTransform()->GetPosition() ;
	Rect2 rect = GetRect();
	rect.position -= rect.size / 2.0;
	if (rect.ContainsPoint(clickPoint))
	{
		Click();
		return true;
	}
	else
		return false;
}

void Button::Click()
{
	for (const std::function<void()>& callback : callbacks)
	{
		if(callback)
			callback();
		else
		{
			std::cerr << "Callback isn't valid\n";
		}
	}
}

void Button::OnDestroyed()
{
	UIManager::RemoveButton(this);
	UIComponent::OnDestroyed();
}
