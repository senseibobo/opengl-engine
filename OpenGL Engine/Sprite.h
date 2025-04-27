#pragma once
#include "Component.h"
#include "glut.h"
#include "Vector2.h"
#include "Texture.h"
class Sprite : public Component
{
public:
	// set
	void SetTexture(std::shared_ptr<Texture> texture);

	// get
	std::shared_ptr<Texture> GetTexture();

	// other
	std::shared_ptr<Texture> LoadAndSetTexture(const char* path);
	void Draw() const override;
private:
	std::shared_ptr<Texture> texture;
};

