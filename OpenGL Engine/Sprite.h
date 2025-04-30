#pragma once
#include "Component.h"
#include "glut.h"
#include "Vector2.h"
#include "Texture.h"
class Sprite : public Component
{
public:

	Sprite()
	{
		this->scale = Vector2(1.0,1.0);
		this->flipHorizontal = false;
		this->flipVertical = false;
	}

	// set
	void SetTexture(std::shared_ptr<Texture> texture);
	void SetScale(Vector2 newScale);
	void SetFlipHorizontal(bool newFlipHorizontal);
	void SetFlipVertical(bool newFlipVertical);
	void SetOffset(Vector2 newOffset);

	// get
	std::shared_ptr<Texture> GetTexture() const;
	Vector2 GetScale();
	bool GetFlipHorizontal() const;
	bool GetFlipVertical() const;
	Vector2 GetOffset() const;

	// other
	std::shared_ptr<Texture> LoadAndSetTexture(const char* path);
	void Draw() const override;
private:
	std::shared_ptr<Texture> texture;
	Vector2 scale;
	Vector2 offset;
	bool flipHorizontal;
	bool flipVertical;
};

