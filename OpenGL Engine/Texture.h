#pragma once
#include <iostream>
#include <unordered_map>
#include "glut.h"
#include "Vector2.h"
#include "stb_image.h"
static class Texture
{
public:
	Texture(GLuint textureID, int width, int height)
	{
		this->textureID = textureID;
		this->size = Vector2(width, height);
	}

	static std::shared_ptr<Texture> LoadFromFile(const char* path);
	GLuint GetID() const;
	Vector2 GetSize() const;
	float GetWidth() const;
	float GetHeight() const;
	void Draw(const Vector2& position, const Vector2& size, const Vector2& scale, float rotation,
		bool tiled, const Vector2& tileSize) const;
	void Draw(const Vector2& position, const Vector2& size, const Vector2& scale, float rotation) const;
private:
	static std::unordered_map<const char*, std::shared_ptr<Texture>> loadedTextures;
	GLuint textureID;
	Vector2 size;
};

