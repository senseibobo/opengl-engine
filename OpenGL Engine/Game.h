#pragma once
#include <memory>
#include "Input.h"
#include "Scene.h"

class Game
{
public:
	void Start();
	void Idle(float deltaTime);
	void Physics(float deltaTime);
	void Draw();
private:
	std::function<void()> pendingSceneChange;
	std::shared_ptr<Scene> scene;
	Scene* NewScene();
	void InitGame();
	void InitInput();
	void SetMainMenuScene();
	void SetGameScene();
};

