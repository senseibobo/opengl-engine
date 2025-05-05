#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "Vector2.h"
#include "Physics.h"
#include "Components.h"

class GameObject;
class Scene
{
public:
	// static
	static Scene* GetCurrent();
	static void SetCurrent(Scene* scene);

	// other
	void Start();
	std::shared_ptr<GameObject> AddObject();
	void AddPlayer(Vector2 position);
	void AddGround(Vector2 position, Vector2 scale);
	std::shared_ptr<Button> AddButton(Vector2 position, Vector2 size, std::string text, std::function<void()> callback);
	void DestroyObject(GameObject* gameObject);
	void Destroy();

	// set 

	// get 
	std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	static Scene* currentScene;
};

