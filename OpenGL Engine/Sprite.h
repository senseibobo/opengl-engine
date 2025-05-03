#pragma once
#include "Component.h"
#include "glut.h"
#include "Rect2.h"
#include "Texture.h"
class Sprite : public Component
{
public:

	Sprite()
	{
		this->scale = Vector2(1.0,1.0);
		this->flipHorizontal = false;
		this->flipVertical = false;
		this->tiled = false;
		this->tileSize = Vector2(32, 32);
		this->tileOffset = Vector2(0.0, 0.0);
	}

	// set
	void SetTexture(std::shared_ptr<Texture> texture);
	void SetScale(Vector2 newScale);
	void SetFlipHorizontal(bool newFlipHorizontal);
	void SetFlipVertical(bool newFlipVertical);
	void SetOffset(Vector2 newOffset);
	void SetTiled(bool newTiled);
	void SetTileSize(Vector2 newTileSize);
	void SetTileOffset(Vector2 newTileOffset);

	// get
	std::shared_ptr<Texture> GetTexture() const;
	Vector2 GetScale() const;
	Rect2 GetRect() const;
	bool GetFlipHorizontal() const;
	bool GetFlipVertical() const;
	Vector2 GetOffset() const;
	bool GetTiled() const;
	Vector2 GetTileSize() const;
	Vector2 GetTileOffset() const;

	// other
	std::shared_ptr<Texture> LoadAndSetTexture(const char* path);
	void Draw() const override;
private:
	std::shared_ptr<Texture> texture;
	Vector2 scale;
	Vector2 offset;
	bool flipHorizontal;
	bool flipVertical;
	bool tiled;
	Vector2 tileSize;
	Vector2 tileOffset;
};

