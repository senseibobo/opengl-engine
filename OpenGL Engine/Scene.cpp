#include "Scene.h"
#include "GameObject.h"
#include "PhysicsRectangleShape.h"

Scene* Scene::currentScene;

void Scene::Start()
{
	for (auto& gameObject : GetGameObjects())
	{
		gameObject->Start();
	}
}

std::shared_ptr<GameObject> Scene::AddObject()
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObjects.push_back(gameObject);
	return gameObject;
}

void Scene::AddPlayer(Vector2 position)
{
	std::shared_ptr<GameObject> player = AddObject();
	std::shared_ptr<Player> playerComponent = std::make_shared<Player>();
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	std::shared_ptr<GameCamera> cameraComponent = std::make_shared<GameCamera>();
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	player->AddComponent(spriteComponent);
	player->AddComponent(collisionComponent);
	player->AddComponent(playerComponent);
	player->AddComponent(cameraComponent);
	std::shared_ptr<Transform> transform = player->GetTransform();
	transform->SetPosition(position);
	transform->SetScale(Vector2(0.02, 0.07));

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionShape->SetSize(texture->GetSize());
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
	cameraComponent->UpdateView();
}

void Scene::AddGround(Vector2 position, Vector2 scale)
{
	scale *= (Vector2(1920, 1080) / Vector2(40, 40));
	std::shared_ptr<GameObject> ground = AddObject();
	std::shared_ptr<Transform> transform = ground->GetTransform();
	transform->SetPosition(position-Vector2(0,600));
	transform->SetScale(scale);
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	spriteComponent->SetTiled(true);
	spriteComponent->SetTileSize(Vector2(40, 40));
	ground->AddComponent(collisionComponent);
	ground->AddComponent(spriteComponent);

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));

	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/brickTile.png");
	collisionShape->SetSize(texture->GetSize());
}


std::shared_ptr<Button> Scene::AddButton(Vector2 position, Vector2 size, std::string text, std::function<void()> callback)
{
	std::shared_ptr<GameObject> button = AddObject();
	std::shared_ptr<Button> buttonComponent = std::make_shared<Button>();
	button->AddComponent(buttonComponent);
	buttonComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	buttonComponent->SetAnchors(0.5, 0.5, 0.5, 0.5);
	buttonComponent->SetOffsets(-100, 100, 40, -40);
	buttonComponent->AddCallback(callback);
	return buttonComponent;
}

void Scene::DestroyObject(GameObject* gameObject)
{
	std::cout << "Destroying object!!\n";
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		std::cout << "Checking object\n";
		if (it->get() == gameObject)
		{
			gameObjects.erase(it);
			std::cout << "Removing all components\n";
			break;
		}
	}
}

void Scene::Destroy()
{
	std::cout << "Destroying every object in scene:\n";
	for (const auto& obj : gameObjects) {
		if (!obj) continue;
		std::cout << "Destroying object\n";
		obj->RemoveAllComponents();
		obj->Destroy();
	}
	gameObjects.clear();
}

std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects()
{
	return this->gameObjects;
}

Scene* Scene::GetCurrent()
{
	return currentScene;
}

void Scene::SetCurrent(Scene* scene)
{
	currentScene = scene;
}
