#include "Game.h"
#include "PhysicsRectangleShape.h"


std::vector<std::shared_ptr<GameObject>> gameObjects;

std::shared_ptr<GameObject> Game::AddObject()
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObjects.push_back(gameObject);
	return gameObject;
}

void Game::Start()
{
	InitInput();
	InitGame();
	for (auto& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Game::Idle(float deltaTime)
{
	for (std::shared_ptr<GameObject> gameObject : gameObjects)
	{
		gameObject->Process(deltaTime);
	}
	glutPostRedisplay();
}

void Game::Physics(float deltaTime)
{
	for (std::shared_ptr<GameObject> gameObject : gameObjects)
	{
		gameObject->PhysicsProcess(deltaTime);
	}
}

void Game::Draw()
{
	for (auto gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}

void Game::AddPlayer()
{
	std::shared_ptr<GameObject> player = AddObject();
	std::shared_ptr<Player> playerComponent = std::make_shared<Player>();
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	player->AddComponent(spriteComponent);
	player->AddComponent(collisionComponent);
	player->AddComponent(playerComponent);
	std::shared_ptr<Transform> transform = player->GetTransform();
	transform->SetPosition(Vector2(400, 500));
	transform->SetScale(Vector2(0.1, 0.1));

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionShape->SetSize(texture->GetSize());
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
}

void Game::AddGround()
{
	std::shared_ptr<GameObject> ground = AddObject();
	std::shared_ptr<Transform> transform = ground->GetTransform();
	transform->SetPosition(Vector2(400, 50));
	transform->SetScale(Vector2(1, 0.1));
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	ground->AddComponent(collisionComponent);
	ground->AddComponent(spriteComponent);

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
	
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	collisionShape->SetSize(texture->GetSize());
}

void Game::InitGame()
{
	AddPlayer();
	AddGround();
}

void Game::InitInput()
{
	Input::AddInputAction("move_left", -GLUT_KEY_LEFT);
	Input::AddInputAction("move_right", -GLUT_KEY_RIGHT);
}
