#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

std::unordered_map<const char*, std::shared_ptr<Texture>> Texture::loadedTextures;

std::shared_ptr<Texture> Texture::LoadFromFile(const char* path)
{
	auto it = loadedTextures.find(path);
	if (it != loadedTextures.end())
	{
		std::cout << "Texture already loaded, reusing it :3\n";
		return loadedTextures[path];
	}
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cout << "ERROR: Couldn't load texture at " << path << "\n";
		return 0;
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureID, width, height);
	loadedTextures[path] = texture;
	std::cout << "Successfully loaded texture from file " << path << ".\n";
	return texture;
}


Vector2 Texture::GetSize() const
{
	return this->size;
}

float Texture::GetWidth() const
{
	return this->size.x;
}

float Texture::GetHeight() const
{
	return this->size.y;
}

void Texture::Draw(const Vector2& position, const Vector2& size, const Vector2& scale, float rotation) const
{
	Draw(position, size, scale, rotation, false, Vector2());
}

void Texture::Draw(const Vector2& position, const Vector2& size, const Vector2& scale, float rotation, 
	bool tiled, const Vector2& tileSize) const
{

	int width = size.x * scale.x;
	int height = size.y * scale.y;
	float left = -width / 2.0;
	float right = -left;
	float up = -height / 2.0;
	float down = -up;
	Vector2 top_left = Vector2(left, up).Rotated(rotation);
	Vector2 top_right = Vector2(right, up).Rotated(rotation);
	Vector2 bottom_left = Vector2(left, down).Rotated(rotation);
	Vector2 bottom_right = Vector2(right, down).Rotated(rotation);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->GetID());
	glBegin(GL_QUADS);
	if (tiled)
	{
		glTexCoord2f(0.0, 0.0);					glVertex2f(position.x + bottom_left.x, position.y + bottom_left.y);
		glTexCoord2f(width / tileSize.x, 0.0);			glVertex2f(position.x + bottom_right.x, position.y + bottom_right.y);
		glTexCoord2f(width / tileSize.x, height / tileSize.y);	glVertex2f(position.x + top_right.x, position.y + top_right.y);
		glTexCoord2f(0.0, height / tileSize.y);			glVertex2f(position.x + top_left.x, position.y + top_left.y);
	}
	else
	{
		glTexCoord2f(0.0, 0.0); glVertex2f(position.x + bottom_left.x, position.y + bottom_left.y);
		glTexCoord2f(1.0, 0.0); glVertex2f(position.x + bottom_right.x, position.y + bottom_right.y);
		glTexCoord2f(1.0, 1.0); glVertex2f(position.x + top_right.x, position.y + top_right.y);
		glTexCoord2f(0.0, 1.0); glVertex2f(position.x + top_left.x, position.y + top_left.y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLuint Texture::GetID() const
{
	return this->textureID;
}