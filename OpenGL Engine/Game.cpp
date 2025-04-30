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

void Game::Reset()
{
	gameObjects.clear();
	Game::InitGame();
}

void Game::SetWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

void Game::AddPlayer()
{
	std::shared_ptr<GameObject> player = AddObject();
	std::shared_ptr<Player> playerComponent = std::make_shared<Player>();
	std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
	std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
	std::shared_ptr<Camera> cameraComponent = std::make_shared<Camera>();
	std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/2025-04-22_20.56.57.png");
	player->AddComponent(spriteComponent);
	player->AddComponent(collisionComponent);
	player->AddComponent(playerComponent);
	player->AddComponent(cameraComponent);
	std::shared_ptr<Transform> transform = player->GetTransform();
	transform->SetPosition(Vector2(400, 500));
	transform->SetScale(Vector2(0.02, 0.07));

	std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
	collisionShape->SetSize(texture->GetSize());
	collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));
	cameraComponent->UpdateView(windowWidth, windowHeight);
}

void Game::AddGround(Vector2 position, Vector2 scale)
{
	std::shared_ptr<GameObject> ground = AddObject();
	std::shared_ptr<Transform> transform = ground->GetTransform();
	transform->SetPosition(position);
	transform->SetScale(scale);
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
	AddGround(Vector2(400, 50), Vector2(0.3,0.1)); // floor all the way down
	AddGround(Vector2(740, 300), Vector2(0.1,1.0)); // big wall to the right
	AddGround(Vector2(200, 200), Vector2(0.1, 0.1)); // first platform

}

void Game::InitInput()
{
	Input::AddInputAction("move_left", -GLUT_KEY_LEFT);
	Input::AddInputAction("move_right", -GLUT_KEY_RIGHT);
	Input::AddInputAction("jump", ' ');
	Input::AddInputAction("reset", 'r');
}
