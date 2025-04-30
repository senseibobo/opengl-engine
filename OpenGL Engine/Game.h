#pragma once
#include <memory>
#include "GameObject.h"
#include "Components.h"
#include "Input.h"
class Game
{
public:
	std::shared_ptr<GameObject> AddObject();
	void Start();
	void Idle(float deltaTime);
	void Physics(float deltaTime);
	void Draw();
	void Reset();
	void SetWindowSize(int width, int height);
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	void InitGame();
	void InitInput();
	void AddPlayer();
	void AddGround(Vector2 position, Vector2 scale);
	int windowWidth;
	int windowHeight;

};

