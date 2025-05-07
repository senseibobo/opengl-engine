#include "UIComponent.h"
#include "GameObject.h"


#pragma region Anchors and Offsets
#pragma region Set
void UIComponent::SetAnchorLeft(float newAnchorLeft)
{
	anchorLeft = newAnchorLeft;
}
void UIComponent::SetAnchorRight(float newAnchorRight)
{
	anchorRight = newAnchorRight;
}
void UIComponent::SetAnchorTop(float newAnchorTop)
{
	anchorTop = newAnchorTop;
}
void UIComponent::SetAnchorBottom(float newAnchorBottom)
{
	anchorBottom = newAnchorBottom;
}

void UIComponent::SetOffsetLeft(float newOffsetLeft)
{
	offsetLeft = newOffsetLeft;
}
void UIComponent::SetOffsetRight(float newOffsetRight)
{
	offsetRight = newOffsetRight;
}
void UIComponent::SetOffsetTop(float newOffsetTop)
{
	offsetTop = newOffsetTop;
}
void UIComponent::SetOffsetBottom(float newOffsetBottom)
{
	offsetBottom = newOffsetBottom;
}
#pragma endregion
#pragma region Get
float UIComponent::GetAnchorLeft() const
{
	return anchorLeft;
}
float UIComponent::GetAnchorRight() const
{
	return anchorRight;
}
float UIComponent::GetAnchorTop() const
{
	return anchorTop;
}
float UIComponent::GetAnchorBottom() const
{
	return anchorBottom;
}

float UIComponent::GetOffsetLeft() const
{
	return offsetLeft;
}
float UIComponent::GetOffsetRight() const
{
	return offsetRight;
}
float UIComponent::GetOffsetTop() const
{
	return offsetTop;
}
float UIComponent::GetOffsetBottom() const
{
	return offsetBottom;
}
void UIComponent::SetAnchors(float left, float right, float top, float bottom)
{
	anchorLeft = left;
	anchorRight = right;
	anchorTop = top;
	anchorBottom = bottom;
}
void UIComponent::SetOffsets(float left, float right, float top, float bottom)
{
	offsetLeft = left;
	offsetRight = right;
	offsetTop = top;
	offsetBottom = bottom;
}
Rect2 UIComponent::GetRect() const
{
	float left = anchorLeft * 800 + offsetLeft;
	float right = anchorRight * 800 + offsetRight;
	float top = anchorTop * 600 - offsetTop;
	float bottom = anchorBottom * 600 - offsetBottom;
	Vector2 position = Vector2(left, top) + GetGameObject()->GetTransform()->GetPosition();
	Vector2 size = Vector2(right, bottom) - Vector2(left, top);
	Rect2 rect = Rect2(position + size/2.0, size);
	return rect;
}
#pragma endregion
#pragma endregion


void UIComponent::Draw() const
{
	if (!texture) return;
	Rect2 rect = GetRect();
	texture->Draw(rect.position, rect.size, Vector2(1,1), 0.0);
}

void UIComponent::OnDestroyed()
{
	UIManager::RemoveUIComponent(this);
}

void UIComponent::SetTexture(std::shared_ptr<Texture> texture)
{
	this->texture = texture;
}

std::shared_ptr<Texture> UIComponent::LoadAndSetTexture(const char* path)
{
	std::shared_ptr<Texture> texture = Texture::LoadFromFile(path);
	SetTexture(texture);
	return texture;
}