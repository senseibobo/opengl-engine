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

std::shared_ptr<Texture> Sprite::GetTexture() const
{
	return this->texture;
}

Vector2 Sprite::GetScale()
{
	return this->scale;
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
	float left = -size.x * scale.x / 2.0;
	float right = -left;
	float up = -size.y * scale.y / 2.0;
	float down = -up;
	Vector2 top_left = Vector2(left, up).Rotated(rotation);
	Vector2 top_right = Vector2(right, up).Rotated(rotation);
	Vector2 bottom_left = Vector2(left, down).Rotated(rotation);
	Vector2 bottom_right = Vector2(right, down).Rotated(rotation);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(position.x + bottom_left.x, position.y + bottom_left.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(position.x + bottom_right.x, position.y + bottom_right.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(position.x + top_right.x, position.y + top_right.y);
	glTexCoord2f(0.0, 1.0); glVertex2f(position.x + top_left.x, position.y + top_left.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}