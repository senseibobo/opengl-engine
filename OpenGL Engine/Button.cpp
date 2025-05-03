#include "Button.h"
#include "GameObject.h"
#include "Sprite.h"

void Button::Start()
{
}

bool Button::CheckIfClicked(int x, int y)
{
	Vector2 clickPoint = Vector2(x, y);
	clickPoint += Camera::GetCurrentCamera()->GetGameObject()->GetTransform()->GetPosition() - Vector2(400,300);
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
}
