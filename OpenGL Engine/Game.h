#pragma once
#include <memory>
#include "Input.h"
#include "Scene.h"

class Game
{
public:
	Game()
	{
		Instance = this;
	}
	static Game* Instance;
	std::shared_ptr<Scene> scene;
	void Start();
	void Idle(float deltaTime);
	void Physics(float deltaTime);
	void Draw();
private:
	std::function<void()> pendingSceneChange;
	Scene* NewScene();
	void InitGame();
	void InitInput();
	void SetMainMenuScene();
	void SetGameScene();
	void LoadFile();
};

