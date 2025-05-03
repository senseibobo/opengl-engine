#include "Sprite.h"
#include "GameObject.h"

void Sprite::SetTexture(std::shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void Sprite::SetScale(Vector2 newScale)
{
	this->scale = newScale;
}

void Sprite::SetFlipHorizontal(bool newFlipHorizontal)
{
	this->flipHorizontal = newFlipHorizontal;
}

void Sprite::SetFlipVertical(bool newFlipVertical)
{
	this->flipVertical = newFlipVertical;
}

void Sprite::SetOffset(Vector2 newOffset)
{
	this->offset = newOffset;
}

void Sprite::SetTiled(bool newTiled)
{
	this->tiled = newTiled;
}

void Sprite::SetTileSize(Vector2 newTileSize)
{
	this->tileSize = newTileSize;
}

void Sprite::SetTileOffset(Vector2 newTileOffset)
{
	this->tileOffset = newTileOffset;
}

std::shared_ptr<Texture> Sprite::GetTexture() const
{
	return this->texture;
}

Vector2 Sprite::GetScale() const
{
	return this->scale;
}

Rect2 Sprite::GetRect() const
{
	std::shared_ptr<Transform> transform = GetGameObject()->GetTransform();
	Rect2 rect;
	rect.size = texture->GetSize() * scale * transform->GetScale();
	rect.position = transform->GetPosition() + offset;
	rect.position -= rect.size / 2.0;
	return rect;
}

bool Sprite::GetFlipHorizontal() const
{
	return this->flipHorizontal;
}

bool Sprite::GetFlipVertical() const
{
	return this->flipVertical;
}

Vector2 Sprite::GetOffset() const
{
	return this->offset;
}

bool Sprite::GetTiled() const
{
	return this->tiled;
}

Vector2 Sprite::GetTileSize() const
{
	return this->tileSize;
}

Vector2 Sprite::GetTileOffset() const
{
	return this->tileOffset;
}

std::shared_ptr<Texture> Sprite::LoadAndSetTexture(const char* path)
{
	std::shared_ptr<Texture> texture = Texture::LoadFromFile(path);
	SetTexture(texture);
	return texture;
}

void Sprite::Draw() const
{
	if (!texture) return;
	Transform* transform = GetGameObject()->GetTransform().get();
	Vector2 size = texture->GetSize();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale() * this->scale;
	float rotation = transform->GetRotation();
	int flipHScale = GetFlipHorizontal() ? -1 : 1;
	int flipVScale = GetFlipVertical() ? -1 : 1;
	scale *= Vector2(flipHScale, flipVScale);
	position += GetOffset();
	texture->Draw(position, size, scale, rotation, tiled, tileSize);
}