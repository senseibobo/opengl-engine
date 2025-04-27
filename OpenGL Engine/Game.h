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
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;

	void InitGame();
	void InitInput();
	void AddPlayer();
	void AddGround();

};

