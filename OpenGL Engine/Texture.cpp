#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

std::unordered_map<const char*, std::shared_ptr<Texture>> Texture::loadedTextures;

std::shared_ptr<Texture> Texture::LoadFromFile(const char* path)
{
	auto it = loadedTextures.find(path);
	if (it != loadedTextures.end())
	{
		return loadedTextures[path];
		std::cout << "Texture already loaded, reusing it :3\n";
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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


GLuint Texture::GetID() const
{
	return this->textureID;
}