#pragma once
#include "Component.h"
#include "UIManager.h"
#include "Texture.h"
#include "Rect2.h"
class UIComponent : public Component
{
public:
	UIComponent()
	{
		anchorTop = 0.0;
		anchorLeft = 0.0;
		anchorRight = 0.0;
		anchorBottom = 0.0;
		offsetLeft = -40;
		offsetRight = 40;
		offsetTop = 40;
		offsetBottom = -40;
		UIManager::AddUIComponent(this);
	}

	// override
	void Draw() const override;
	void OnDestroyed() override;

	// set get
	#pragma region Anchors and Offsets
	// set
	// anchors
	void SetAnchorLeft(float newAnchorLeft);
	void SetAnchorRight(float newAnchorRight);
	void SetAnchorTop(float newAnchorTop);
	void SetAnchorBottom(float newAnchorBottom);

	// offsets
	void SetOffsetLeft(float newOffsetLeft);
	void SetOffsetRight(float newOffsetRight);
	void SetOffsetTop(float newOffsetTop);
	void SetOffsetBottom(float newOffsetBottom);
	
	// get
	// anchors
	float GetAnchorLeft() const;
	float GetAnchorRight() const;
	float GetAnchorTop() const;
	float GetAnchorBottom() const;

	// offsets
	float GetOffsetLeft() const;
	float GetOffsetRight() const;
	float GetOffsetTop() const;
	float GetOffsetBottom() const;

	void SetAnchors(float left, float right, float top, float bottom);
	void SetOffsets(float left, float right, float top, float bottom);
	#pragma endregion

	void SetTexture(std::shared_ptr<Texture> texture);

	Rect2 GetRect() const;

	std::shared_ptr<Texture> LoadAndSetTexture(const char* path);
	

private:
	std::shared_ptr<Texture> texture;

	// anchors
	float anchorLeft;
	float anchorRight;
	float anchorTop;
	float anchorBottom;

	// offsets
	float offsetLeft;
	float offsetRight;
	float offsetTop;
	float offsetBottom;
};

